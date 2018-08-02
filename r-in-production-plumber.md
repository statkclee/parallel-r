---
layout: page
title: R 병렬 프로그래밍
date: "2018-08-02"
subtitle: R 양산환경(`plumber`) - 타이타닉
output:
  html_document: 
    toc: yes
    toc_float: true
    highlight: tango
    number_section: true
    code_folding: show
mainfont: NanumGothic
---



# 타이타닉 생존 확률 예측 서비스 [^plumber-titanic-api] {#titanic-survival-probability-in-production}

[^plumber-titanic-api]: [the raybuhr blog, "Making Predictions over HTTP with R", October 17, 2017](https://github.com/raybuhr/plumber-titanic)

기본적으로 서비스로 관심이 있는 것은 타이타닉호에 승선했을 때, 나이, 호실, 성별 등 기본정보를 입력했을 때
생존확률이 얼마인지 알려주는 서비스를 제공하는 것이다.
결국 예측모형을 `.RData`, `.rds` 파일로 저장하면 RESTful API 서비스를 
`plumber.R` 혹은 `titanic-api.R` 파일에 기술한다. 통상 **끝점(endpoint)** 서비스를 기술한다.

- `#* @get /healthcheck`
- `#* @get /`
- `#* @html`
- `#* @post /survival`
- `#* @get /survival`

반면에, `rounter` 혹은 `server.R` 파일에는 암화화 쿠기, 오류 처리 등을 포함하여 서비스를 제공한다.

<img src="fig/plumber-titanic-api.png" alt="타이타닉 RESTful API 개발" width="100%" />


## 타이타닉 생존 모형 {#step-01-titanic-survival-probability}

[캐글 타이타닉](https://www.kaggle.com/c/titanic/data) 데이터를 다운로드 받아 생존 예측모형을 제작한다.


```r
# 0. 환경설정 -------------------
library(tidyverse)

# 1. 데이터 불러오기 -------------------

titanic_dat <- read_csv("data/titanic-train.csv")

# 2. 데이터 전처리 -------------------

transform_titantic_data <- function(input_titantic_data) {
    ouput_titantic_data <- data_frame(
        survived = factor(input_titantic_data$Survived, levels = c(0, 1)),
        pclass   = factor(input_titantic_data$Pclass, levels = c(1, 2, 3)),
        female   = tolower(input_titantic_data$Sex) == "female",
        age      = factor(dplyr::if_else(input_titantic_data$Age < 18, "child", "adult", "unknown"), 
                     levels = c("child", "adult", "unknown"))
    )
    return(ouput_titantic_data)
}

titanic_df <- transform_titantic_data(titanic_dat)

# 3. 예측모형  -------------------

training_rows <- sample(1:nrow(titanic_df), size = floor(0.7*nrow(titanic_df)))
train_df <- titanic_df[training_rows, ]
test_df <- titanic_df[-training_rows, ]

titanic_glm <- glm(survived ~ pclass + female + age, 
                   data = titanic_df, 
                   family = binomial(link = "logit"))

# 4. 모형성능 평가  -------------------

test_predictions <- predict(titanic_glm, newdata = test_df, type = "response") >= 0.5
test_actuals <- test_df$survived == 1
accuracy <- table(test_predictions, test_actuals)
print(accuracy)
print(paste0("Accuracy: ", round(100 * sum(diag(accuracy))/sum(accuracy), 2), "%"))

# 5. 예측모형 배포 -------------------

saveRDS(titanic_glm, file = "plumber_titanic/titanic-model.rds", compress = TRUE)
```

## 생존확률 RESTful API 서비스 건강상태 체크 {#step-02-restful-api-service}

가장 먼저 R에서 개발한 `titanic-model.rds`를 가져온다. 
그리고 나서, 모형 버젼 **MODEL_VERSION**, 입력변수 **VARIABLES**, RESTful API 서비스로 제공하는 값에 대해 기술한다.

다음으로 HTTP GET 요청으로 RESTful API가 정상 동작하는지 건강상태 확인 `http://127.0.0.1:8000/healthcheck`을 가장 먼저 수행한다.


```r
library(plumber)

model <- readRDS("plumber_titanic/titanic-model.rds")

MODEL_VERSION <- "0.0.1"
VARIABLES <- list(
    pclass = "Pclass = 1, 2, 3 (Ticket Class: 1st, 2nd, 3rd)",
    sex = "Sex = male or female",
    age = "Age = # in years",
    gap = "",
    survival = "Successful submission will results in a calculated Survival Probability from 0 to 1 (Unlikely to More Likely)")


#* @get /healthcheck
health_check <- function() {
    result <- data.frame(
        "input" = "",
        "status" = 200,
        "model_version" = MODEL_VERSION
    )
    
    return(result)
}
```

<img src="fig/titanic-predictive-api-postman-healthcheck.png" alt="POSTMAN 건강상태 확인" width="100%" />

## 생존확률 RESTful API 서비스 홈페이지 {#step-02-restful-api-service-homepage}

기계와 기계 사이에 데이터를 `json` 형태로 주고 받기 때문에 불필요할 수도 있다.
하지만, 제3자가 봤을 때 혹시 필요한 경우가 있어 **방문 페이지(landing page)**를 만들어 놓는 것이 필요한 경우도 있다.
데코레이터 `@get` 아래 `@html`을 사용하게 되면 `json` 대신에 `html`을 반환하게 되어 방문 웹페이지를 깔끔하게 구축할 수 있다.


```r
#* @get /
#* @html
home <- function() {
    title <- "Titanic Survival API"
    body_intro <-  "Welcome to the Titanic Survival API!"
    body_model <- paste("We are currently serving model version:", MODEL_VERSION)
    body_msg <- paste("To received a prediction on survival probability,", 
                      "submit the following variables to the <b>/survival</b> endpoint:",
                      sep = "\n")
    body_reqs <- paste(VARIABLES, collapse = "<br>")
    
    result <- paste(
        "<html>",
        "<h1>", title, "</h1>", "<br>",
        "<body>", 
        "<p>", body_intro, "</p>",
        "<p>", body_model, "</p>",
        "<p>", body_msg, "</p>",
        "<p>", body_reqs, "</p>",
        "</body>",
        "</html>",
        collapse = "\n"
    )
    
    return(result)
}
```

<img src="fig/titanic-predictive-api-postman-landing-page.png" alt="POSTMAN 방문 페이지(landing page)" width="100%" />

## 생존확률 RESTful API 끝점(endpoint) {#step-03-restful-api-endpoint}

예측 서비스를 끝점(endpoint)을 통해서 바로 제공하기 전에 `transform_titantic_data()` 함수와 
`validate_feature_inputs()` 함수를 통해서 예측서비스 입력에 대해서 먼저 점검 작업을 수행한다.
특히, `validate_feature_inputs()` 함수는 입력 변수에 대해 논리 테스트를 수행하여 모든 것이 이상이 없다면 
"OK"를 결과값으로 반환시킨다.

`@post`, `@get` 방식으로  `/survival` 끝점을 통해서 `predict_survival` 함수로 산출된 생존확률값을 제공한다.


```r
transform_titantic_data <- function(input_titantic_data) {
    ouput_titantic_data <- data.frame(
        pclass = factor(input_titantic_data$Pclass, levels = c(1, 2, 3)),
        female = tolower(input_titantic_data$Sex) == "female",
        age = factor(dplyr::if_else(input_titantic_data$Age < 18, "child", "adult", "unknown"), 
                     levels = c("child", "adult", "unknown"))
    )
}

validate_feature_inputs <- function(age, pclass, sex) {
    age_valid <- (age >= 0 & age < 200 | is.na(age))
    pclass_valid <- (pclass %in% c(1, 2, 3))
    sex_valid <- (sex %in% c("male", "female"))
    tests <- c("Age must be between 0 and 200 or NA", 
               "Pclass must be 1, 2, or 3", 
               "Sex must be either male or female")
    test_results <- c(age_valid, pclass_valid, sex_valid)
    if(!all(test_results)) {
        failed <- which(!test_results)
        return(tests[failed])
    } else {
        return("OK")
    }
}

#* @post /survival
#* @get /survival
predict_survival <- function(Age=NA, Pclass=NULL, Sex=NULL) {
    age = as.integer(Age)
    pclass = as.integer(Pclass)
    sex = tolower(Sex)
    valid_input <- validate_feature_inputs(age, pclass, sex)
    if (valid_input[1] == "OK") {
        payload <- data.frame(Age=age, Pclass=pclass, Sex=sex)
        clean_data <- transform_titantic_data(payload)
        prediction <- predict(model, clean_data, type = "response")
        result <- list(
            input = list(payload),
            reposnse = list("survival_probability" = prediction,
                            "survival_prediction" = (prediction >= 0.5)
            ),
            status = 200,
            model_version = MODEL_VERSION)
    } else {
        result <- list(
            input = list(Age = Age, Pclass = Pclass, Sex = Sex),
            response = list(input_error = valid_input),
            status = 400,
            model_version = MODEL_VERSION)
    }
    
    return(result)
}
```

<img src="fig/titanic-predictive-api-postman-endpoint.png" alt="POSTMAN 끝점" width="100%" />

특히, 훌륭한 RESTful API를 설계하기 위한 지침을 참조하여 활용하는 것도 권장된다. [^good-restful-api-design]

[^good-restful-api-design]: [Principles of good RESTful API Design, DECEMBER 31, 2013](https://codeplanet.io/principles-good-restful-api-design/)
