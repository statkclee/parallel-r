---
layout: page
title: 데이터 과학
subtitle: R 함수 작성
output:
  html_document: 
    keep_md: yes
  pdf_document:
    latex_engine: xelatex
mainfont: NanumGothic
---




> ## 학습 목표 {.objectives}
>
> * 함수를 작성하는 이유와 함수작성법을 살펴본다.
> * 좋은 함수는 어떤 함수인지 살펴본다.

### 1. 함수를 작성하는 이유

함수를 작성하는 이유는 반복되는 중복 문제를 해결하고 추상화를 통해 더 복잡한 작업을 가능하게 만들기 위해 사용한다.
데이터프레임에 담긴 변수의 측도가 상이하여 측도를 재조정하는 경우 다음과 같은 수학식이 많이 사용된다.
즉, 최대값과 최소값을 빼서 분모에 놓고 분자에 최소값을 빼고 나누면 0--1 사이 값으로 척도를 재조정하게 된다.

$$ f(x)_{\text{척도조정}} = \frac{x-min(x)}{max(x)-min(x)} $$



~~~{.r}
df <- data.frame(a=c(1,2,3,4,5),
				 b=c(10,20,30,40,50),
				 c=c(7,8,6,1,3),
				 d=c(5,4,6,5,2))
df$a <- (df$a - min(df$a, na.rm = TRUE)) /
        (max(df$a, na.rm = TRUE) - min(df$a, na.rm = TRUE))
df$b <- (df$b - min(df$b, na.rm = TRUE)) /
        (max(df$a, na.rm = TRUE) - min(df$b, na.rm = TRUE))
df$c <- (df$c - min(df$c, na.rm = TRUE)) /
        (max(df$c, na.rm = TRUE) - min(df$c, na.rm = TRUE))
df$d <- (df$d - min(df$d, na.rm = TRUE)) /
        (max(df$d, na.rm = TRUE) - min(df$d, na.rm = TRUE))
df        
~~~



~~~{.output}
     a         b         c    d
1 0.00  0.000000 0.8571429 0.75
2 0.25 -1.111111 1.0000000 0.50
3 0.50 -2.222222 0.7142857 1.00
4 0.75 -3.333333 0.0000000 0.75
5 1.00 -4.444444 0.2857143 0.00

~~~

상기 R 코드는 측도를 모두 맞춰서 변수 4개(`a`, `b`, `c`, `d`)를 비교하거나 향후 분석을 위한 것이다. 
하지만, 읽어야 되는 코드가 중복되고 길어 코드를 작성한 개발자의 **의도** 가 의도적이지는 않지만 숨겨졌다.

그리고, R 코드에 실수한 것이 그냥 남게 되어 다음 프로그램 실행에서 버그(특히, 구문론이 아닌 의미론적 버그)가 숨겨지게 된다. 즉, 상기 코드가 만들어 지는 과정을 살펴보면 이해가 쉽게된다.

1. `df$a <- (df$a - min(df$a, na.rm = TRUE)) / (max(df$a, na.rm = TRUE) - min(df$a, na.rm = TRUE))` 코드를 작성한 후,
정상적으로 돌아가는지 확인한다.
1. 1번 코드가 잘 동작하게 되면 다음 복사하여 붙여넣기 신공을 사용하여 다른 칼럼 작업을 확장해 나간다. `df$b`, `df$c`, `df$d`를 생성하게 된다.
1. 즉, 복사해서 붙여넣은 것을 변수명을 편집해서 `df$b`, `df$c`, `df$d` 변수를 순차적으로 생성해 낸다.

> ### 위캠 어록 {.callout}
>
> * Duplication hides the intent
> * If you have copied-and-pasted twice, it's time to write a function

### 2. 함수를 작성하는 시점

복사해서 붙여넣는 것을 두번 하게 되면, 함수를 작성할 시점이다. 중복을 제거하는 한 방법은 함수를 작성하는 것이다.
함수를 작성하게 되면 의도가 명확해진다.
함수명을 `rescale`로 붙이고 이를 실행하게 되면, 의도가 명확하게 드러나게 되고, 복사해서 붙여넣게 되면서 
생겨나는 중복과 반복에 의한 실수를 줄일 수 있게 되고, 향후 코드를 갱신할 때도 도움이 된다.



~~~{.r}
rescale <- function(x){
              rng <- range(x, na.rm = TRUE)
              (x - rng[1]) / (rng[2] - rng[1])
            }

df$a <- rescale(df$a)
df$b <- rescale(df$b)
df$c <- rescale(df$c)
df$d <- rescale(df$d)
~~~

또다른 방법은 함수형 프로그래밍을 사용하는 것으로 함수명을 반복적으로 사용하는 것조차도 피할 수 있다.



~~~{.r}
library(purrr)
df[] <- map(df, rescale)
~~~

### 3. 함수를 작성하는 방법

함수를 작성할 경우 먼저 매우 단순한 문제에서 출발한다.
척도를 맞추는 상기 과정을 R 함수로 만들어본다. 

1. 입력값과 출력값을 정의한다. 즉, 입력값이 `c(1,2,3,4,5)` 으로 들어오면 출력값은 
`0.00 0.25 0.50 0.75 1.00` 0--1 사이 값으로 나오는 것이 확인되어야 하고, 각 원소값도
출력벡터 원소값에 매칭이 되는지 확인한다.

2. 기능이 구현되어 동작이 제대로 되는지 확인되는 R코드를 작성한다. 


~~~{.r}
(df$a - min(df$a, na.rm = TRUE)) / (max(df$a, na.rm = TRUE) - min(df$a, na.rm = TRUE))
~~~

3. 확장가능하게 임시 변수를 사용해서 위에서 구현된 코드를 다시 작성한다. 


~~~{.r}
( x - min( x , na.rm = TRUE)) / (max( x , na.rm = TRUE) - min( x , na.rm = TRUE))
~~~


~~~{.r}
x <- df$a
( x - min( x , na.rm = TRUE)) / (max( x , na.rm = TRUE) - min( x , na.rm = TRUE))
~~~

4. 함수 작성의도를 명확히 하도록 다시 코드를 작성한다.


~~~{.r}
x <- df$a
rng <- range(x, na.rm = TRUE)
(x - rng[1]) / (rng[2] - rng[1])
~~~

5. 최종적으로 재작성한 코드를 함수로 변환한다.


~~~{.r}
x <- df$a

rescale <- function(x){
				rng <- range(x, na.rm = TRUE)
				(x - rng[1]) / (rng[2] - rng[1])
			}

rescale(x)
~~~

### 4. 좋은 함수

좋은 함수를 작성하려면 다음과 같은 조건이 만족되어야 한다.

1. 함수와 인자에 대해 유의미한 명칭을 사용한다.
    * 함수명에 적절한 동사명을 사용한다.
1. 직관적으로 인자를 배치하고 기본디폴트값에도 추론가능한 값을 사용한다.
1. 함수가 인자로 받아 반환하는 것을 명확히 한다.
1. 함수 내부 몸통부문에 좋은 스타일을 잘 사용한다.


> ### 좋은 함수란? {.callout}
>
> 척도를 일치시키는 기능을 함수로 구현했지만, 기능을 구현했다고 좋은 함수가 되지는 않는다.
> 좋은 함수가 되는 조건은 다음과 같다.
>
> 1. **Correct:** 기능이 잘 구현되어 올바르게 동작할 것
> 1. **Understandable:** 사람이 이해할 수 있어야 함. 즉, 함수는 컴퓨터를 위해 기능이 올바르게 구현되고, 사람도 이해할 수 있도록 작성되어야 한다.
> 1. 즉, **Correct + Understandable:** 컴퓨터와 사람을 위해 적성될 것.




