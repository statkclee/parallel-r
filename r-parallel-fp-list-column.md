---
layout: page
title: 데이터 과학
subtitle: 리스트 칼럼(list-column) 자료형
output:
  html_document: 
    keep_md: yes
  pdf_document:
    latex_engine: xelatex
mainfont: NanumGothic
---




> ## 학습 목표 {.objectives}
>
> * 리스트 칼럼(list-column) 자료형에 대해 이해한다.
> * R 자료형을 레고블록을 통해 이해한다.


## 1. 리스트 칼럼 [^jennybc-purrr-list-columns] 

[^r-lego-data-structure]: [Photos that depict R data structures and operations via Lego](https://github.com/jennybc/lego-rstats)

### 1.1 레고를 통해 본 R 자료 구조 [^r-lego-data-structure]

[^jennybc-purrr-list-columns]: [List columns](https://jennybc.github.io/purrr-tutorial/ls13_list-columns.html)

레고를 통해 살펴본 R 자료구조는 계산가능한 원자 자료형(논리형, 숫자형, 요인형)으로 크게 볼 수 있다. 
R에서 정수형과 부동소수점은 그다지 크게 구분을 하지 않는다. 동일 길이를 갖는 벡터를 쭉 붙여넣으면 자료구조형이 
**데이터프레임**으로 되고, 길이가 갖지 않는 벡터를 한 곳에 모아넣은 자료구조가 **리스트**다.

데이터프레임이 굳이 모두 원자벡터만을 갖출 필요는 없다. 리스트를 데이터프레임 내부에 갖는 것도 
데이터프레임인데 굳이 구별하자면 티블(`tibble`)이고, 이런 자료구조를 **리스트-칼럼(list-column)**이라고 부른다.

<img src="fig/data-structure-list-column.png" alt="리스트 칼럼" width="97%" />

리스트-칼럼 자료구조가 빈번히 마주하는 경우가 흔한데... 대표적으로 다음 사례를 들 수 있다.

- 정규표현식을 통한 텍스트 문자열 처리
- 웹 API로 추출된 JSON, XML 데이터
- 분할-적용-병합(Split-Apply-Combine) 전략 

데이터프레임이 티블(tibble) 형태로 되어 있으면 다음 작업을 나름 수월하게 추진할 수 있다.

- **들여다보기(Inspect)**: 데이터프레임에 무엇이 들었는지 확인.
- **인덱싱(Indexing)**: 명칭 혹은 위치를 확인해서 필요한 원소를 추출.
- **연산(Compute)**: 리스트-칼럼에 연산 작업을 수행해서 또다른 벡터나 리스트-칼럼을 생성.
- **간략화(Simplify)**: 리스트-칼럼을 익숙한 데이터프레임으로 변환.
