---
layout: page
title: R 병렬 프로그래밍
---

<img src="fig/ct-unplugged-4th-paradigm-korea.png" width="57%" />

> ### AI is a Superpower {.callout}
>
> "AI is a superpower!!!", 인공지능을 체득하면 슈퍼파워를 손에 쥘 것이다. [Andrew Ng](https://twitter.com/andrewyng/status/728986380638916609)
>
> 금수저, 은수저 슈퍼파워를 받은 사람과 기계학습을 통달한 흑수저들간의 무한경쟁이 드뎌 시작되었다. 물론, 
> 금수저를 입에 물고 기계학습을 통달한 사람이 가장 유리한 출발을 시작한 것도 사실이다.

## 학습목차 

1. [고성능 R 아키텍처](r-perf-arch.html)
    - [왜 고성능 R 아키텍처가 필요한가?](why-r-hpc.html)
    - [R 스케일-업 성능향상](r-scale-up.html)
    - [R 스케일-아웃 성능향상](r-scale-out.html)     
        - [뉴욕타임즈 기사 병렬처리 사례](r-scale-out-nytimes.html) 
1. **R코드 자동화**
    - [유닉스 철학과 파이프라인](r-parallel-rscript-unix.html)
    - [`.R` 스크립트 실행](r-parallel-rscript-exec.html)
    - [`.R` 스크립트를 인자와 함께 실행](r-parallel-rscript-args.html)
    - [`optparse` 파이썬 스타일](r-parallel-rscript-optparse.html)
    - [분석결과 내보내기](r-parallel-local-export.html)
1. [재현가능한 과학연구를 위한 도커](http://statkclee.github.io/r-docker/) 
    - [도커는 무엇이고 왜 사용하나](http://statkclee.github.io/r-docker/01-what-and-why.html)
    - [도커 실행](http://statkclee.github.io/r-docker/02-Launching-Docker.html)
    - [팩키지 설치](http://statkclee.github.io/r-docker/03-install-packages.html) 
    - [도커허브(Dockerhub)](http://statkclee.github.io/r-docker/04-Dockerhub.html)
    - [도커파일(Dockerfiles)](http://statkclee.github.io/r-docker/05-dockerfiles.html)
    - [분석결과 공유](http://statkclee.github.io/r-docker/06-Sharing-all-your-analysis.html)
1. **성능 측정과 비교**
    - [정보수집 프로파일링(profiling) - profviz](performance-profiling.html)
    - [정보수집 프로파일링을 통한 성능향상](performance-profviz.html)
    - [성능 측정기준 벤치마킹](perf-benchmark.html)
1. **빅데이터**
    - [RStudio 빅데이터 전략](big-data-strategy.html)
    - [SparkR 설치](spark-hadoop-install.html)

## 왜 R 언어인가? [^r-rank] [^r-r4stats]

[Rexer Analytics](http://www.rexeranalytics.com/)가 2015년 응답자 1,220명을 대상으로 실시한 결과 R이 데이터 분석 소프트웨어 분야에서 압도적인 1위 위치를 점유하고 있음을 확인할 수 있다.

[^r-rank]: [Interactive-The Top Programming Languages](http://spectrum.ieee.org/static/interactive-the-top-programming-languages#index)

[^r-r4stats]: [The Popularity of Data Analysis Software](http://r4stats.com/articles/popularity/)


| | |
|-----------------------------------|-----------------------------------|
|<img src="fig/rexersurveyalltools2015.png" alt="Rexer Analytics 설문조사 2015 (응답자 1,220)" width="70%"> | <img src="fig/ieee-r-ranking.png" alt="IEEE 조사" width="70%">



> ### xwMOOC는 수학을 사랑합니다. {.prereq}
> 
> 2차 방정식 $a x^2 + b x + c = 0$ 에 대한 해답은 ...
>
> $$x = \frac{-b \pm \sqrt{b^2 - 4 a c}}{2 a}$$ 


> ### 가장최신 R 설치 [^r-latest-install] {.callout}
> 
> ~~~ {.shell}
> $ codename=$(lsb_release -c -s)
> $ echo "deb http://cran.fhcrc.org/bin/linux/ubuntu $codename/" | sudo tee -a /etc/apt/sources.list > /dev/null
> $ sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys E084DAB9
> $ sudo add-apt-repository ppa:marutter/rdev
> $ sudo apt-get update
> $ sudo apt-get upgrade
> $ sudo apt-get install r-base r-base-dev
> ~~~

[^r-latest-install]: [How to install latest version of R on Ubuntu 12.04 LTS?](http://askubuntu.com/questions/614530/how-to-install-latest-version-of-r-on-ubuntu-12-04-lts)

### R 팩키지 설치 [^r-packages-install]

[^r-packages-install]: [How should I deal with “package 'xxx' is not available (for R version x.y.z)” warning?](http://stackoverflow.com/questions/25721884/how-should-i-deal-with-package-xxx-is-not-available-for-r-version-x-y-z-wa)


### xwMOOC 오픈 교재

- [컴퓨터 과학 언플러그드](http://unplugged.xwmooc.org)  
- [리보그](http://reeborg.xwmooc.org)  
     - [러플](http://rur-ple.xwmooc.org)  
- [파이썬 거북이](http://swcarpentry.github.io/python-novice-turtles/index-kr.html)  
- [정보과학을 위한 파이썬](http://python.xwmooc.org)  
- [소프트웨어 카펜트리 5.3](http://swcarpentry.xwmooc.org)
- [IoT 오픈 하드웨어(라즈베리 파이)](http://raspberry-pi.xwmooc.org/)
    - [$100 오픈 컴퓨터](http://computer.xwmooc.org/)   
    - [$100 오픈 슈퍼컴퓨터](http://computers.xwmooc.org/)
- **데이터 과학**
    - [R 데이터과학](http://data-science.xwmooc.org/)
    - [R 팩키지](http://r-pkgs.xwmooc.org/)
    - [R 도커](http://statkclee.github.io/r-docker/)
    - [통계적 사고](http://think-stat.xwmooc.org/)
- **기계학습, 딥러닝, 인공지능**
    - [기계학습](http://statkclee.github.io/ml)
    - [고생대 프로젝트](http://statkclee.github.io/trilobite)
- [기호 수학(Symbolic Math)](http://sympy.xwmooc.org/)
- [선거와 투표](http://politics.xwmooc.org/)

