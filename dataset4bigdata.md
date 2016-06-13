---
layout: page
title: 데이터 과학
subtitle: 데이터 과학을 위한 데이터 (빅데이터)
minutes: 10
---

> ### 학습 목표 {.objectives}
>
> * 데이터 과학을 위한 데이터 저장소 및 대표적인 데이터셋을 살펴본다.
> * 데이터 과학을 훈련할 대표적인 데이터셋에 대해 살펴본다.

### 데이터 과학을 위한 빅데이터 [^Joseph-Rickert] [^big-datasets]


데이터 과학을 위해 다양한 기계학습 알고리즘, 통계모형, 신경망 딥러닝을 학습하는 것과는 별도로 이를 적용할 데이터를 찾는 것도 일이다. 너무 많은 예제 데이터가 있는 것도 문제로 빅데이터, 데이터 과학에서 자주 인용되는 데이터를 찾아본다.

* **영화 추천 데이터** : [MovieLens Data Sets](https://datahub.io/dataset/movielens)으로 무비렌즈 온라인 영화추천 사용자 71,567명이 10,681 영화에 95,580 태그 및 10,000,054 평가결과가 담긴 데이터다.
    * 1997년 9월 19일부터 1998년 4월 22일까지 7개월동안 사용자 943명로부터 1,664개 영화에서 10만개 평가를 포함한 데이터로 `library(recommenderlab)` 팩키지를 불러와서 `data(MovieLense)` 명령어로 바로 사용가능하다.
* **항공사 데이터** : [Airline on-time performance](http://stat-computing.org/dataexpo/2009/)로 1987년부터 2008년까지 국내 항공사 출발 및 도착 정보를 담고 있는 데이터셋으로 2009년 ASA 경진대회에 사용된 데이터넷으로 빅데이터의 iris 데이터라는 별명이 붙어있다. 1.23억 관측점과 변수 29개로 구성되어 보통 개인용 컴퓨터에 바로 올라가지 않는다. [다운로드](http://www.transtats.bts.gov/OT_Delay/OT_DelayCause1.asp)
    * 2013년 뉴욕에서 출발한 전체 항공사에 대한 정시 데이터정보를 [nycflights13 - Flights that Departed NYC in 2013](https://cran.r-project.org/web/packages/nycflights13/) R 팩키지로 되어 있어 바로 분석에 사용할 수 있다. `library(nycflights13)`
* **백만곡 데이터** : [Million Song Dataset](http://labrosa.ee.columbia.edu/millionsong/)는 [Echo Nest](http://the.echonest.com/company/) 회사가 생성해서 제공하는 데이터로 원래 [HDF5](https://www.hdfgroup.org/about/hdf_technologies.html) 형식으로 제공되어 활용하기 까다로왔으나 다양한 사람들의 노력으로 이제 백만곡 데이터에 대한 접근성은 나아졌다. [다운로드 1%, 1.8 GB](http://static.echonest.com/millionsongsubset_full.tar.gz), [다운로드 전체, 280 GB](http://labrosa.ee.columbia.edu/millionsong/pages/getting-dataset) [UCI 노래 출시년도 예측](http://archive.ics.uci.edu/ml/datasets/YearPredictionMSD)
    * R 팩키지로 별도로 되어 있지 않아 `sqlite` 데이터베이스 형태로 다운로드 받아 R 에서 분석한다. 711.6 MB SQLite 데이터베이스 크기를 갖는다. [^million-songs-in-r]

[^million-songs-in-r]: [The Million Song Dataset, part 1: What happened after the 1960s?](https://stattrekker.wordpress.com/2015/08/29/the-million-song-dataset-part-1-what-happened-after-the-1960s/)



~~~ {.r}
library(RCurl)
library(RSQLite)
library(data.table)

url <- "http://labrosa.ee.columbia.edu/millionsong/sites/default/files/AdditionalFiles/track_metadata.db"
download.file(url, "track_metadata.db", "auto")

fetch  <- function(db, query, n = -1) {
  result <- dbSendQuery(db, query)
  data <- dbFetch(result, n)
  dbClearResult(result)
  return(as.data.table(data))
}

metadata.db <- dbConnect(SQLite(), dbname='track_metadata.db')

dbListTables(metadata.db)

songs <- fetch(metadata.db, "SELECT * FROM songs")
dbDisconnect(metadata.db)

head(songs, n=3)
~~~



[^Joseph-Rickert]: [Finding Data on the Internet](http://www.inside-r.org/howto/finding-data-internet)

[^big-datasets]: [Data Sets for Data Science](http://www.r-bloggers.com/data-sets-for-data-science/)