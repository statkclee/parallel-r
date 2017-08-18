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

<!--html_preserve--><div id="htmlwidget-565917ece360dac28e53" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-565917ece360dac28e53">{"x":{"filter":"none","data":[["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"],[5063,36229,39214,45461,70740,124425,57969,70282,66455,96370,8932,55479,124288,131620,86784,2988,41518,102532,22363,32780,124998,47866,42245,77512,127138,8932,18758,79401,35246,58265,64365,18758,98781,28090,45669,137118,99093,103927,87042,115611,34156,96482,45811,118067,70282,26022,31476,127453,26480,975,28176,108159,22352,104508,65670,76612,46403,70939,14328,72766,117905,58579,58802,128480,115364,57866,10055,114601,65670,52762,51549,52520,117144,70939,124102,8932,18390,119501,48838,87042,129008,42245,5475,41703,42290,127138,104500,58265,135223,64150,84549,111841,79531,80285,102532,124078,134401,67584,135092,49531],[1784,55247,8798,60126,5060,86882,4975,4954,2541,7162,38038,8366,2976,597,4306,8360,1271,111362,2053,3826,2921,47200,4015,3156,51540,1673,1953,1958,778,3247,765,344,1223,7151,1209,2712,4993,44665,920,377,1200,2021,8361,2987,1376,1517,41997,1347,8368,106782,4995,4308,5463,1584,594,720,356,2194,1917,1250,2501,2161,4701,59501,55280,5618,3114,1923,8641,5902,67734,5265,2502,2949,45499,3148,5991,349,204,2505,2321,7438,2826,2949,694,96079,7458,6953,1479,41997,194,52435,2688,1198,3543,52281,2719,4148,1537,3157],[3,4,5,4,5,3,1.5,2.5,4,4,3.5,4.5,4.5,3.5,4,2,3.5,4.5,1,3,3.5,3,1,3.5,4,5,4.5,4.5,5,4,4,4,5,3,5,4.5,4,3,5,2.5,4,3.5,4,3,4,4,4,2,3.5,3.5,4.5,4,4.5,4,3.5,4,5,5,3,4,5,4.5,5,3.5,4,4,4,4.5,2.5,2,4.5,4,4,5,3.5,2,4,2,4,4,3,1,1,4,2.5,4.5,4,3.5,1,2.5,3.5,3,3,2.5,5,4,2,3.5,3.5,3.5],[1246545450,1211763071,1372568297,1219171397,1010331428,1355324245,1201179729,1062533189,1306766891,1088599323,1206549371,1094061556,1177496949,1315455687,1357091593,1197414110,1290364449,1402649373,1118198444,1196200653,1414088233,1277246535,1291972471,1149585665,1186324092,1219336260,1360840330,1127671980,1003171610,1299476125,1287862025,1360782708,1132743804,1184776332,1197075442,1211804831,1290529856,1168651450,1053472340,1359141591,1181586268,1123419539,1169317578,1112330215,945131396,1177182279,1423047736,1143941993,1229115458,1427752523,1197183387,1425618807,1206752907,1237407739,1156452632,1163870891,1164105281,1351440591,1115604598,1250097253,1059970479,1388620251,1162869310,1420501246,1214972925,1420946998,1021673970,1281717057,1150660800,1350110616,1299238523,1169156681,998957981,1351440783,1202618316,1228301658,1158186332,1169038826,1019620324,1054615728,970776167,1154930997,1251837560,1425220778,1139604661,1356021335,1231099915,1299478369,1244851878,1170342887,1122808603,1245685708,939802247,1426349640,1211754663,1180563234,1068139510,1186787420,1053313713,1201549742],["As Good as It Gets (1997)","Into the Wild (2007)","Collateral (2004)","Get Smart (2008)","M*A*S*H (a.k.a. MASH) (1970)","Midnight in Paris (2011)","Vanilla Sky (2001)","Ocean's Eleven (a.k.a. Ocean's 11) (1960)","Cruel Intentions (1999)","Cold Mountain (2003)","Wallace &amp; Gromit in The Curse of the Were-Rabbit (2005)","Saved! (2004)","Bringing Out the Dead (1999)","Pretty Woman (1990)","Shrek (2001)","Shrek 2 (2004)","Fried Green Tomatoes (1991)","X-Men: Days of Future Past (2014)","Honey, I Blew Up the Kid (1992)","Hollow Man (2000)","High Plains Drifter (1973)","Crank (2006)","Dude, Where's My Car? (2000)","Bicentennial Man (1999)","Zodiac (2007)","Boogie Nights (1997)","French Connection, The (1971)","Terms of Endearment (1983)","Trainspotting (1996)","Sister Act (1992)","Jack (1996)","Ace Ventura: Pet Detective (1994)","Grand Day Out with Wallace and Gromit, A (1989)","Girl with a Pearl Earring (2003)","Once Upon a Time in the West (C'era una volta il West) (1968)","Eyes Wide Shut (1999)","Lord of the Rings: The Fellowship of the Ring, The (2001)","Lucky Number Slevin (2006)","Gone with the Wind (1939)","Speed (1994)","Aliens (1986)","Dune (1984)","Day After Tomorrow, The (2004)","Who Framed Roger Rabbit? (1988)","Star Trek IV: The Voyage Home (1986)","Austin Powers: International Man of Mystery (1997)","Munich (2005)","Nightmare on Elm Street, A (1984)","Harry Potter and the Prisoner of Azkaban (2004)","Wolf of Wall Street, The (2013)","Beautiful Mind, A (2001)","Moulin Rouge (2001)","Reign of Fire (2002)","Contact (1997)","Snow White and the Seven Dwarfs (1937)","Wallace &amp; Gromit: The Best of Aardman Animation (1996)","Forrest Gump (1994)","Untouchables, The (1987)","Armageddon (1998)","Bridge on the River Kwai, The (1957)","October Sky (1999)","NeverEnding Story, The (1984)","Rush Hour 2 (2001)","Chronicles of Narnia: Prince Caspian, The (2008)","Lars and the Real Girl (2007)","Spirited Away (Sen to Chihiro no kamikakushi) (2001)","Toy Story 2 (1999)","There's Something About Mary (1998)","Anchorman: The Legend of Ron Burgundy (2004)","Adaptation (2002)","Adventureland (2009)","Death to Smoochy (2002)","Office Space (1999)","Dr. No (1962)","X-Men: The Last Stand (2006)","Cider House Rules, The (1999)","Chicago (2002)","Clear and Present Danger (1994)","Under Siege 2: Dark Territory (1995)","8MM (1999)","Pleasantville (1998)","Kill Bill: Vol. 2 (2004)","13th Warrior, The (1999)","Dr. No (1962)","Substitute, The (1996)","Skyfall (2012)","Troy (2004)","21 Grams (2003)","Saint, The (1997)","Munich (2005)","Smoke (1995)","How the Grinch Stole Christmas! (1966)","General's Daughter, The (1999)","Raiders of the Lost Ark (Indiana Jones and the Raiders of the Lost Ark) (1981)","Diner (1982)","Grindhouse (2007)","Haunting, The (1999)","Hannibal (2001)","Shall We Dance? (Shall We Dansu?) (1996)","Stuart Little (1999)"],["Comedy|Drama|Romance","Action|Adventure|Drama","Action|Crime|Drama|Thriller","Action|Comedy","Comedy|Drama|War","Comedy|Fantasy|Romance","Mystery|Romance|Sci-Fi|Thriller","Comedy|Crime","Drama","Drama|Romance|War","Adventure|Animation|Children|Comedy","Comedy|Drama","Drama","Comedy|Romance","Adventure|Animation|Children|Comedy|Fantasy|Romance","Adventure|Animation|Children|Comedy|Musical|Romance","Comedy|Crime|Drama","Action|Adventure|Sci-Fi","Children|Comedy|Sci-Fi","Horror|Sci-Fi|Thriller","Western","Action|Thriller","Comedy|Sci-Fi","Drama|Romance|Sci-Fi","Crime|Drama|Thriller","Drama","Action|Crime|Thriller","Comedy|Drama","Comedy|Crime|Drama","Comedy|Crime","Comedy|Drama","Comedy","Adventure|Animation|Children|Comedy|Sci-Fi","Drama|Romance","Action|Drama|Western","Drama|Mystery|Thriller","Adventure|Fantasy","Crime|Drama|Mystery","Drama|Romance|War","Action|Romance|Thriller","Action|Adventure|Horror|Sci-Fi","Adventure|Sci-Fi","Action|Adventure|Drama|Sci-Fi|Thriller","Adventure|Animation|Children|Comedy|Crime|Fantasy|Mystery","Adventure|Comedy|Sci-Fi","Action|Adventure|Comedy","Action|Crime|Drama|Thriller","Horror|Thriller","Adventure|Fantasy|IMAX","Comedy|Crime|Drama","Drama|Romance","Drama|Musical|Romance","Action|Adventure|Fantasy","Drama|Sci-Fi","Animation|Children|Drama|Fantasy|Musical","Adventure|Animation|Comedy","Comedy|Drama|Romance|War","Action|Crime|Drama","Action|Romance|Sci-Fi|Thriller","Adventure|Drama|War","Drama","Adventure|Children|Fantasy","Action|Comedy","Adventure|Children|Fantasy","Comedy|Drama","Adventure|Animation|Fantasy","Adventure|Animation|Children|Comedy|Fantasy","Comedy|Romance","Comedy","Comedy|Drama|Romance","Comedy|Drama","Comedy|Crime|Drama","Comedy|Crime","Action|Adventure|Thriller","Action|Sci-Fi|Thriller","Drama","Comedy|Crime|Drama|Musical","Action|Crime|Drama|Thriller","Action","Drama|Mystery|Thriller","Comedy|Drama|Fantasy","Action|Drama|Thriller","Action|Adventure|Fantasy","Action|Adventure|Thriller","Action|Crime|Drama","Action|Adventure|Thriller|IMAX","Action|Adventure|Drama|War","Crime|Drama|Mystery|Romance|Thriller","Action|Romance|Sci-Fi|Thriller","Action|Crime|Drama|Thriller","Comedy|Drama","Animation|Comedy|Fantasy|Musical","Crime|Drama|Mystery|Thriller","Action|Adventure","Comedy|Drama","Action|Crime|Horror|Sci-Fi|Thriller","Horror|Thriller","Horror|Thriller","Comedy|Drama|Romance","Children|Comedy|Fantasy"]],"container":"<table class=\"display\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>userId<\/th>\n      <th>movieId<\/th>\n      <th>rating<\/th>\n      <th>timestamp<\/th>\n      <th>title<\/th>\n      <th>genres<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"columnDefs":[{"className":"dt-right","targets":[1,2,3,4]},{"orderable":false,"targets":0}],"order":[],"autoWidth":false,"orderClasses":false}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->

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
checking subsets of size 1 2 done [0.09s].
writing ... [249409 rule(s)] done [0.06s].
creating S4 object  ... done [0.03s].

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

<!--html_preserve--><div id="htmlwidget-0abfe183e4515077d1c1" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-0abfe183e4515077d1c1">{"x":{"filter":"none","data":[["1","2","3","4","5","6","7","8","9","10","11","12"],["{2571} =&gt; {1196}","{2571} =&gt; {480}","{2571} =&gt; {6539}","{2571} =&gt; {260}","{2571} =&gt; {2959}","{2571} =&gt; {7153}","{2571} =&gt; {4993}","{2571} =&gt; {593}","{2571} =&gt; {5952}","{2571} =&gt; {356}","{2571} =&gt; {296}","{2571} =&gt; {318}"],[1.20945168486556,1.19930177812314,1.18847853426096,1.18187923218983,1.17191127948185,1.16517917371496,1.1650758991571,1.16210356023413,1.15640578140202,1.1304154975074,1.1199070049135,1.11424491442647],[0.554524361948956,0.564965197215777,0.554524361948956,0.568445475638051,0.619489559164733,0.604408352668213,0.657772621809745,0.556844547563805,0.620649651972158,0.631090487238979,0.617169373549884,0.564965197215777],[0.715568862275449,0.729041916167665,0.715568862275449,0.733532934131736,0.79940119760479,0.779940119760479,0.848802395209581,0.718562874251497,0.800898203592814,0.81437125748503,0.796407185628742,0.729041916167665],[2571,2571,2571,2571,2571,2571,2571,2571,2571,2571,2571,2571],["Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)"],[1196,480,6539,260,2959,7153,4993,593,5952,356,296,318],["Star Wars: Episode V - The Empire Strikes Back (1980)","Jurassic Park (1993)","Pirates of the Caribbean: The Curse of the Black Pearl (2003)","Star Wars: Episode IV - A New Hope (1977)","Fight Club (1999)","Lord of the Rings: The Return of the King, The (2003)","Lord of the Rings: The Fellowship of the Ring, The (2001)","Silence of the Lambs, The (1991)","Lord of the Rings: The Two Towers, The (2002)","Forrest Gump (1994)","Pulp Fiction (1994)","Shawshank Redemption, The (1994)"]],"container":"<table class=\"display\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>rules<\/th>\n      <th>lift<\/th>\n      <th>support<\/th>\n      <th>confidence<\/th>\n      <th>source_movieId<\/th>\n      <th>source_title<\/th>\n      <th>recom_movieId<\/th>\n      <th>recom_title<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"columnDefs":[{"className":"dt-right","targets":[2,3,4,5,7]},{"orderable":false,"targets":0}],"order":[],"autoWidth":false,"orderClasses":false,"rowCallback":"function(row, data) {\nDTWidget.formatRound(this, row, data, 2, 3);\nDTWidget.formatRound(this, row, data, 3, 3);\nDTWidget.formatRound(this, row, data, 4, 3);\n}"}},"evals":["options.rowCallback"],"jsHooks":[]}</script><!--/html_preserve-->
