# R 병렬 프로그래밍



## 웹에서 R을 돌린다. [^r-as-a-webservice]

[^r-as-a-webservice]: [How do I expose R code as a web service?](https://www.quora.com/How-do-I-expose-R-code-as-a-web-service)

웹에서 R을 돌리는 방법은 오래전부터 많이 시도되어 왔고, 이제는 안정화되었다고 봐도 될듯 싶다.

- `plumber`: [Turn your R code into a web API](https://github.com/trestletech/plumber)
- `opencpu`: [OpenCPU system for embedded scientific computation and reproducible research](https://www.opencpu.org/)
- `rapache`: [Web Application Development with R and Apache](http://rapache.net/)


> ### OpenCPU 와 다른 웹도구와 차별점 [^so-opencpu] {.callout}
>
> OpenCPU is a layer on top of the regular tools (e.g. RApache, rpy2) that defines a framework and protocol for interacting with R. 
> It handles stuff like object serialization, security, resource control, reproducibility etc, while abstracting away technicalities.

[^so-opencpu]: [What is the intention of opencpu.org compared to other approaches?
](https://stackoverflow.com/questions/8858429/whats-the-intention-of-opencpu-org-compared-to-other-approaches/8916615#8916615)

## `plumber` 팩키지

`plumber` 팩키지를 사용하게 되면 로컬컴퓨터에 웹서버를 띄워 간단하게 웹상에서 R을 사용한다는 의미를 체험하는데 최적이다. 이것이 마음에 들면
확장하여 실운영환경으로 적용해도 좋을 듯 싶다.


### 환경설치 및 R 웹서버 띄우기

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

### R 웹서버에서 제공하는 서비스

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

### 실행 사례

`curl "http://localhost:8000/mean"` 명령어를 실행시키면 `localhost`, 8000포트를 통해 `mean` 서비스가 요청되고 기본설정된 매개변수 `sample=10`이 전달되어
표준정규분포에서 표본을 10개 뽑아 평균을 계산하고 출력결과를 반환시킨다.

`curl --data '{"a":4, "b":5}' http://localhost:8000/sum` 명령어를 실행시키면 `localhost`, 8000포트를 통해 `sum` 서비스를 json 형식 데이터를 전달하여,
두값을 더한 후 결과값을 반환시킨다.



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