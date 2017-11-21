# R 병렬 프로그래밍




## 1. OpenCPU 

[OpenCPU](https://www.opencpu.org/)는 RESTful API를 팩키지 기반으로 제공한다.

간단한 R 팩키지 개발에 대한 내용은 [R 팩키지 - 헬로우 월드](http://statkclee.github.io/data-science/r-pkg-hello-world.html)를 참조한다.



~~~{.r}
# 0. 환경설정 --------------------------------------------
# install.packages("opencpu") # OpenCPU 설치

library(opencpu)
library(devtools)

# 0.1. 예제 앱 둘러보기 ----------------------------------
# install.packages("opencpu") # OpenCPU 설치

# ocpu_start_app("rwebapps/nabel")
# ocpu_start_app("rwebapps/markdownapp")
# ocpu_start_app("rwebapps/stockapp")
# remove_apps("rwebapps/stockapp")
# remove_apps("rwebapps/markdownapp")

# 1. 오픈CPU 서버 기동 -----------------------------------
# https://stackoverflow.com/questions/44298053/r-opencpu-wont-start
# ocpu_start_server() # opencpu$start(8000) 
ocpu_start_server(8000)

browseURL("http://localhost:8000/ocpu/library/webzenr/R/mu_origin/print", browser = getOption("browser"), encodeIfNeeded = FALSE)


$ curl http://localhost:8000/ocpu/library/webzenr/R/mu_origin/json -d '{"muorg"
: "TRUE"}' -H "Content-Type: application/json"
["I love MU Origin!"]



$ curl http://localhost:8000/ocpu/library/webzenr/R/cat_function/json \
>   -d '{"love": "FALSE"}' \
>   -H "Content-Type: application/json"
["I am not a cool person."]
~~~


