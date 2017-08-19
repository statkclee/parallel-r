# xwMOOC 데이터 과학
xwMOOC  
`r Sys.Date()`  
 


## 1. 비개인화 추천 {#non-personal-recommendation}

비개인화 추천이 필요한 이유는 사용자를 우선 식별하기 어려운 경우가 있다. 
예를 들어 신규 고객이라든가, 추천 알고리즘이 너무 복잡해서 계산이 오래 걸려 이런 경우를 피하고 싶은데 
그럼에도 불구하고 나름 효과적인 추천 알고리즘이 필요한 경우 비개인화 추천 알고리즘이 유용하다.

과거 빌보드 챠트가 대표적인데 매출이나 라디오 방송횟수를 고려하여 매주 순위를 매겼다. 
영화 순위와 가장 인기있는 상품(매출기준, 별점기준) 등을 통해 제품추천 순위를 정한다.

## 2. 영화 비개인화 추천 {#movie-non-personal-recommendation}

### 2.1. 영화 및 평점 데이터 {#movie-review}

코세라 미네소타 대학 추천시스템 강의에 활용된 "Non-Personalized and Stereotype-Based Recommenders" 데이터(`movies.csv`, 
`ratings.csv`)를 활용하여 비개인화 추천 알고리즘을 개발해본다. 


~~~{.r}
# 1. 데이터 가져오기 -----------------------

movie_df <- read_csv("data/movies.csv")
rating_df <- read_csv("data/ratings.csv")

# 2. 데이터 정제과정 -----------------------

nonperson_df <- left_join(rating_df, movie_df, by="movieId")

nonperson_df %>% sample_n(100) %>% 
    DT::datatable()
~~~

<!--html_preserve--><div id="htmlwidget-2eec84c4ae1ca1899ed0" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-2eec84c4ae1ca1899ed0">{"x":{"filter":"none","data":[["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"],[120572,7723,34587,131910,89527,90462,133811,67352,34587,8932,41486,1741,125171,19414,5063,104887,2702,86768,76630,121403,95708,75422,53930,2945,12778,120941,78774,102532,123297,58346,84752,42290,2988,75001,370,9050,53834,7880,50898,62805,128045,138072,35227,67683,129005,26022,132187,113645,102025,46093,73445,36229,70282,96370,130715,127138,130819,53834,2988,74546,45811,133811,48821,74849,104397,105059,92882,65670,93710,34494,113806,68558,12649,21860,121052,48821,35050,41613,101921,10055,125171,134181,132295,45811,126912,102668,124078,93705,45461,21391,21391,120067,35259,14437,6116,25411,35227,62805,104037,104958],[420,3698,1674,2599,44191,2028,48738,2004,248,2100,5219,2991,1777,6365,6787,364,7445,7482,1104,68157,76251,4014,4239,2719,41285,77561,802,1265,235,1278,6502,2671,2701,40815,2918,2628,3481,3471,32,1387,3186,163,707,97913,4673,1653,68358,34,534,1721,57368,33166,3113,207,637,4901,5507,1405,345,56757,3274,55269,53464,1101,357,5010,1949,30707,516,253,4367,4036,6365,1997,246,1459,1350,3000,3717,8961,914,30707,592,344,293,2921,1103,507,413,1387,2527,2567,2622,7346,858,40278,3107,68791,1732,34542],[3,3,3,3.5,5,5,4.5,3,2,2,3.5,2.5,3,3,2.5,3,4,3,3.5,4.5,3,4,4,3,3.5,3.5,4,4.5,4,4,2.5,3,3,3.5,4.5,2.5,4,4,4,3.5,3,2,2,2.5,4,3.5,5,3.5,4,2.5,5,4.5,0.5,1.5,1.5,3,3,3.5,5,1.5,2.5,4,1,3,4,5,5,4,3,3.5,4,3.5,2.5,3.5,4.5,1,3.5,5,2.5,4.5,3,3.5,4,1,3,4,4.5,3,3,3,3,3,1,2.5,5,4.5,3,3.5,3,4],[1130275875,964234265,1186505532,1279181697,1145316340,938916435,1260775162,1142441379,1186509345,1219336392,1191247530,1226945264,1137512518,1166639320,1253826804,1182624547,1388774960,1113020042,1341727404,1305673164,1310676384,1269215161,1105334819,1090433523,1164668442,1338010679,896975970,1199368143,1080674182,1009168887,1136232505,1139762390,931248855,1426140368,1185126271,1119436487,1233539982,1107865114,1075632089,1170546420,1310303230,1173816439,987550013,1368834285,1002996324,1177182433,1286568553,1336860046,1371736268,1197045998,1214871126,1184375959,1053639944,1060105690,1095978050,1370793325,1058030123,1233612523,994767930,1230448427,1169265531,1266660938,1290462293,1023544881,1138042249,1177856681,1180234730,1149772885,1071366162,1322910687,1119062822,1272182968,1150346092,1128634528,1118607152,965285586,1340502333,973923482,1422889068,1109643768,1137512640,1139997287,1291034865,1169268784,1360518271,1154627241,1088531518,1286333375,1085195538,944130941,944130754,1226108447,1298139039,1291656461,1205528465,1157067122,987460974,1243294206,1023822267,1286236083],["Beverly Hills Cop III (1994)","Running Man, The (1987)","Witness (1985)","Election (1999)","V for Vendetta (2006)","Saving Private Ryan (1998)","Last King of Scotland, The (2006)","Gremlins 2: The New Batch (1990)","Houseguest (1994)","Splash (1984)","Resident Evil (2002)","Live and Let Die (1973)","Wedding Singer, The (1998)","Matrix Reloaded, The (2003)","All the President's Men (1976)","Lion King, The (1994)","Man on Fire (2004)","Enter the Dragon (1973)","Streetcar Named Desire, A (1951)","Inglourious Basterds (2009)","Kick-Ass (2010)","Chocolat (2000)","Blow (2001)","Haunting, The (1999)","Match Point (2005)","Iron Man 2 (2010)","Phenomenon (1996)","Groundhog Day (1993)","Ed Wood (1994)","Young Frankenstein (1974)","28 Days Later (2002)","Notting Hill (1999)","Wild Wild West (1999)","Harry Potter and the Goblet of Fire (2005)","Ferris Bueller's Day Off (1986)","Star Wars: Episode I - The Phantom Menace (1999)","High Fidelity (2000)","Close Encounters of the Third Kind (1977)","Twelve Monkeys (a.k.a. 12 Monkeys) (1995)","Jaws (1975)","Girl, Interrupted (1999)","Desperado (1995)","Mulholland Falls (1996)","Wreck-It Ralph (2012)","Tango &amp; Cash (1989)","Gattaca (1997)","Star Trek (2009)","Babe (1995)","Shadowlands (1993)","Titanic (1997)","Cloverfield (2008)","Crash (2004)","End of Days (1999)","Walk in the Clouds, A (1995)","Sgt. Bilko (1996)","Spy Game (2001)","xXx (2002)","Beavis and Butt-Head Do America (1996)","Adventures of Priscilla, Queen of the Desert, The (1994)","Sweeney Todd: The Demon Barber of Fleet Street (2007)","Single White Female (1992)","Darjeeling Limited, The (2007)","Fantastic Four: Rise of the Silver Surfer (2007)","Top Gun (1986)","Four Weddings and a Funeral (1994)","Black Hawk Down (2001)","Man for All Seasons, A (1966)","Million Dollar Baby (2004)","Renaissance Man (1994)","Interview with the Vampire: The Vampire Chronicles (1994)","Lara Croft: Tomb Raider (2001)","Shadow of the Vampire (2000)","Matrix Reloaded, The (2003)","Exorcist, The (1973)","Hoop Dreams (1994)","Absolute Power (1997)","Omen, The (1976)","Princess Mononoke (Mononoke-hime) (1997)","Gone in 60 Seconds (2000)","Incredibles, The (2004)","My Fair Lady (1964)","Million Dollar Baby (2004)","Batman (1989)","Ace Ventura: Pet Detective (1994)","Léon: The Professional (a.k.a. The Professional) (Léon) (1994)","High Plains Drifter (1973)","Rebel Without a Cause (1955)","Perfect World, A (1993)","Airheads (1994)","Jaws (1975)","Westworld (1973)","EDtv (1999)","William Shakespeare's A Midsummer Night's Dream (1999)","Girl Next Door, The (2004)","Godfather, The (1972)","Jarhead (2005)","Backdraft (1991)","Terminator Salvation (2009)","Big Lebowski, The (1998)","Grizzly Man (2005)"],["Action|Comedy|Crime|Thriller","Action|Sci-Fi","Drama|Romance|Thriller","Comedy","Action|Sci-Fi|Thriller|IMAX","Action|Drama|War","Drama|Thriller","Comedy|Horror","Comedy","Comedy|Fantasy|Romance","Action|Horror|Sci-Fi|Thriller","Action|Adventure|Thriller","Comedy|Romance","Action|Adventure|Sci-Fi|Thriller|IMAX","Drama|Thriller","Adventure|Animation|Children|Drama|Musical|IMAX","Action|Crime|Drama|Mystery|Thriller","Action|Crime","Drama","Action|Drama|War","Action|Comedy","Drama|Romance","Crime|Drama","Horror|Thriller","Crime|Drama|Romance","Action|Adventure|Sci-Fi|Thriller|IMAX","Drama|Romance","Comedy|Fantasy|Romance","Comedy|Drama","Comedy|Fantasy","Action|Horror|Sci-Fi","Comedy|Romance","Action|Comedy|Sci-Fi|Western","Adventure|Fantasy|Thriller|IMAX","Comedy","Action|Adventure|Sci-Fi","Comedy|Drama|Romance","Adventure|Drama|Sci-Fi","Mystery|Sci-Fi|Thriller","Action|Horror","Drama","Action|Romance|Western","Crime|Drama|Thriller","Animation|Comedy","Action|Comedy|Crime|Thriller","Drama|Sci-Fi|Thriller","Action|Adventure|Sci-Fi|IMAX","Children|Drama","Drama|Romance","Drama|Romance","Action|Mystery|Sci-Fi|Thriller","Crime|Drama","Action|Fantasy|Horror|Mystery|Thriller","Drama|Romance","Comedy","Action|Crime|Drama|Thriller","Action|Crime|Thriller","Adventure|Animation|Comedy|Crime","Comedy|Drama","Drama|Horror|Musical|Thriller","Drama|Thriller","Adventure|Comedy|Drama","Action|Adventure|Sci-Fi","Action|Romance","Comedy|Romance","Action|Drama|War","Drama","Drama","Comedy|Drama","Drama|Horror","Action|Adventure","Drama|Horror","Action|Adventure|Sci-Fi|Thriller|IMAX","Horror|Mystery","Documentary","Mystery|Thriller","Horror|Mystery|Thriller","Action|Adventure|Animation|Drama|Fantasy","Action|Crime","Action|Adventure|Animation|Children|Comedy","Comedy|Drama|Musical|Romance","Drama","Action|Crime|Thriller","Comedy","Action|Crime|Drama|Thriller","Western","Drama","Crime|Drama|Thriller","Comedy","Action|Horror","Action|Sci-Fi|Thriller|Western","Comedy","Comedy|Fantasy","Comedy|Romance","Crime|Drama","Action|Drama|War","Action|Drama","Action|Adventure|Sci-Fi|Thriller","Comedy|Crime","Documentary"]],"container":"<table class=\"display\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>userId<\/th>\n      <th>movieId<\/th>\n      <th>rating<\/th>\n      <th>timestamp<\/th>\n      <th>title<\/th>\n      <th>genres<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"columnDefs":[{"className":"dt-right","targets":[1,2,3,4]},{"orderable":false,"targets":0}],"order":[],"autoWidth":false,"orderClasses":false}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->

### 2.2. 비개인화 추천 알고리즘 {#non-personal-algorithm}

영화별로 묶어 영화를 본 관객 평점을 평균내어 가장 높은 평점을 받은 영화 10개를 뽑아 이를 
추천영화로 제시한다. 통계적으로 보면 평균을 내어 이를 활용하는 것으로 볼 수 있다.


~~~{.r}
# 3. 고평점 영화 추천 -----------------------

nonperson_df %>% group_by(movieId, title) %>% 
    summarise(mean_movie_rating = mean(rating)) %>% 
    arrange(desc(mean_movie_rating)) %>% 
    ungroup() %>% 
    top_n(10, mean_movie_rating)
~~~



~~~{.output}
# A tibble: 10 x 3
   movieId                            title mean_movie_rating
     <int>                            <chr>             <dbl>
 1     318 Shawshank Redemption, The (1994)          4.364362
 2     858            Godfather, The (1972)          4.315848
 3    1248             Touch of Evil (1958)          4.259259
 4    2959                Fight Club (1999)          4.258503
 5    7502          Band of Brothers (2001)          4.247423
 6    1203              12 Angry Men (1957)          4.246032
 7    2859         Stop Making Sense (1984)          4.220000
 8    1221   Godfather: Part II, The (1974)          4.218462
 9     296              Pulp Fiction (1994)          4.217781
10    2571               Matrix, The (1999)          4.195359

~~~

## 3. 제품추천 (Product Association) [^movie-recommendation] {#product-recommendation}

[^movie-recommendation]: [Movie Recommendation with Market Basket Analysis](https://rpubs.com/vitidN/203264)

다음 단계로 관객이 특정 영화를 하나 본 사실을 바탕으로 다른 영화를 추천해보자.
마치 고객이 물건을 하나 구매한 후에 다른 제품을 추천하는 것과 유사하다.
이를 위해서 사용하는 기법이 지지도(Support), 신뢰도(Confidence), **향상도(lift)**를 활용하는 것이다.
연관분석에 대한 [xwMOOC 장바구니 데이터분석](http://statkclee.github.io/ml/ml-market-basket.html)을 참조한다.

### 3.1. 연관분석기법으로 영화추천 {#association-rules}

가장 먼저 `arules` 팩키지를 활용 **관객-영화 행렬(User-Item Matrix)**을 생성시킨다. 관객이 영화를 봤으면 1, 그렇지 않은 경우 0으로 
인코딩하는데 엄청나게 성긴 행렬 객체로 표현해야 주기억장치(main memory)이 꽉 차서 컴퓨터가 사망하는 사례를 막을 수 있다.
이유는 간단하다. 영화가 너무 많고 약 2시간 기준이라고 하면 유저인 관객이 이 모든 영화를 다 보는 것은 불가능하기 때문에 
거의 대부분의 영화에 0 이 채워지게 된다. 따라서 관객-영화 행렬이 엄청 커질 수 밖에 없다.


~~~{.r}
# 4. Lift -----------------------------------
(user_item_matrix <- as(split(nonperson_df$movieId, nonperson_df$userId), "transactions"))
~~~



~~~{.output}
transactions in sparse format with
 862 transactions (rows) and
 2500 items (columns)

~~~



~~~{.r}
format(object.size(user_item_matrix), units = "auto")
~~~



~~~{.output}
[1] "1.2 Mb"

~~~



~~~{.r}
rule_param = list(
    supp = 0.001,
    conf = 0.7,
    maxlen = 2
)

movie_arules <- apriori(user_item_matrix, parameter = rule_param)
~~~



~~~{.output}
Apriori

Parameter specification:
 confidence minval smax arem  aval originalSupport maxtime support minlen
        0.7    0.1    1 none FALSE            TRUE       5   0.001      1
 maxlen target   ext
      2  rules FALSE

Algorithmic control:
 filter tree heap memopt load sort verbose
    0.1 TRUE TRUE  FALSE TRUE    2    TRUE

Absolute minimum support count: 0 

set item appearances ...[0 item(s)] done [0.00s].
set transactions ...[2500 item(s), 862 transaction(s)] done [0.02s].
sorting and recoding items ... [2500 item(s)] done [0.01s].
creating transaction tree ... done [0.00s].
checking subsets of size 1 2 done [0.11s].
writing ... [249409 rule(s)] done [0.06s].
creating S4 object  ... done [0.04s].

~~~



~~~{.r}
movie_arules <- as(movie_arules,"data.frame")
~~~

### 3.2. 영화추천 {#the-matrix}

다음 단계로 관객-영화 행렬(User-Item Matrix)을 연관분석 특히, 향상도(lift)로 계산한 후에 
매트릭스(The Matrix) 영화를 본 관객에게 향상도를 기준으로 다음에 볼 영화를 추천해 보자.


~~~{.r}
## 4.1. 추천 영화 ---------------------------

recom_df <- movie_arules %>% 
    mutate(tmp_movie = str_extract_all(rules, "[0-9]+")) %>% 
    separate(tmp_movie, c("lhs_movie", "rhs_movie"), sep=",", fill="left", remove = TRUE) %>% 
    mutate(lhs_movie = as.numeric(str_extract(lhs_movie, "[[:number:]]+")), 
           rhs_movie = as.numeric(str_extract(rhs_movie, "[[:number:]]+")))

recom_df <- movie_df %>% select(movieId, title) %>% 
    right_join(recom_df, by=c("movieId" = "rhs_movie")) %>% 
    rename(recom_title=title, recom_movieId = movieId) 

recom_df <- movie_df %>% select(movieId, title) %>% 
    right_join(recom_df, by=c("movieId" = "lhs_movie")) %>% 
    rename(source_title=title, source_movieId = movieId) %>% 
    select(rules, lift, support, confidence, source_movieId, source_title, recom_movieId, recom_title)

recom_df %>% filter(source_movieId == 2571) %>% 
    arrange(desc(lift)) %>% DT::datatable() %>% 
    DT::formatRound(c("lift", "support", "confidence"), digits=3)
~~~

<!--html_preserve--><div id="htmlwidget-cd93f0dce8ffe6d618e0" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-cd93f0dce8ffe6d618e0">{"x":{"filter":"none","data":[["1","2","3","4","5","6","7","8","9","10","11","12"],["{2571} =&gt; {1196}","{2571} =&gt; {480}","{2571} =&gt; {6539}","{2571} =&gt; {260}","{2571} =&gt; {2959}","{2571} =&gt; {7153}","{2571} =&gt; {4993}","{2571} =&gt; {593}","{2571} =&gt; {5952}","{2571} =&gt; {356}","{2571} =&gt; {296}","{2571} =&gt; {318}"],[1.20945168486556,1.19930177812314,1.18847853426096,1.18187923218983,1.17191127948185,1.16517917371496,1.1650758991571,1.16210356023413,1.15640578140202,1.1304154975074,1.1199070049135,1.11424491442647],[0.554524361948956,0.564965197215777,0.554524361948956,0.568445475638051,0.619489559164733,0.604408352668213,0.657772621809745,0.556844547563805,0.620649651972158,0.631090487238979,0.617169373549884,0.564965197215777],[0.715568862275449,0.729041916167665,0.715568862275449,0.733532934131736,0.79940119760479,0.779940119760479,0.848802395209581,0.718562874251497,0.800898203592814,0.81437125748503,0.796407185628742,0.729041916167665],[2571,2571,2571,2571,2571,2571,2571,2571,2571,2571,2571,2571],["Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)"],[1196,480,6539,260,2959,7153,4993,593,5952,356,296,318],["Star Wars: Episode V - The Empire Strikes Back (1980)","Jurassic Park (1993)","Pirates of the Caribbean: The Curse of the Black Pearl (2003)","Star Wars: Episode IV - A New Hope (1977)","Fight Club (1999)","Lord of the Rings: The Return of the King, The (2003)","Lord of the Rings: The Fellowship of the Ring, The (2001)","Silence of the Lambs, The (1991)","Lord of the Rings: The Two Towers, The (2002)","Forrest Gump (1994)","Pulp Fiction (1994)","Shawshank Redemption, The (1994)"]],"container":"<table class=\"display\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>rules<\/th>\n      <th>lift<\/th>\n      <th>support<\/th>\n      <th>confidence<\/th>\n      <th>source_movieId<\/th>\n      <th>source_title<\/th>\n      <th>recom_movieId<\/th>\n      <th>recom_title<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"columnDefs":[{"className":"dt-right","targets":[2,3,4,5,7]},{"orderable":false,"targets":0}],"order":[],"autoWidth":false,"orderClasses":false,"rowCallback":"function(row, data) {\nDTWidget.formatRound(this, row, data, 2, 3);\nDTWidget.formatRound(this, row, data, 3, 3);\nDTWidget.formatRound(this, row, data, 4, 3);\n}"}},"evals":["options.rowCallback"],"jsHooks":[]}</script><!--/html_preserve-->

## 4. 농담 추천 [^recommenderlab-jester] {#joke-recom}

[^recommenderlab-jester]: [Recommender Systems: Non-personalized Recommender](http://michael.hahsler.net/other_courses/ICMA_Recommendation_Tools/code/non-personalized.html#bester-average-rating)

### 4.1. `recommenderlab` 팩키지를 통한 비개인화 추천 {#joke-recommenderlab}

`recommenderlab` 팩키지를 기능을 활용하여 즉각 농담을 추천할 수 있다.
`Jester5k` 농담은 5,000명이 100개 농담에 대한 평점이 담겨있다.

`recommenderRegistry` 체계를 활용하기 때문에 먼저 등록을 한다. 
그리고 나서 `Recommender`에 `method = "POPULAR"`를 인자로 넘기면 추천을 해준다.
첫번째 유저 `u2841`에 대한 추천 농담을 3개 뽑는 과정은 다음과 같다.



~~~{.r}
# 0. 환경설정 ------------------------------

# library(recommenderlab) # devtools::install_github("mhahsler/recommenderlab")
# library(tidyverse)
# library(stringr)

# 1. 데이터 가져오기 -----------------------
data(Jester5k)

# 2. 팩키지 사용 추천 ----------------------
recommenderRegistry$get_entry("POPULAR", type ="realRatingMatrix")
~~~



~~~{.output}
Recommender method: POPULAR for realRatingMatrix
Description: Recommender based on item popularity.
Reference: NA
Parameters:
  normalize    aggregationRatings aggregationPopularity
1  "center" new("standardGeneric" new("standardGeneric"

~~~



~~~{.r}
joke_recom <- Recommender(Jester5k, method = "POPULAR")

joke_pred <- predict(joke_recom, Jester5k[1:3,])
(joke_pred_list <- as(joke_pred, "list"))
~~~



~~~{.output}
$u2841
 [1] "j89" "j72" "j76" "j88" "j83" "j87" "j81" "j78" "j73" "j80"

$u15547
 [1] "j89" "j93" "j76" "j88" "j91" "j83" "j87" "j81" "j97" "j78"

$u15221
character(0)

~~~



~~~{.r}
cat(JesterJokes[joke_pred_list$u2841[1:3]], sep = "\n\n")
~~~



~~~{.output}
A radio conversation of a US naval ship with Canadian authorities ... Americans: Please divert your course 15 degrees to the North to avoid a collision. Canadians: Recommend you divert YOUR course 15 degrees to the South to avoid a collision. Americans: This is the Captain of a US Navy ship. I say again, divert YOUR course. Canadians: No. I say again, you divert YOUR course. Americans: This is the aircraft carrier USS LINCOLN, the second largest ship in the United States' Atlantic Fleet. We are accompanied by three destroyers, three cruisers and numerous support vessels. I demand that you change your course 15 degrees north, that's ONE FIVE DEGREES NORTH, or counter-measures will be undertaken to ensure the safety of this ship. Canadians: This is a lighthouse. Your call.

On the first day of college, the Dean addressed the students, pointing out some of the rules: "The female dormitory will be out-of-bounds for all male students and the male dormitory to the female students. Anybody caught breaking this rule will be finded $20 the first time." He continued, "Anybody caught breaking this rule the second time will be fined $60. Being caught a third time will cost you a fine of $180. Are there any questions ?" At this point, a male student in the crowd inquired: "How much for a season pass ?"

There once was a man and a woman that both got in a terrible car wreck. Both of their vehicles were completely destroyed, buy fortunately, no one was hurt. In thankfulness, the woman said to the man, 'We are both okay, so we should celebrate. I have a bottle of wine in my car, let's open it.' So the woman got the bottleout of the car, and handed it to the man. The man took a really big drink, and handed the woman the bottle. The woman closed the bottle and put it down. The man asked, 'Aren't you going to take a drink?' The woman cleverly replied, 'No, I think I'll just wait for the cops to get here.'

~~~

### 4.2. 인기도를 세가지 기준으로 적용하기 {#joke-popularity}

첫번째로 농담 평점을 기준으로, 두번째로 유저 평가수를 기준으로, 세번째로 이 둘을 조합한 기준을 넣어 
농담을 추천해본다.

#### 4.2.1. 인기도가 높은 농담 추천

Jester5k 평점 데이터를 정규화하고 농담이 칼럼기준으로 되어 있어 유저가 평가한 농담 평점을 평균내고 
이를 평점이 높은 순으로 정렬하고 나서 상위 3개를 뽑는다.


~~~{.r}
# 3. 인기도에 따른 추천 --------------------
## 3.1. 평균 평점이 높은 농담
joke_avg_top3 <- Jester5k %>% 
    normalize %>% 
    colMeans %>% 
    sort(decreasing = TRUE) %>% 
    head(3)

cat(JesterJokes[names(joke_avg_top3)], sep = "\n\n")
~~~



~~~{.output}
A guy goes into confession and says to the priest, "Father, I'm 80 years old, widower, with 11 grandchildren. Last night I met two beautiful flight attendants. They took me home and I made love to both of them. Twice." The priest said: "Well, my son, when was the last time you were in confession?" "Never Father, I'm Jewish." "So then, why are you telling me?" "I'm telling everybody."

A radio conversation of a US naval ship with Canadian authorities ... Americans: Please divert your course 15 degrees to the North to avoid a collision. Canadians: Recommend you divert YOUR course 15 degrees to the South to avoid a collision. Americans: This is the Captain of a US Navy ship. I say again, divert YOUR course. Canadians: No. I say again, you divert YOUR course. Americans: This is the aircraft carrier USS LINCOLN, the second largest ship in the United States' Atlantic Fleet. We are accompanied by three destroyers, three cruisers and numerous support vessels. I demand that you change your course 15 degrees north, that's ONE FIVE DEGREES NORTH, or counter-measures will be undertaken to ensure the safety of this ship. Canadians: This is a lighthouse. Your call.

A guy walks into a bar, orders a beer and says to the bartender, "Hey, I got this great Polish Joke..." The barkeep glares at him and says in a warning tone of voice: "Before you go telling that joke you better know that I'm Polish, both bouncers are Polish and so are most of my customers" "Okay" says the customer,"I'll tell it very slowly."

~~~

#### 4.2.2. 평가가 많은 농담 추천

평점보다 농담에 대한 평가횟수가 높은 농담을 정렬하여 상위 3개를 추출하여 추천한다.


~~~{.r}
## 3.2. 평가수 높은 농담

joke_freq_top3 <- Jester5k %>% 
    normalize %>% 
    colCounts %>% 
    sort(decreasing = TRUE) %>% 
    head(3)

cat(JesterJokes[names(joke_freq_top3)], sep = "\n\n")
~~~



~~~{.output}
Q. Did you hear about the dyslexic devil worshiper? A. He sold his soul to Santa.

They asked the Japanese visitor if they have elections in his country. "Every Morning" he answers.

Q: What did the blind person say when given some matzah? A: Who the hell wrote this?

~~~

#### 4.2.3. 평가수와 평점을 조합하여 추천

이 둘을 조합하여 농담을 추천하는 것도 가능하다.


~~~{.r}
## 3.3. 평점이 높고 자주 언급되는 농담

joke_avg_freq_top3 <- Jester5k %>% 
    normalize %>% 
    binarize(minRating = 5) %>% 
    colCounts() %>% 
    sort(decreasing = TRUE) %>% 
    head(3)

cat(JesterJokes[names(joke_avg_freq_top3)], sep = "\n\n")
~~~



~~~{.output}
A guy goes into confession and says to the priest, "Father, I'm 80 years old, widower, with 11 grandchildren. Last night I met two beautiful flight attendants. They took me home and I made love to both of them. Twice." The priest said: "Well, my son, when was the last time you were in confession?" "Never Father, I'm Jewish." "So then, why are you telling me?" "I'm telling everybody."

An old Scotsmen is sitting with a younger Scottish gentleman and says the boy. "Ah, lad look out that window. You see that stone wall there, I built it with me own bare hands, placed every stone meself. But do they call me MacGregor the wall builder? No! He Takes a few sips of his beer then says, "Aye, and look out on that lake and eye that beautiful pier. I built it meself, laid every board and hammered each nail but do they call me MacGregor the pier builder? No! He continues..."And lad, you see that road? That too I build with me own bare hands. Laid every inch of pavement meself, but do they call MacGregor the road builder? No!" Again he returns to his beer for a few sips, then says, "Agh, but you screw one sheep..."

A man arrives at the gates of heaven. St. Peter asks, "Religion?" The man says, "Methodist." St. Peter looks down his list, and says, "Go to room 24, but be very quiet as you pass room 8." Another man arrives at the gates of heaven. "Religion?" "Baptist." "Go to room 18, but be very quiet as you pass room 8." A third man arrives at the gates. "Religion?" "Jewish." "Go to room 11, but be very quiet as you pass room 8." The man says, "I can understand there being different rooms for different religions, but why must I be quiet when I pass room 8?" St. Peter tells him, "Well the Catholics are in room 8, and they think they're the only ones here.

~~~
