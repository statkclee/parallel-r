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


<img src="fig/paralle-r-pipeline.png" alt="R 파이프라인" width="70%">

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




* [optparse - Command Line Option Parser](https://cran.r-project.org/web/packages/optparse/index.html)
* [argparse - Command line optional and positional argument parser](https://cran.r-project.org/web/packages/argparse/index.html)
* [getopt - C-like getopt behavior](https://cran.r-project.org/web/packages/getopt/)
