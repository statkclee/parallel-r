---
layout: page
title: 데이터 과학
subtitle: optparse` 파이썬 스타일
---

> ## 학습 목표 {.objectives}
>
> * `optparse` 파이썬 스타일을 사용해서 동일한 문제를 푼다.

### 파이썬 `optparse` 스타일 

`commandArgs`를 사용해서 인자를 받는 R스크립트를 실행하는 방법이 전통적인 방법이라면,
`optparse` 파이썬 라이브러리를 R에서 사용하여 동일한 작업을 수행한다.

`make_option`을 통해 명령라인 인터페이스에 들어갈 인자를 설정한다. 
그리고, `optparse`에서 설정한 인자값을 R코드에서 받아 명령어를 실행시키는 구조로 R스크립트를 작성한다.

~~~ {.python}
#!/usr/bin/env Rscript

##==========================================================================
## R스크립트 인자 설정
##==========================================================================

library(optparse)

option_list <- list(
    make_option(c("-f", "--file"), type="character", default=NULL, 
              help="dataset file name", metavar="character"),
    make_option(c("-o", "--out"), type="character", default="out.txt", 
              help="output file name [default= %default]", metavar="character")
); 
 
opt_parser <- OptionParser(option_list=option_list);
opt <- parse_args(opt_parser);

if (is.null(opt$file)){
  print_help(opt_parser)
  stop("At least one argument must be supplied (input file).n", call.=FALSE)
}

##==========================================================================
## 자동화 프로그램
##==========================================================================
# 데이터 불러오기
gdp.df <- read.csv(opt$file, sep=",", head=FALSE)
# 평균계산
gdp.mean <- mean(gdp.df$V1)
# 계산결과 파일저장
cat(strsplit(opt$file, '\\.')[[1]][1], "평균: ", gdp.mean, "\n", encoding="utf-8", file=opt$out)
~~~

### 실행결과

`Rscript r-args-ex04.R`을 실행하면서 인자를 넣지 않게 되면 메시지를 출력하고, R 스크립트 실행을 멈춘다.

~~~ {.shell}
$ Rscript r-args-ex04.R
~~~

~~~ {.output}
Usage: r-args-ex04.R [options]

Options:
        -f CHARACTER, --file=CHARACTER
                dataset file name

        -o CHARACTER, --out=CHARACTER
                output file name [default= out.txt]

        -h, --help
                Show this help message and exit

Error: At least one argument must be supplied (input file).n
Execution halted
~~~

`optparse`에서 설정된 `-f` 옵션플래그에 처리할 데이터명을 지정하고, 작업처리된 결과를
`-o` 옵션플래그로 지정해서 R스크립트로 처리한 결과를 파일로 떨구어 저장시킨다.

~~~{.shell}
$ Rscript r-args-ex04.R -f france.csv -o france_output.csv
$ cat france_output.csv
~~~

~~~ {.output}
france 평균:  20.95751
~~~