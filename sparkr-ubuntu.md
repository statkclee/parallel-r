---
layout: page
title: 데이터 과학
subtitle: 우분투 SparkR 설치
minutes: 10
---

> ### 학습 목표 {.objectives}
>
> * 우분투 SparkR 설치을 설치한다.
> * 스파크를 설치하기 위한 사전 의존성을 점검하고 설치한다.
> * `SparkR` 설치를 위한 `devtools`를 설치한다.
> * R과 RStudio를 스파크와 SparkR에 연결하고 설정을 완료한다.


### 1. SparkR로 분석할 데이터를 준비한다.

`nycflights13.csv` 파일을 다운로드 받아 SparkR로 분석을 준비한다.

~~~ {.shell}
$ wget https://s3-us-west-2.amazonaws.com/sparkr-data/nycflights13.csv
~~~

### 2. 스파크와 하둡 설치

`spark-setup.sh` 쉘스크립트를 생성하고 파일 내부에 다음을 순차적으로 실행시킨다.

1. 자바를 설치한다.
1. 스칼라를 설치한다.
1. 스파크를 설치하는 방법은 다음 두가지가 존재한다.
    * 사전에 빌드가 완료된 스파크를 설치하는 방법 [^spark-prebuild-install]
    * [GitHub](https://github.com/apache/spark) 에서 소스파일을 받아 `maven`으로 설치하는 방법 [^spark-build]

[^spark-prebuild-install]: [Install Apache Spark on Ubuntu-14.04](http://blog.prabeeshk.com/blog/2014/10/31/install-apache-spark-on-ubuntu-14-dot-04/)
[^spark-build]: [우분투에 Apache Spark 설치 삽질](http://ryoost.tistory.com/entry/%EC%9A%B0%EB%B6%84%ED%88%AC%EC%97%90-Apache-Spark-%EC%84%A4%EC%B9%98-%EC%82%BD%EC%A7%88)


~~~ {.shell}
#!/bin/sh

# 1. Java Install
sudo apt-add-repository ppa:webupd8team/java
sudo apt-get update
sudo apt-get install -y oracle-java8-installer

# 2. Scala Install

wget http://downloads.lightbend.com/scala/2.11.8/scala-2.11.8.tgz
sudo mkdir /usr/local/src/scala
sudo tar xvf scala-2.11.8.tgz -C /usr/local/src/scala/

echo 'export SCALA_HOME=/usr/local/src/scala/scala-2.11.8' >> ~/.bashrc 
echo 'export PATH=$SCALA_HOME/bin:$PATH' >> ~/.bashrc 

cd ~
. .bashrc


# 3. Spark Install

sudo apt-get install -y git

wget http://d3kbcqa49mib13.cloudfront.net/spark-1.6.1-bin-hadoop2.6.tgz
tar xvf spark-1.6.1-bin-hadoop2.6.tgz

cd spark-1.6.1-bin-hadoop2.6
sbt/sbt assembly

./bin/run-example SparkPi 10
~~~

마지막에 로그 사이에... $\pi$값이 다음과 같이 보이면 정상적으로 설치가 완료된 것이다.

~~~ {.output}
16/06/07 20:20:35 INFO DAGScheduler: Job 0 finished: reduce at SparkPi.scala:36, took 0.762281 s
Pi is roughly 3.139584
16/06/07 20:20:35 INFO SparkUI: Stopped Spark web UI at http://10.211.55.10:4040
~~~

### 4. Spark와 하둡을 설치한 다음 R과 RStudio에 연결시킨다.

1. `devtools`를 설치한다.
1. `devtools::install_github()` 명령어로 아파치스파크를 다운로드 한다.
    * devtools::install_github('apache/spark@v1.6.1', subdir='R/pkg') 명령어를 실행시킨다.
    * `v1.6.1` 버젼은 아파치스파크 설치버젼과 일치시킨다.
1.  외부 CSV 파일을 불러오기 위해, `spark-csv` `.jar` 파일을 다운로드하여 설치한다.
    * `spark-csv_2.11-1.4.0.jar` 파일은 [spark-csv](https://spark-packages.org/package/databricks/spark-csv)에서 다운로드 받는다.
    * 스파크가 설치된 홈디렉토리에서 ` ./bin/spark-shell --packages com.databricks:spark-csv_2.11:1.4.0` 명령어를 실행하여 설치한다.
    * 위 명령어가 동작되지 않는 경우 `/home/parallels/.ivy2/jars` 디렉토리에서 `.jar` 파일을 복사해 넣는다.


#### 4.1. `devtools` 팩키지 전 설치전 필수적으로 설치할 라이브러리

`devtools` 팩키지로 GitHub에서 SparkR을 설치하기 전에 필수적으로 설치할 라이브러리를 사전에 설치시킨다.

~~~ {.shell}
$ sudo apt-get -y install libcurl4-gnutls-dev
$ sudo apt-get -y install libxml2-dev
$ sudo apt-get -y install libssl-dev
~~~

#### 4.2. `devtools`와 `SparkR`을 설치 

`devtools`와 `SparkR`을 차례로 설치한다.

~~~ {.r}
install.packages("devtools")
devtools::install_github('apache/spark@v1.6.1', subdir='R/pkg')
~~~

#### 4.3. SparkR과 spark-csv 설정

SparkR과 spark-csv 설정을 다음과 같이 진행한다.

~~~ {.r}
Sys.setenv(SPARK_HOME = "/home/parallels/spark-1.6.1-bin-hadoop2.6/")
Sys.setenv(SPARKR_SUBMIT_ARGS="--packages com.databricks:spark-csv_2.11:1.4.0 sparkr-shell")
.libPaths(c(file.path(Sys.getenv("SPARK_HOME"), "R","lib"),  .libPaths()))
library(SparkR)
~~~

#### 4.4. `nycflights13.csv` SparkR로 분석

`nycflights13.csv` 데이터를 스파크 문법에 맞춰 분석을 시작한다.

~~~ {.r}
# Initialize SparkContext and SQLContext
sc <- sparkR.init(appName="SparkR-Flights-example")
sqlContext <- sparkRSQL.init(sc)

flights <- read.df(sqlContext, "nycflights13.csv","com.databricks.spark.csv",header="true")
head(flights)
~~~

출력결과가 다음과 같이 나오면 SparkR에서 외부 csv 데이터를 불러와서 작업을 시작할 모든 준비가 마친 것이다.

~~~ {.output}
> head(flights)
16/06/06 01:45:13 INFO MemoryStore: Block broadcast_13 stored as values in memory (estimated size 127.2 KB, free 721.9 KB)
16/06/06 01:45:13 INFO MemoryStore: Block broadcast_13_piece0 stored as bytes in memory (estimated size 13.8 KB, free 735.7 KB)
16/06/06 01:45:13 INFO BlockManagerInfo: Added broadcast_13_piece0 in memory on localhost:33386 (size: 13.8 KB, free: 511.0 MB)
16/06/06 01:45:13 INFO SparkContext: Created broadcast 13 from textFile at TextFile.scala:30
16/06/06 01:45:13 INFO FileInputFormat: Total input paths to process : 1
16/06/06 01:45:13 INFO SparkContext: Starting job: dfToCols at NativeMethodAccessorImpl.java:-2
16/06/06 01:45:13 INFO DAGScheduler: Got job 5 (dfToCols at NativeMethodAccessorImpl.java:-2) with 1 output partitions
16/06/06 01:45:13 INFO DAGScheduler: Final stage: ResultStage 5 (dfToCols at NativeMethodAccessorImpl.java:-2)
16/06/06 01:45:13 INFO DAGScheduler: Parents of final stage: List()
16/06/06 01:45:13 INFO DAGScheduler: Missing parents: List()
16/06/06 01:45:13 INFO DAGScheduler: Submitting ResultStage 5 (MapPartitionsRDD[38] at dfToCols at NativeMethodAccessorImpl.java:-2), which has no missing parents
16/06/06 01:45:13 INFO MemoryStore: Block broadcast_14 stored as values in memory (estimated size 7.5 KB, free 743.2 KB)
16/06/06 01:45:13 INFO MemoryStore: Block broadcast_14_piece0 stored as bytes in memory (estimated size 4.2 KB, free 747.4 KB)
16/06/06 01:45:13 INFO BlockManagerInfo: Added broadcast_14_piece0 in memory on localhost:33386 (size: 4.2 KB, free: 511.0 MB)
16/06/06 01:45:13 INFO SparkContext: Created broadcast 14 from broadcast at DAGScheduler.scala:1006
16/06/06 01:45:13 INFO DAGScheduler: Submitting 1 missing tasks from ResultStage 5 (MapPartitionsRDD[38] at dfToCols at NativeMethodAccessorImpl.java:-2)
16/06/06 01:45:13 INFO TaskSchedulerImpl: Adding task set 5.0 with 1 tasks
16/06/06 01:45:13 INFO TaskSetManager: Starting task 0.0 in stage 5.0 (TID 5, localhost, partition 0,PROCESS_LOCAL, 2375 bytes)
16/06/06 01:45:13 INFO Executor: Running task 0.0 in stage 5.0 (TID 5)
16/06/06 01:45:13 INFO HadoopRDD: Input split: file:/home/rstudio/nycflights13.csv:0+11744183
16/06/06 01:45:13 INFO Executor: Finished task 0.0 in stage 5.0 (TID 5). 3920 bytes result sent to driver
16/06/06 01:45:13 INFO TaskSetManager: Finished task 0.0 in stage 5.0 (TID 5) in 17 ms on localhost (1/1)
16/06/06 01:45:13 INFO TaskSchedulerImpl: Removed TaskSet 5.0, whose tasks have all completed, from pool 
16/06/06 01:45:13 INFO DAGScheduler: ResultStage 5 (dfToCols at NativeMethodAccessorImpl.java:-2) finished in 0.013 s
16/06/06 01:45:13 INFO DAGScheduler: Job 5 finished: dfToCols at NativeMethodAccessorImpl.java:-2, took 0.022469 s
  year month day dep_time dep_delay arr_time arr_delay carrier tailnum flight origin dest air_time distance hour minute
1 2013     1   1      517         2      830        11      UA  N14228   1545    EWR  IAH      227     1400    5     17
2 2013     1   1      533         4      850        20      UA  N24211   1714    LGA  IAH      227     1416    5     33
3 2013     1   1      542         2      923        33      AA  N619AA   1141    JFK  MIA      160     1089    5     42
4 2013     1   1      544        -1     1004       -18      B6  N804JB    725    JFK  BQN      183     1576    5     44
5 2013     1   1      554        -6      812       -25      DL  N668DN    461    LGA  ATL      116      762    5     54
6 2013     1   1      554        -4      740        12      UA  N39463   1696    EWR  ORD      150      719    5     54
~~~

### 5. 전체 설치 쉘스크립트와 R 스크립트

#### 5.1. 쉘스크립트

~~~ {.shell}
#!/bin/sh

# 1. Java Install
sudo apt-add-repository ppa:webupd8team/java
sudo apt-get update
sudo apt-get install -y oracle-java8-installer

# 2. Scala Install

wget http://downloads.lightbend.com/scala/2.11.8/scala-2.11.8.tgz
sudo mkdir /usr/local/src/scala
sudo tar xvf scala-2.11.8.tgz -C /usr/local/src/scala/

echo 'export SCALA_HOME=/usr/local/src/scala/scala-2.11.8' >> ~/.bashrc 
echo 'export PATH=$SCALA_HOME/bin:$PATH' >> ~/.bashrc 

cd ~
. .bashrc


# 3. Spark Install
sudo apt-get install -y git

wget http://d3kbcqa49mib13.cloudfront.net/spark-1.6.1-bin-hadoop2.6.tgz
tar xvf spark-1.6.1-bin-hadoop2.6.tgz

cd spark-1.6.1-bin-hadoop2.6
sbt/sbt assembly

./bin/run-example SparkPi 10

# 4. devtools Install

sudo apt-get -y install libcurl4-gnutls-dev
sudo apt-get -y install libxml2-dev
sudo apt-get -y install libssl-dev

# 5. R and RStudio Install

codename=$(lsb_release -c -s)
echo "deb http://cran.fhcrc.org/bin/linux/ubuntu $codename/" | sudo tee -a /etc/apt/sources.list > /dev/null
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys E084DAB9
sudo add-apt-repository ppa:marutter/rdev
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install -y r-base r-base-dev

sudo apt-get install -y gdebi-core
wget https://download2.rstudio.org/rstudio-server-0.99.902-amd64.deb
sudo gdebi rstudio-server-0.99.902-amd64.deb

sudo useradd -m rstudio
sudo passwd rstudio


# 6.  NYC  flight  data install

wget https://s3-us-west-2.amazonaws.com/sparkr-data/nycflights13.csv
~~~

#### 5.2. R 스크립트

~~~ {.r}
install.packages("devtools")
devtools::install_github('apache/spark@v1.6.1', subdir='R/pkg')

Sys.setenv(SPARK_HOME = "/home/parallels/spark-1.6.1-bin-hadoop2.6/")
Sys.setenv(SPARKR_SUBMIT_ARGS="--packages com.databricks:spark-csv_2.11:1.4.0 sparkr-shell")
.libPaths(c(file.path(Sys.getenv("SPARK_HOME"), "R","lib"),  .libPaths()))
library(SparkR)

# Initialize SparkContext and SQLContext
sc <- sparkR.init(appName="SparkR-Flights-example")
sqlContext <- sparkRSQL.init(sc)

flights <- read.df(sqlContext, "nycflights13.csv","com.databricks.spark.csv",header="true")
head(flights)
~~~