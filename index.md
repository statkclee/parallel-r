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

1. **고성능 아키텍쳐와 성능측정**
    - [기계학습 - 기술부채(Technical Debt)](http://statkclee.github.io/ml/ml-technical-debt.html)
    - [고성능 R 아키텍처](r-perf-arch.html)
        - [왜 고성능 R 아키텍처가 필요한가?](why-r-hpc.html)
        - [R 스케일-업 성능향상](r-scale-up.html)
        - [Rcpp - 코드 최적화](r-perf-rcpp.html)
        - [R 스케일-아웃 성능향상 - 병렬처리](r-scale-out.html)     
            - [뉴욕타임즈 기사 병렬처리 사례](r-scale-out-nytimes.html)
            - [진행상태 표시 막대 - `progressr`](parallel-progressr.html)         
    - **[고성능 R코드 작성과 성능비교](perf-writing-efficient-code.html)**
        - [R 코드 성능 측정기준 - 벤치마킹](perf-benchmark.html)
        - [프로파일링(profiling) 팩킺 - `profviz`](performance-profiling.html)
        - [프로파일링(Profiling)을 통한 성능향상](performance-profviz.html)    
1. **[기계학습 R 서버 만들기](r-caret-parallel-server.html)**    
1. **[배포(deployment) = 기계학습 모형 사용](r-restful-production.html)**
    - [RESTful API 개발환경 - `plumber`](r-restful-api-test.html)
        1. [HTTP API - Straw man 버전(결혼)](r-restful-api-on-aws-strawman.html)
        1. [HTTP API - Stone man 버전(admission)](r-restful-api-on-aws-stoneman.html)
        1. [HTTP API - Iron man 버전](r-restful-api-on-aws-ironman.html)        
    - [왜 GLM인가?](r-deployment-glm.html)
        + [AWS RESTful API 서버](r-restful-api-on-aws.html)
    - [예측모형 데이터베이스(DBMS) 배포](r-database-tidypredict.html) 
    - [R 양산환경(`plumber`) - 타이타닉](r-in-production-plumber.html)    
    - [신용위험 확률(plumber) API](r-credit-score-api.html)    
    - [TV 시청시간 예측서비스 - 데이터는 openCPU, 구현은 plumber, 서비스는 AWS](r-gss-tvhours.html)
1. **자동화(Automation)**
    - [R 자동화(Make) - `drake`](r-makefile.html)
        - [소프트웨어 카펜트리 자동화 Make(소프트웨어)](http://statkclee.github.io/make-novice/index-kr.html)
        - [R과 Make(소프트웨어+R) - TV 토론 효과](r-make-software.html)
        - [STAT545 자동화 - Make](r-stat545-make.html)
1. [**함수형 프로그래밍(Functional Programming)**](ds-fp.html)
    - [R 함수 작성](ds-fp-write-fn.html)
    - [R 함수형 프로그래밍](ds-fp-purrr.html)
        - [시군 인구증가(2005-2016)](ds-fp-population-by-sigun.html)
    - [FP 자료구조 - 리스트 칼럼(list-column)](r-parallel-fp-ds.html)
        - [리스트 자료형 살펴보기](r-parallel-fp-view-list.html)
        - [리스트 자료 원소 추출하기](r-parallel-fp-extract-list.html)
        - [트럼프 트윗](r-parallel-fp-trump-tweet.html)
    - [병렬 데이터 처리 - multidplyr](r-multidplyr.html)
    - [멀티코어 병렬 프로그래밍 - doParallel](r-doparallel.html)
    - **왕좌의 게임(Game of Thrones) - 데이터 사각화(Data Rectangling)**
    	- [GoT 데이터](r-parallel-got-data.html)
    	- [GoT 데이터 - 데이터 정제](r-parallel-got-wrangling.html)
    - [열이 아닌 행(row) 데이터 조작](r-rowwise-wrangling.html)
    - [데이터 과학 기본 프로그래밍](programming-ds-basic.html)
1. [`purrr` &rarr; `furrr`](r-parallel-furrr.html)
    - [분할-적용-병합(Split-Apply-Combine) 전략](r-parallel-split-apply-combine.html)
1. [추천 시스템(Recommendation System)](recommendation-sys.html)
    - [영화진흥위원회 오픈API - 스크린수와 매출](kofic-movie-api.html)
    - [추천 시스템(Recommendation System) - 비개인화 추천(Nonpersonal Recommendation)](recommendation-nonpersonal.html)
    - [추천 시스템(Recommendation System) - 콘텐츠기반 필터링 추천(Content-based Filtering Recommendation)](recommendation-content-based-filtering.html)
    - [추천 시스템(Recommendation System) - 사용자기반 협업 필터링(User-based Collaborative Filtering)](recommendation-user-based-filtering.html)
    - [추천 시스템(Recommendation System) - 탐색적분석과 모형선정](recommendation-implementation.html)
    - [`sparklyr` 추천시스템 - MovieLens](recommendation-sparklyr.html)

> ### xwMOOC는 수학을 사랑합니다. {.prereq}
> 
> 2차 방정식 $a x^2 + b x + c = 0$ 에 대한 해답은 ...
>
> $$x = \frac{-b \pm \sqrt{b^2 - 4 a c}}{2 a}$$ 



### xwMOOC 오픈 교재

- [컴퓨터 과학 언플러그드](http://statkclee.github.io/unplugged)  
- [리보그](http://reeborg.xwmooc.org)  
     - [러플](http://rur-ple.xwmooc.org)  
- [파이썬 거북이](http://swcarpentry.github.io/python-novice-turtles/index-kr.html)  
- [정보과학을 위한 파이썬](http://python.xwmooc.org)  
- [소프트웨어 카펜트리 5.3](http://swcarpentry.xwmooc.org)
- [IoT 오픈 하드웨어(라즈베리 파이)](http://statkclee.github.io/raspberry-pi)
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
- [선거와 투표](http://statkclee.github.io/politics)

