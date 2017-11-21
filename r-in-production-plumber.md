---
layout: page
title: R 병렬 프로그래밍
date: "2017-11-21"
subtitle: R 양산환경(`plumber`) - 타이타닉
output:
  html_document: 
    toc: yes
  pdf_document:
    latex_engine: xelatex
mainfont: NanumGothic
---


## 1. 양산환경 R [^r-as-a-webservice] {#r-in-production}

[^r-as-a-webservice]: [How do I expose R code as a web service?](https://www.quora.com/How-do-I-expose-R-code-as-a-web-service)

웹에서 R을 돌리는 방법은 오래전부터 많이 시도되어 왔고, 이제는 안정화되었다고 봐도 될듯 싶다. 
한동안 `opencup`가 많이 사용되어 왔으나 팩키지를 만들어야 기본적으로 R을 양산환경에 돌릴 수 있다는 
부담감(?)으로 작용하는 것도 사실이다. 최근에는 `plumber`

- `plumber`: [Turn your R code into a web API](https://github.com/trestletech/plumber)
- `opencpu`: [OpenCPU system for embedded scientific computation and reproducible research](https://www.opencpu.org/)
    -  팩키지를 개발하고 이를 RESTful API 서비스로 제공.
- `deployR`: [The elements of scaling R-based applications with DeployR](http://blog.revolutionanalytics.com/2016/09/the-elements-of-scaling-r-based-applications-with-deployr.html)
    - 마이크로소프트에서 개발하여 제공.
- `rapache`: [Web Application Development with R and Apache](http://rapache.net/)
    - 오래전에 개발된 후에 더이상 활발히 개발이 진행되고 있지 않는 것으로 파악됨.


> ### OpenCPU 와 다른 웹도구와 차별점 [^so-opencpu] {.callout}
>
> OpenCPU is a layer on top of the regular tools (e.g. RApache, rpy2) that defines a framework and protocol for interacting with R. 
> It handles stuff like object serialization, security, resource control, reproducibility etc, while abstracting away technicalities.

[^so-opencpu]: [What is the intention of opencpu.org compared to other approaches?
](https://stackoverflow.com/questions/8858429/whats-the-intention-of-opencpu-org-compared-to-other-approaches/8916615#8916615)

## 2. `plumber` 팩키지 맛보기 {#intro-to-plumber}

`plumber` 팩키지를 사용하게 되면 로컬컴퓨터에 웹서버를 띄워 간단하게 웹상에서 R을 사용한다는 의미를 체험하는데 최적이다. 
이것이 마음에 들면 확장하여 실운영환경으로 적용해서 최근 활발히 사용하고 있다.


### 2.1. 환경설치 및 R 웹서버 띄우기 {#config-webserver-plumber}

`devtools::install_github("trestletech/plumber")` 명령어로 R 웹서버를 띄우고 나서,
`myfile.R`에 웹서버를 통해 노출할 함수를 지정하면 된다. 그리고 나서 `r$run(port=8000)` 명령어를 실행하면 실제로 웹서버에 
노출한 함수를 곧바로 활용할 수 있다.


```r
devtools::install_github("trestletech/plumber")

library(plumber)

r <- plumb("code/myfile.R") 
r$run(port=8000)
Starting server to listen on port 8000
Running the swagger UI at http://127.0.0.1:8000/__swagger__/
```

### 2.2. R 웹서버에서 제공하는 서비스 {#plumber-services}

`@get`, `@post` 두가지 사례를 `normalMean`, `addTwo` 함수를 `mean`, `sum`을 통해 서비스로 제공하고 있다.


```r
#* @get /mean
normalMean <- function(samples=10){
    data <- rnorm(samples)
    mean(data)
}

#* @post /sum
addTwo <- function(a, b){
    as.numeric(a) + as.numeric(b)
}
```

### 2.3. 실행 사례 {#plumber-in-service}

`curl "http://localhost:8000/mean"` 명령어를 실행시키면 `localhost`, 8000포트를 통해 `mean` 서비스가 요청되고, 
기본설정된 매개변수 `sample=10`이 전달되어 표준정규분포에서 표본을 10개 뽑아 평균을 계산하고 출력결과를 반환시킨다.

`curl --data '{"a":4, "b":5}' http://localhost:8000/sum` 명령어를 실행시키면 `localhost`, 
8000포트를 통해 `sum` 서비스를 json 형식 데이터를 전달하여, 두값을 더한 후 결과값을 반환시킨다.



```r
$ curl "http://localhost:8000/mean"
[-0.6062]
$ curl "http://localhost:8000/mean?samples=1000"
[-0.0021]
$  curl --data "a=4&b=3" "http://localhost:8000/sum"
[7]
$ curl --data '{"a":4, "b":5}' http://localhost:8000/sum
[9]
```

## 3. 타이타닉 생존 확률 예측 서비스 [^titanic-plumber-api]

[^titanic-plumber-api]: [raybuhr blog, Making Predictions over HTTP with R October 17, 2017](https://raybuhr.github.io/2017/10/making-predictions-over-http/)


