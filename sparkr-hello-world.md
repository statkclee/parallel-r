---
layout: page
title: 데이터 과학
subtitle: SparkR 헬로 월드
minutes: 10
---

> ### 학습 목표 {.objectives}
>
> * SparkR 헬로 월드를 찍어본다.

### 헬로 월드

코딩을 처음 배우게 되면 "Hello World"를 찍어 보게 된다. 사실 헬로월드를 찍게되면
해당 프로그래밍 언어로 대화가 가능하게 되었다는 의미가 된다. 마치 아무것도 모르던 사람과 
처음 말을 트게 되고 이제부터 친교를 쌓아나가게 되는 것만 남게 된다는 느낌이다.

임베디드 아두이노 프로그래밍을 처음 배울 때 전구를 깜박이는 것이 그쪽 세계에서 헬로월드에 
해당되고, 빅데이터 세계에서는 단어 숫자를 처음 세는 것이 헬로월드다.

`README.md` 파일에 담긴 내용을 살펴본다. `head README.md` 파일은 다음과 같다.

~~~ {.shell}
vagrant@vagrant-ubuntu-trusty-64:~/spark-1.6$ head README.md
# Apache Spark

Spark is a fast and general cluster computing system for Big Data. It provides
high-level APIs in Scala, Java, Python, and R, and an optimized engine that
supports general computation graphs for data analysis. It also supports a
rich set of higher-level tools including Spark SQL for SQL and DataFrames,
MLlib for machine learning, GraphX for graph processing,
and Spark Streaming for stream processing.

<http://spark.apache.org/>
~~~

`wc -l README.md` 명령어를 통해서 95개 행으로 구성된 것을 읽어보지 않고 파악할 수 있다.

~~~ {.shell}
vagrant@vagrant-ubuntu-trusty-64:~/spark-1.6$ wc -l README.md
95 README.md
~~~

### `SparkR`를 사용한 헬로월드 [^sparkR-hello-world]

[^sparkR-hello-world]: [SparkR quick start that works](http://www.r-bloggers.com/sparkr-quick-start-that-works/)

가장 먼저 `README.md` 파일이 위치한 `$SPARK_HOME` 경로로 이동한다. 그리고 나서 `./bin/sparkR` 명령어로 SparkR를 시작시킨다.

~~~ {.r}
vagrant@vagrant-ubuntu-trusty-64:~/spark-1.6$ ./bin/sparkR
~~~

~~~ {.output}
R version 3.3.0 (2016-05-03) -- "Supposedly Educational"
Copyright (C) 2016 The R Foundation for Statistical Computing
Platform: x86_64-pc-linux-gnu (64-bit)

R is free software and comes with ABSOLUTELY NO WARRANTY.
You are welcome to redistribute it under certain conditions.
Type 'license()' or 'licence()' for distribution details.

  Natural language support but running in an English locale

R is a collaborative project with many contributors.
Type 'contributors()' for more information and
'citation()' on how to cite R or R packages in publications.

Type 'demo()' for some demos, 'help()' for on-line help, or
'help.start()' for an HTML browser interface to help.
Type 'q()' to quit R.

Launching java with spark-submit command /home/vagrant/spark-1.6/bin/spark-submit   "sparkr-shell" /tmp/RtmpZNiWwz/backend_port6bf6ac1b64e
...
중략
...
 Welcome to
    ____              __
   / __/__  ___ _____/ /__
  _\ \/ _ \/ _ `/ __/  '_/
 /___/ .__/\_,_/_/ /_/\_\   version  1.6.1
    /_/


 Spark context is available as sc, SQL context is available as sqlContext
>
~~~

R 이 연결된 것이 확인되고, SparkR 명령프롬프트가 깜박이는 것이 확인된다. 스파크 학습교재에 있는 내용을 그대로 따라하면 95개 행으로 된 것이 확인된다. 물론 직접 돌리게 되면 로그가 엄청 찍히고 나서... 마지막에 `[1] 95` 가 찍힌다.

~~~ {.r}
> text_file <- SparkR:::textFile(sc, 'README.md')
> count(text_file)
[1] 95
~~~

