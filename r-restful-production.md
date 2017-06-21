# R 병렬 프로그래밍



<img src="fig/api-plumber-api.png" alt="R RESTful API 개발환경" width="57%" />

## 1. 로컬 컴퓨터 RESTful API 서비스

예를 들어 `plumber`를 RESFtul API 기본 서버로 지정하는 경우 로컬컴퓨터에서 `httr` 팩키지가 지원하는 `GET`, `POST` 함수를 
활용하여 `plumber` 팩키지가 R 코드를 서비스로 제공하도록 개발환경을 구축한다.

로컬 컴퓨터에 `plumber` 개발환경을 구축하는 방법은 다음과 같다.

`devtools::install_github("trestletech/plumber")` 명령어로 R코드를 RESTful API로 제공하는 팩키지를 설치한다.
제공할 서비스를 `myfile.R` 파일에 담아 넣고 `POST`, `GET`으로 서비스를 명세한다.
`r$run(port=8000)` 명령어를 실행해서 `myfile.R` 파일에 담아 놓은 서비스를 RESTful API로 제공한다.


~~~{.r}
devtools::install_github("trestletech/plumber")

library(plumber)

r <- plumb("code/myfile.R") 
r$run(port=8000)
Starting server to listen on port 8000
Running the swagger UI at http://127.0.0.1:8000/__swagger__/
~~~


## 2. AWS EC2 RESTful API 서비스 

로컬 컴퓨터에 RESTful API 서비스를 개발하여 테스트를 마무리했다면, 로컬 컴퓨터에 가상컴퓨터를 생성하거나,
클라우드에 예를 들어 AWS EC2 컴퓨터에 `plumber` 팩키지를 설치하여 RESTful API 서비스를 제공하도록 탈바꿈 한다.




