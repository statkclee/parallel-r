---
layout: page
title: R 병렬 프로그래밍
subtitle: R 함수형 프로그래밍
date: "2017-11-18"
output:
  html_document: 
    toc: yes
  pdf_document:
    latex_engine: xelatex
mainfont: NanumGothic
---




> ## 학습 목표 {.objectives}
>
> * 함수형 프로그래밍이 필요한 이유를 살펴본다.
> * 함수도 인자라는 것을 이해한다.
> * `purrr` 함수형 프로그래밍 기본을 이해한다.


## 1. `for` 루프 대안이 필요한 이유 [^hadley-wickham-managing-many-models] {#why-not-for-loop}

[^hadley-wickham-managing-many-models]: [Hadley Wickham: Managing many models with R, Psychology at the University of Edinburgh](https://www.youtube.com/watch?v=rz3_FDVt9eg&t=2324s)

`for` 루프는 객체와 구현 패턴을 강조하다보니 동작을 숨기게 된다. 
반면에 함수형 프로그래밍은 명사와 마찬가지로 동사도 강조하고, 구현에 대한 상세한 내용은
추상화하여 감추어 버린다. 이런 점에서 함수형 프로그래밍으로 코드를 작성하게 되면 간결하고 유지보수성이 좋아진다.
**for 루프**는 객체를 강조하는 반면 **함수형 프로그래밍**은 동작에 중점을 둔다.

> ### 함수형 프로그램 작성 순서 {.callout}
>
> 1. 전문영역지식을 활용하여 작성내용을 체계화한다.
> 1. 변수를 사용하여 정리한다.
> 1. 공통되는 코드를 뽑아낸다.

R 함수형 프로그램 작성에 Hadley Wickham이 사용하는 서양식 작은 케익(cupcake) 제작 요리법을 살펴본다.
바닐라 케이크와 쵸코 케이크 요리재료와 요리법은 거의 유사하다. 차이점이 있다면 밀가루(flour)와 코코아(cocoa)가 
큰 차이가 나고 나머지 요리법의 절차는 거의 유사하다.

<img src="fig/fp-cupcake.png" alt="컵케이크 요리법" width="87%" />

바닐라 케이크와 쵸코 케이크 조리법이 두 페이지에 걸쳐 있는데 이를 한 페이지로 줄이면 다음과 같다.
즉, 요리재료를 표준화해서 공통 요소를 뽑아내면 밀가루(flour)와 코코아(cocoa)를 바꿔 넣으면 되고,
요리법의 경우 먼저 요리법을 체계화해서 1단계 예열, 2단계 재료 섞기, 3단계 굽기로 나누고 
2단계를 좀더 상세하게 마른 재료와 젖은 재료를 섞어 혼합하는 과정으로 체계화한다.

<img src="fig/fp-cupcake-fp.png" alt="컵케이크 요리법 함수형 프로그래밍으로 전환" width="87%" />


`mtcars` 데이터셋 각변수에 대한 평균과 중위수를 계산하는 것을 살펴본다. `for` 루프를 사용하는 경우 객체와 
구현 패턴에 중점을 두게 되어 `mean`, `median` 함수명만 차이나는 `for` 루프가 두개 생성되었다.


이를 `purrr` 팩키지를 사용해서 함수형 프로그램으로 작성하면 동작에 중점을 둔 훨씬 간결한 코드가 된다.

<div class = "row">
<div class = "col-md-6">
**`for` 루프는 명사에 중점**


~~~{.r}
means <- vector("double", ncol(mtcars))

for(i in seq_along(means)) {
    means[[i]] <- mean(mtcars[[i]], na.rm=TRUE)
}
means
~~~



~~~{.output}
 [1]  20.090625   6.187500 230.721875 146.687500   3.596563   3.217250
 [7]  17.848750   0.437500   0.406250   3.687500   2.812500

~~~



~~~{.r}
medians <- vector("double", ncol(mtcars))
for(i in seq_along(mtcars)) {
    medians[[i]] <- median(mtcars[[i]], na.rm=TRUE)
}
medians
~~~



~~~{.output}
 [1]  19.200   6.000 196.300 123.000   3.695   3.325  17.710   0.000
 [9]   0.000   4.000   2.000

~~~

</div>
<div class = "col-md-6">
**함수형 프로그래밍은 동작에 중점**


~~~{.r}
library(purrr)

map_dbl(mtcars, mean)
~~~



~~~{.output}
       mpg        cyl       disp         hp       drat         wt 
 20.090625   6.187500 230.721875 146.687500   3.596563   3.217250 
      qsec         vs         am       gear       carb 
 17.848750   0.437500   0.406250   3.687500   2.812500 

~~~



~~~{.r}
map_dbl(mtcars, median)
~~~



~~~{.output}
    mpg     cyl    disp      hp    drat      wt    qsec      vs      am 
 19.200   6.000 196.300 123.000   3.695   3.325  17.710   0.000   0.000 
   gear    carb 
  4.000   2.000 

~~~
</div>
</div>


## 3. 함수형 프로그래밍 라이브러리 `purrr` {#purrr-library}

### 3.1. 함수를 데이터로 간주 {#function-is-data-as-well}

함수를 데이터로 간주하는 것도 가능하다. 함수(mean, median, sd)를 리스트로 만들어 놓고 이를 `map` 함수에 
데이터로 던져서 `mtcars` 데이터셋 각 칼럼별로 평균, 중위수, 표준편차를 구하는 것도 가능하다.


~~~{.r}
# 3. 함수를 데이터로 간주하는 것도 가능 ------------------

funs_list <- list(mean, median, sd)

map(funs_list, ~ mtcars %>% map_dbl(.x))
~~~



~~~{.output}
[[1]]
       mpg        cyl       disp         hp       drat         wt 
 20.090625   6.187500 230.721875 146.687500   3.596563   3.217250 
      qsec         vs         am       gear       carb 
 17.848750   0.437500   0.406250   3.687500   2.812500 

[[2]]
    mpg     cyl    disp      hp    drat      wt    qsec      vs      am 
 19.200   6.000 196.300 123.000   3.695   3.325  17.710   0.000   0.000 
   gear    carb 
  4.000   2.000 

[[3]]
        mpg         cyl        disp          hp        drat          wt 
  6.0269481   1.7859216 123.9386938  68.5628685   0.5346787   0.9784574 
       qsec          vs          am        gear        carb 
  1.7869432   0.5040161   0.4989909   0.7378041   1.6152000 

~~~

### 3.2. `purrr` 기초 {#purrr-basics}

함수를 인자로 넘기는 방법이 하나만 있는 것은 아니다. `sapply`, `lapply` 함수를 사용하는 방법이 많이 사용되고 있으며, 
위에서 처럼 직접 함수를 작성해도 되지만, `purrr` 팩키지를 사용하여 기능을 동일한 기능 구현을 통일하는 것도 가능하다.


~~~{.r}
sapply(df, mean)
~~~



~~~{.output}
   a    b    c    d 
 3.0 30.0  5.0  4.4 

~~~



~~~{.r}
library(purrr)
map_dbl(df, mean)
~~~



~~~{.output}
   a    b    c    d 
 3.0 30.0  5.0  4.4 

~~~

> #### `purrr` 팩키지 `map` 함수를 사용할 경우 장점{.callout}
>
> `map_dbl(.x, .f, ...)` 작업을 실행시키면 특정 벡터(`.x`)에 대한 연산작업(`.f`)을 반복해서 실행
>
> * `.x` 벡터에 대해 반복 연산작업을 수행
> * 원소 각각에 대해서 `.f` 함수 연산 작업을 수행
> * 결과를 반환

`map` 함수는 반환되는 자료형에 따라 차이가 나지만 기본적인 작동방식은 동일하다.

* `map()` : 리스트를 반환
* `map_dbl()` : double 숫자벡터를 반환
* `map_lgl()` : 부울 논리 벡터를 반환
* `map_int()` : 정수형 벡터를 반환
* `map_chr()` : 문자형 벡터를 반환

### 3.3. `purrr` `map` 함수 `.f` 지정방법 {#how-to-use-purrr}

`.f` 함수를 지정하는 다양한 방법을 살펴보면 다음과 같다.

* 기존 함수를 사용 : `map(df, summary)`
* 사용자 정의 함수를 사용 : `map(df, rescale)`
* 익명 함수를 사용 : `map(df, function(x) sum(is.na(x)))`
* 공식 단축키 함수를 사용 : `map(df, ~ sum(is.na(x)))`

`.f` 함수를 `[[`으로 원소 혹은 하위집합을 뽑아내는 경우를 살펴보자.


~~~{.r}
list_of_results <- list(
	list(a = 1, b = "A"),
	list(a = 2, b = "C"),
	list(a = 3, b = "D"))

map_dbl(list_of_results, function(x) x[["a"]])
~~~



~~~{.output}
[1] 1 2 3

~~~



~~~{.r}
map_dbl(list_of_results, "a")
~~~



~~~{.output}
[1] 1 2 3

~~~



~~~{.r}
map_dbl(list_of_results, 1)
~~~



~~~{.output}
[1] 1 2 3

~~~

`map_dbl(list_of_results, function(x) x[["a"]])` 첫번째 경우 익명함수를 사용해서 리스트명을 기준으로 뽑아낸다.
두번째 `map_dbl(list_of_results, "a")`는 문자열 명칭을 사용해서 하위집합 뽑아내기를 통해 단축키를 사용해서 뽑아낸다.
마지막, `map_dbl(list_of_results, 1)`은 정수 숫자위치를 기준으로 하위집합 뽑아내는 단축키 활용법을 보여주고 있다.

함수형 프로그래밍은 패턴을 일반화하여 추상화해서, 개발자가 데이터와 동작에 집중하게도록 한다.
이를 통해 반복문제를 좀더 쉽게 풀 수 있도록 하고, 더 이해하기 좋은 코드를 만들게 돕는다.

