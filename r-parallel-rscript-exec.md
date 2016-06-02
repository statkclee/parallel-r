---
layout: page
title: 데이터 과학
subtitle: .R 스크립트 실행
---

> ## 학습 목표 {.objectives}
>
> * 유닉스 철학을 이해한다.
> * 데이터과학 작업 파이프라인을 이해한다.
> * R스크립트를 유닉스 철학에 따라 실행한다. 

### 1. 유닉스 철학과 RScript

<img src="fig/parallel-r-pipeline.png" alt="R 파이프라인" width="70%">

통계 예측모형, 기계학습, 딥러닝 시스템을 개발할 경우 유닉스/리눅스 운영체제로 환경을 통일하고 텍스트 파일을 모든 프로그램과 시스템이 의사소통하는 기본 인터페이스로 잡고, 이를 파이프로 연결한다.

1. 텍스트 데이터로 분석에 사용될 혹은 훈련데이터로 준비한다.
1. 파이썬 혹은 쉘스크립트, R스크립트를 활용하여 전처리한다.
1. R `caret` 혹은 파이썬 `Scikit-learn` 예측모형을 적합, 기계학습 훈련, 시각화를 수행한다.
1. 마크다운(웹), LaTeX(조판) 출력형식에 맞춰 서식을 결정한다.
1. 최종 결과를 텍스트, 이미지 파일, pdf, html로 출력한다.

~~~ {.shell}
$ cat data.txt | preProcesswithPython.py | runModelwithR.R | formatOutput.sh > mlOutput.txt
~~~

> ### [유닉스 철학](https://en.wikipedia.org/wiki/Unix_philosophy) {.callout}
> 
> Write programs that do one thing and do it well. Write programs to work together. Write programs to handle text streams, because that is a universal interface. -- Doug McIlroy
> 
> * 한가지 작업만 매우 잘하는 프로그램을 작성한다(Write programs that do one thing and do it well)
> * 프로그램이 함께 동작하도록 작성한다(Write programs to work together)
> * 텍스트를 다루는 프로그램을 작성한다. 이유는 어디서나 사용되는 인터페이스가 되기 때문이다(Write programs to handle text streams, because that is a universal interface)

### 2. R 스크립트 실행환경 [^R-scripts]

[^R-scripts]: [R scripts](http://www.r-bloggers.com/r-scripts/)

유닉스/리눅스 운영체제가 준비되었다면 R스크립트 실행환경을 준비한다.

#### 2.1. R설치

R을 스크립트 형태(`.R`) 파일로 실행할 경우 가장 먼저 `r-base-core`를 설치한다. 그래픽 사용자 인터페이스가 없는 형태의 R이 설치되며 R 스크립트 실행에 필요한 연관된 프로그램도 더불어 설치한다.

~~~ {.shell}
$ sudo apt-get install -y r-base-core
~~~

#### 2.2. R 스크립트 실행환경 

R과 스크립트를 실행할 `Rscript` 실행프로그램이 위치한 디렉토리를 확인한다. 여기에 사용되는 명령어는 `which`다.
`which R` 명령어를 통해 R 실행파일이 `/usr/bin/` 디렉토리에 위치한 것을 확인할 수 있다.

~~~ {.shell}
$ which R
~~~

~~~ {.output}
/usr/bin/R
~~~

`which Rscript` 명령어를 통해 Rcript 실행파일도 `/usr/bin/` 디렉토리에 위치한 것을 확인할 수 있다.

~~~ {.shell}
$ which Rscript
~~~

~~~ {.output}
/usr/bin/Rscript
~~~

`echo $PATH` 명령어를 통해 `/usr/bin`, 경우에 따라서는 `/usr/local/bin` 디렉토리에 R과 Rscript 실행파일이 존재하는 것을 확인한다.

~~~ {.shell}
$ echo $PATH
~~~

~~~ {.output}
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
~~~

#### 2.3. R 스크립트파일 실행 

`.R` 스크립트 파일을 명령라인 인터페이스로 실행하는 방법은 다양한다. 먼저 `hello_world.R` 스크립트 파일을 생성한다.

~~~ {.r}
#! /usr/bin/env Rscript

print("Hello World!!!")
~~~

쉬뱅(shebang, #!) 다음에 스크립트를 실행할 프로그램을 지정한다. `Rscript`로 지정하여 R스크립트를 실행하는데 사용한다.

`#! /usr/bin/env Rscript`

~~~ {.shell}
$ chmod +x hello_world.R
$ ./hello_world.R
~~~

`chmod +x` 명령어를 통해서 일반 텍스트 파일을 실행가능한 파일 형식으로 지정한다.
`hello_world.R` 파일이 실행가능한 형태가 되었기 때문에 `./hello_world.R` 명령어로 R스크립트를 실행시킨다.

~~~ {.output}
Hello World!!!
~~~

#### 2.4. 기타 R 스크립트파일 실행 방법

R스크립트를 실행하는 방법은 다양하다.

~~~ {.shell}
$ R --slave -f hello_world.R
~~~ 

~~~ {.shell}
$ Rscript hello_world.R
~~~

`Rscript` 명령어로 실행을 시켜도 동일한 산출 결과가 출력된다.

~~~ {.shell}
$ R CMD BATCH hello_world.R hello_world_output.txt
~~~

`R CMD BATCH` 명령어로 실행시키면 실행결과가 `hello_world_output.txt` 파일에 저장된다. `hello_world_output.txt` 파일명을 지정하지 않으면 `hello_world.Rout` 파일에 저장된다.

~~~ {.shell}
$ R --no-save << RSCRIPT
     print("Hello World")
  RSCRIPT
~~~

`R --no-save <<` 사용법도 가능하다.

* [optparse - Command Line Option Parser](https://cran.r-project.org/web/packages/optparse/index.html)
* [argparse - Command line optional and positional argument parser](https://cran.r-project.org/web/packages/argparse/index.html)
* [getopt - C-like getopt behavior](https://cran.r-project.org/web/packages/getopt/)
