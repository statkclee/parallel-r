# R 병렬 프로그래밍




## 1. RESTful API 테스트 [^plumber-restful-api-earl-2015]

[^plumber-restful-api-earl-2015]: [PLUMBER - TURN R CODE INTO WEB APIS, Jeff Allen @trestleJeff](https://plumber.trestletech.com/components/earl-2015/)

R 코드를 RESTful API 서비스로 제공하고자 할 경우 정말 훌륭한 서비스를 만드는 것도 중요하지만, 
결국 시작은 헬로월드를 찍는 것부터 시작된다. 즉, RESTful API로 개발된 결과물을 빨리 확인할 수 있는 통합개발환경이 중요한 역할을 담당하게 된다.

## 2. 헬로월드

가장 먼저 `hello_world` 함수를 `/hello_world` 서비스로 제공한다.
`httr` 팩키지 `GET` 함수를 활용하여 웹브라우져를 열어 테스트하는 대신 RStudio 개발환경에서 일원화하여 개발속도를 가속시킨다.

### 2.1. 헬로월드 서비스 코드


~~~{.r}
#* @get /hello_world
hello_world <- function() {
    return("안녕하세요... 반갑습니다.")
}
~~~

### 2.2. 헬로월드 서비스 호출 및 테스트 


~~~{.r}
# 0. 환경설정 ---------------------------------
#library(httr)
#library(tidyverse)

# 1. 헬로 월드: GET ---------------------------------
GET("http://localhost:8000/hello_world") %>% 
    content()
~~~



~~~{.output}
[[1]]
[1] "ok"

~~~

## 3. 매개변수 넘기는 경우

단순히 서비스를 호출하는 대신에 인증을 위해 `ID`, `비밀번호`등을 넘기는 경우도 흔하다.
이런 경우 인자를 넘기는 방식이 다양하다.
POST를 전통적으로 `?`로 시작해서 인자를 넘긴다고 지정하고 다수 매개변수를 넘길 때 매개변수를 `&`로 구분해서 넘긴다.

혹은 POST 내부 인자로 `query`를 사용해서 `list` 자료형으로 넘기는 것도 가능하고,
`path`에 지정하는 것도 가능하다.

### 3.1. 매개변수 넘기는 API  


~~~{.r}
#* @post /sum_two
plus_operation <- function(a, b) {
    return(list(result = as.numeric(a) + as.numeric(b)))
}

#* @get /iris/<sp>/<n:int>
function(n, sp) {
    iris %>% dplyr::filter(Species == sp) %>% 
        .[as.integer(n), ]
}
~~~

### 3.2. 매개변수 넘기는 API 테스트 



~~~{.r}
# 2. 매개변수 넘기기: POST ---------------------------------
## 2.1. 매개변수 2개 넘겨 더하기
POST("http://localhost:8000/sum_two?a=1&b=2") %>% 
    content()
~~~



~~~{.output}
$result
$result[[1]]
[1] 3

~~~



~~~{.r}
POST("http://localhost:8000/sum_two", query=list(a=1, b=3)) %>% 
    content()
~~~



~~~{.output}
$result
$result[[1]]
[1] 4

~~~



~~~{.r}
## 2.2. 깔끔한 매개변수 넘기기
GET("http://localhost:8000", path = "iris/virginica/3") %>% 
    content()
~~~



~~~{.output}
[[1]]
[[1]]$Sepal.Length
[1] 7.1

[[1]]$Sepal.Width
[1] 3

[[1]]$Petal.Length
[1] 5.9

[[1]]$Petal.Width
[1] 2.1

[[1]]$Species
[1] "virginica"

~~~

## 4. 그래프 

### 4.1. 그래프 시각화를 하는 API  

R의 강점인 그래프도 가능하다.


~~~{.r}
#* @get /ggplot2_density
#* @png

ggp2dens <- function(seed = rnorm(1), fill.colour = "tomato", alpha = 1) {
    library(ggplot2)
    set.seed(seed)
    p <- data.frame(x = rnorm(100)) %>% ggplot(aes(x)) + 
        geom_density(fill = fill.colour, alpha = alpha)
    print(p)
}
~~~

### 4.2. 그래프 시각화를 하는 API  테스트


~~~{.r}
# 3. 그래프 ---------------------------------
plot(0:1, 0:1, type = "n")
GET("http://localhost:8000/ggplot2_density?seed=77&fill.colour=tomato&alpha=0.5") %>% 
    content() %>% rasterImage(0, 0, 1, 1)
~~~

<img src="fig/plumber-restful-api-graph-test-1.png" style="display: block; margin: auto;" />

## 5. JSON 파일을 인자로 넘기는 경우

### 5.1. JSON 형태로 매개변수를 넘기는 API코드와 데이터

인자를 JSON 파일형태로 지정하여 파일로 넘기는 경우 인자를 JSON으로 정리한다.

> ### data.json {.callout}
>
> `data.json` 파일에 담기는 데이터 세부내용은 다음과 같다.
> 
> 
> `{"Status.of.existing.checking.account": "A11", "Duration.in.month": 12, "Credit.history": "A32", "Savings.account.bonds": "A63"}`


~~~{.r}
#* @post /predict
predict.default.rate <- function(
    Status.of.existing.checking.account
    , Duration.in.month
    , Credit.history
    , Savings.account.bonds
) {
    data <- list(
        Status.of.existing.checking.account=Status.of.existing.checking.account
        , Duration.in.month=Duration.in.month
        , Credit.history=Credit.history
        , Savings.account.bonds=Savings.account.bonds
    )
    prediction <- predict(decision.tree, data)
    return(list(default.probability=unbox(prediction[1, 2])))
}
~~~

### 5.2. JSON 형태 파일을 받는 API 테스트 


~~~{.r}
# 4. 파일 ---------------------------------
## 4.1. JSON 파일: 레코드 1개
# curl --data "@data.json" localhost:8000/predict

POST("http://localhost:8000/predict", body=upload_file("data.json")) %>%
    content()
~~~



~~~{.output}
$default.probability
[1] 0.3058

~~~