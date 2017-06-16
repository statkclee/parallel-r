# R 병렬 프로그래밍




## 1. 신용위험 API[^german-credit-api]

[^german-credit-api]: [How to create a RESTful API for a machine learning credit model in R](https://www.knowru.com/blog/how-create-restful-api-for-machine-learning-credit-model-in-r/)

훌륭한 신용위험 모형을 개발하는 것도 중요하지만, 다소 성능이 떨어지더라도 실용적으로 활용될 수 있도록 RESTful API로 
예측모형 결과를 배포하는 것도 필요하다. 이런 목적으로 다양한 R 팩키지가 개발되어 지원되고 있다.

그중 [배관공(Plumber)](https://github.com/trestletech/plumber)를 활용하여 신용위험을 알려주는 API를 개발해보자.

<img src="fig/Plumber.png" alt="배관공(plumber) 로고" width="17%" />

## 2. 신용평가 모형 개발

가장 먼저 신용평가모형 개발에 오래전부터 예제 데이터로 사용된 [독일신용데이터](https://archive.ics.uci.edu/ml/support/Statlog+(German+Credit+Data))를
신용평가모형 데이터를 활용한다.

신용평가모형은 이미 개발되었다고 가정하고 4개 변수를 중요입력변수로 가정하고,
예측모형 아케텍쳐로 의사결정나무(`rpart`) 모형을 활용하는 것으로 준비한다.

그리고, 준비된 신용평가모형이 정상적으로 동작하는지를  `predict` 함수에 신용위험을 평가할 고객 한명 데이터를 준비해서 넣는다.

- `Status of existing checking account`='A11', 
- `Duration in month`=20, 
- `Credit history`='A32', 
- `Savings account/bonds`='A65'



~~~{.r}
# 0. 환경설정 -------------------------------------
library(tidyverse)
library(rpart)

# 1. 데이터 가져오기-------------------------------

url <- "https://archive.ics.uci.edu/ml/machine-learning-databases/statlog/german/german.data"

gc_df <- read_delim(url, delim=" ", col_names =FALSE)

names(gc_df) <- c(
    'Status of existing checking account', 'Duration in month', 'Credit history', 
    'Purpose', 'Credit amount', 'Savings account/bonds', 
    'Employment years', 'Installment rate in percentage of disposable income', 
    'Personal status and sex', 'Other debtors / guarantors', 'Present residence since', 
    'Property', 'Age in years', 'Other installment plans', 'Housing', 'Number of existing credits at this bank', 
    'Job', 'Number of people being liable to provide maintenance for', 'Telephone', 'Foreign worker', 'Status'
)

# 2. 모형생성 -------------------------------------------

gc_rpart <- rpart(
    Status ~ `Status of existing checking account` + `Duration in month` + `Credit history` + `Savings account/bonds`, 
    method="class", data=gc_df)

new_data <- list(
    `Status of existing checking account`='A11', 
    `Duration in month`=20, 
    `Credit history`='A32', 
    `Savings account/bonds`='A65')

predict(gc_rpart, new_data)
          1         2
1 0.6942446 0.3057554

save.image(file="image/german_credit_plumber.RData")
~~~

## 3. 신용위험 서버 API

클라이언드 특정 고객에 대한 신용평가모형 결과를 서버쪽에서 제공하기 위한 API 코드는 다음과 같다.

즉, 예측모형 개발과 동일한 환경을 `.Rdata`에 담아 불러오고 나서,
`predict_default_rate` 함수를 `@post` `/predict` 서비스로 노출시킨다. 



~~~{.r}
# german_credit_data_api.R
# 0. 환경설정 -------------------------------------
library(tidyverse)
library(rpart)
library(jsonlite)

load("image/german_credit_plumber.RData")

#* @post /predict
predict_default_rate <- function(Status.of.existing.checking.account, Duration.in.month, Credit.history, Savings.account.bonds) {
    
    data <- list(
        `Status of existing checking account` =Status.of.existing.checking.account, 
        `Duration in month`=Duration.in.month, 
        `Credit history`=Credit.history, 
        `Savings account/bonds`=Savings.account.bonds
    )
    prediction <- predict(gc_rpart, data)
    return(list(default_probability=unbox(prediction[1, 2])))
}


## 4. 신용위험 서비스 제공

서버에 환경을 구축하고 나서 `r$run(port=8000)`를 실행하게 되면 
신용위험평가 결과를 제공하는 서비스에 대한 준비가 완료된다.
~~~

~~~{.r}
library(plumber)
r <- plumb("code/german_credit_data_api.R")
r$run(port=8000)
Starting server to listen on port 8000
Running the swagger UI at http://127.0.0.1:8000/__swagger__/
~~~

<img src="fig/german-credit-api.png" alt="신용평가서비스 API" width="97%" />

## 5. 신용위험 서비스 테스트

신용위험을 예측하는 서비스가 준비되어서 서비스로 제공되고 있다.
이에, 직접 서비스를 호출하여 결과를 받아보자.
JSON 형태 데이터를 전달하면 `/predict` 인터페이스를 통해 신용위험 예측 서비스를 제공하는 서버가 이를 받아들어 개발된 예측모형에서 미리 
산출된 로직을 통해 신용위험을 평가하여 확률값을 계산하여 이를 전달한다.


~~~{.r}
$ curl -X POST \
       -d '{"Status.of.existing.checking.account": "A11", "Duration.in.month": 24, "
Credit.history": "A32", "Savings.account.bonds": "A63"}' \
       -H 'Content-Type: application/json' \
       localhost:8000/predict
{"default_probability":0.6224}
~~~