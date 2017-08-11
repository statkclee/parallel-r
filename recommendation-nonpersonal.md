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

<!--html_preserve--><div id="htmlwidget-b0e5f2cc69e75122d905" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-b0e5f2cc69e75122d905">{"x":{"filter":"none","data":[["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"],[13215,83891,127647,8932,48098,61276,3915,55679,37091,53930,26932,35246,58802,62805,43829,31921,2847,53930,111841,11343,107711,75195,43354,47150,42096,42124,18390,31362,41613,21050,79531,134964,60016,62805,114601,43354,83891,53113,23428,16472,82715,97384,82715,26480,121954,124448,60349,104958,3076,45811,128263,21860,115852,46809,2945,95708,77512,107087,115364,128263,45619,132187,98781,31444,1935,96482,24112,129078,91478,31321,27838,117144,45619,49830,49642,61305,97953,42245,97163,16581,22338,12778,49455,36727,32780,16766,48821,74849,82880,53680,66362,54989,84549,79601,13565,10164,52520,131331,50898,131439],[8665,3275,3707,1917,8644,44195,6305,588,2542,5872,68791,3753,594,3977,68319,7285,597,2881,1097,2989,69122,105,6595,4022,3785,1042,1721,4306,362,4370,2064,231,7293,2421,54503,45499,945,1196,7360,32587,8368,2067,44694,2094,223,141,344,1232,1198,3996,1784,44191,4874,49530,527,1276,2082,5294,2291,48516,34150,6863,49272,3198,4027,407,3698,4223,33794,56152,164,3841,3683,1333,778,59784,8641,2672,5690,315,3698,1391,1089,106920,1237,551,367,3809,1644,2424,1090,380,589,2059,3087,1831,2083,919,50,32587],[4,0.5,5,2.5,3,3,4,4.5,5,3,3.5,1,5,3,3,2.5,0.5,3,3,4,4,4.5,3,4.5,2.5,4,4.5,4.5,5,3.5,3,3,2,4,5,2.5,0.5,4.5,4,4.5,0.5,5,4,3,4,4,3,5,3,4.5,2,4.5,3,3.5,3.5,3.5,2.5,4,3,3,1.5,4.5,3.5,5,2.5,4,2,3.5,4.5,3,3.5,2,3.5,4.5,3.5,4,3,3,4,1.5,3,2.5,4.5,3,5,3,4,3,2.5,5,4,2,4,4,3.5,2,2.5,3.5,4,3.5],[1205014723,1370462647,1175010588,1214928046,1410776281,1232180131,1096111613,1176474647,1069480645,1133798102,1246354900,1085178544,1162865616,1031820914,1241726044,1241723849,1193593309,1051488240,1245684670,1154283324,1276302269,1167554534,1276465591,1257437710,1302228621,1196507298,1158782417,1222472696,958885945,1230070951,949754476,1304890789,1424840015,1031821459,1281710288,1276463870,1370460918,1360176456,1317218679,1150487594,1175512490,1225339214,1175511105,1229119977,1170309441,1333228276,1312061673,1287614512,1188263775,1169264124,1214180682,1150757209,1112031419,1389555249,1086449393,1311577514,1118054061,1356873504,1202646064,1389385470,1149048321,1096643280,1195951267,1359062152,1224377087,1298895622,1044495745,1088226246,1289007188,1226339682,1131448774,998692570,1149447094,1119369466,1152575511,1230973586,1274159637,1354792877,1209321910,1336565369,1421185868,1134497315,1180633160,1399250670,1196198639,1288245373,950947300,1024409190,1185836090,1156123439,1313279198,1160174455,1122807204,1130720611,1388594174,1051409147,1325458480,1294685560,1077304553,1140388936],["Bourne Supremacy, The (2004)","Boondock Saints, The (2000)","9 1/2 Weeks (Nine 1/2 Weeks) (1986)","Armageddon (1998)","I, Robot (2004)","Thank You for Smoking (2006)","Fahrenheit 451 (1966)","Aladdin (1992)","Lock, Stock &amp; Two Smoking Barrels (1998)","Die Another Day (2002)","Terminator Salvation (2009)","Patriot, The (2000)","Snow White and the Seven Dwarfs (1937)","Charlie's Angels (2000)","X-Men Origins: Wolverine (2009)","Thirteen (2003)","Pretty Woman (1990)","Double Jeopardy (1999)","E.T. the Extra-Terrestrial (1982)","For Your Eyes Only (1981)","Hangover, The (2009)","Bridges of Madison County, The (1995)","S.W.A.T. (2003)","Cast Away (2000)","Scary Movie (2000)","That Thing You Do! (1996)","Titanic (1997)","Shrek (2001)","Jungle Book, The (1994)","A.I. Artificial Intelligence (2001)","Roger &amp; Me (1989)","Dumb &amp; Dumber (Dumb and Dumber) (1994)","50 First Dates (2004)","Karate Kid, Part II, The (1986)","Superbad (2007)","X-Men: The Last Stand (2006)","Top Hat (1935)","Star Wars: Episode V - The Empire Strikes Back (1980)","Dawn of the Dead (2004)","Sin City (2005)","Harry Potter and the Prisoner of Azkaban (2004)","Doctor Zhivago (1965)","Volver (2006)","Rocketeer, The (1991)","Clerks (1994)","Birdcage, The (1996)","Ace Ventura: Pet Detective (1994)","Stalker (1979)","Raiders of the Lost Ark (Indiana Jones and the Raiders of the Lost Ark) (1981)","Crouching Tiger, Hidden Dragon (Wo hu cang long) (2000)","As Good as It Gets (1997)","V for Vendetta (2006)","K-PAX (2001)","Blood Diamond (2006)","Schindler's List (1993)","Cool Hand Luke (1967)","Mighty Ducks, The (1992)","Frailty (2001)","Edward Scissorhands (1990)","Departed, The (2006)","Fantastic Four (2005)","School of Rock (2003)","Casino Royale (2006)","Papillon (1973)","O Brother, Where Art Thou? (2000)","In the Mouth of Madness (1995)","Running Man, The (1987)","Enemy at the Gates (2001)","Batman Begins (2005)","Enchanted (2007)","Devil in a Blue Dress (1995)","Air America (1990)","Blood Simple (1984)","Birds, The (1963)","Trainspotting (1996)","Kung Fu Panda (2008)","Anchorman: The Legend of Ron Burgundy (2004)","Thirteenth Floor, The (1999)","Grave of the Fireflies (Hotaru no haka) (1988)","Specialist, The (1994)","Running Man, The (1987)","Mars Attacks! (1996)","Reservoir Dogs (1992)","Her (2013)","Seventh Seal, The (Sjunde inseglet, Det) (1957)","Nightmare Before Christmas, The (1993)","Mask, The (1994)","What About Bob? (1991)","I Know What You Did Last Summer (1997)","You've Got Mail (1998)","Platoon (1986)","True Lies (1994)","Terminator 2: Judgment Day (1991)","Parent Trap, The (1998)","Scrooged (1988)","Lost in Space (1998)","Muppet Christmas Carol, The (1992)","Wizard of Oz, The (1939)","Usual Suspects, The (1995)","Sin City (2005)"],["Action|Crime|Thriller","Action|Crime|Drama|Thriller","Drama|Romance","Action|Romance|Sci-Fi|Thriller","Action|Adventure|Sci-Fi|Thriller","Comedy|Drama","Drama|Sci-Fi","Adventure|Animation|Children|Comedy|Musical","Comedy|Crime|Thriller","Action|Adventure|Thriller","Action|Adventure|Sci-Fi|Thriller","Action|Drama|War","Animation|Children|Drama|Fantasy|Musical","Action|Comedy","Action|Sci-Fi|Thriller","Drama","Comedy|Romance","Action|Crime|Drama|Thriller","Children|Drama|Sci-Fi","Action|Adventure|Thriller","Comedy|Crime","Drama|Romance","Action|Thriller","Drama","Comedy|Horror","Comedy|Drama","Drama|Romance","Adventure|Animation|Children|Comedy|Fantasy|Romance","Adventure|Children|Romance","Adventure|Drama|Sci-Fi","Documentary","Adventure|Comedy","Comedy|Romance","Action|Adventure|Drama","Comedy","Action|Sci-Fi|Thriller","Comedy|Musical|Romance","Action|Adventure|Sci-Fi","Action|Drama|Horror|Thriller","Action|Crime|Film-Noir|Mystery|Thriller","Adventure|Fantasy|IMAX","Drama|Romance|War","Comedy|Drama","Action|Adventure|Sci-Fi","Comedy","Comedy","Comedy","Drama|Mystery|Sci-Fi","Action|Adventure","Action|Drama|Romance","Comedy|Drama|Romance","Action|Sci-Fi|Thriller|IMAX","Drama|Fantasy|Mystery|Sci-Fi","Action|Adventure|Crime|Drama|Thriller|War","Drama|War","Drama","Children|Comedy","Crime|Drama|Thriller","Drama|Fantasy|Romance","Crime|Drama|Thriller","Action|Adventure|Sci-Fi","Comedy|Musical","Action|Adventure|Thriller","Crime|Drama","Adventure|Comedy|Crime","Horror|Thriller","Action|Sci-Fi","Drama|War","Action|Crime|IMAX","Adventure|Animation|Children|Comedy|Fantasy|Musical|Romance","Crime|Film-Noir|Mystery|Thriller","Action|Comedy","Crime|Drama|Film-Noir","Horror|Thriller","Comedy|Crime|Drama","Action|Animation|Children|Comedy|IMAX","Comedy","Drama|Sci-Fi|Thriller","Animation|Drama|War","Action|Drama|Thriller","Action|Sci-Fi","Action|Comedy|Sci-Fi","Crime|Mystery|Thriller","Drama|Romance|Sci-Fi","Drama","Animation|Children|Fantasy|Musical","Action|Comedy|Crime|Fantasy","Comedy","Horror|Mystery|Thriller","Comedy|Romance","Drama|War","Action|Adventure|Comedy|Romance|Thriller","Action|Sci-Fi","Children|Comedy|Romance","Comedy|Fantasy|Romance","Action|Adventure|Sci-Fi","Children|Comedy|Musical","Adventure|Children|Fantasy|Musical","Crime|Mystery|Thriller","Action|Crime|Film-Noir|Mystery|Thriller"]],"container":"<table class=\"display\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>userId<\/th>\n      <th>movieId<\/th>\n      <th>rating<\/th>\n      <th>timestamp<\/th>\n      <th>title<\/th>\n      <th>genres<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"crosstalkOptions":{"key":null,"group":null},"columnDefs":[{"className":"dt-right","targets":[1,2,3,4]},{"orderable":false,"targets":0}],"order":[],"autoWidth":false,"orderClasses":false},"selection":{"mode":"multiple","selected":null,"target":"row"}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->

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
     <dbl>                            <chr>             <dbl>
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
checking subsets of size 1 2 done [0.12s].
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

<!--html_preserve--><div id="htmlwidget-d8cedbee6e38d909ac30" style="width:100%;height:auto;" class="datatables html-widget"></div>
<script type="application/json" data-for="htmlwidget-d8cedbee6e38d909ac30">{"x":{"filter":"none","data":[["1","2","3","4","5","6","7","8","9","10","11","12"],["{2571} =&gt; {1196}","{2571} =&gt; {480}","{2571} =&gt; {6539}","{2571} =&gt; {260}","{2571} =&gt; {2959}","{2571} =&gt; {7153}","{2571} =&gt; {4993}","{2571} =&gt; {593}","{2571} =&gt; {5952}","{2571} =&gt; {356}","{2571} =&gt; {296}","{2571} =&gt; {318}"],[1.20945168486556,1.19930177812314,1.18847853426096,1.18187923218983,1.17191127948185,1.16517917371496,1.1650758991571,1.16210356023413,1.15640578140202,1.1304154975074,1.1199070049135,1.11424491442647],[0.554524361948956,0.564965197215777,0.554524361948956,0.568445475638051,0.619489559164733,0.604408352668213,0.657772621809745,0.556844547563805,0.620649651972158,0.631090487238979,0.617169373549884,0.564965197215777],[0.715568862275449,0.729041916167665,0.715568862275449,0.733532934131736,0.79940119760479,0.779940119760479,0.848802395209581,0.718562874251497,0.800898203592814,0.81437125748503,0.796407185628742,0.729041916167665],[2571,2571,2571,2571,2571,2571,2571,2571,2571,2571,2571,2571],["Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)","Matrix, The (1999)"],[1196,480,6539,260,2959,7153,4993,593,5952,356,296,318],["Star Wars: Episode V - The Empire Strikes Back (1980)","Jurassic Park (1993)","Pirates of the Caribbean: The Curse of the Black Pearl (2003)","Star Wars: Episode IV - A New Hope (1977)","Fight Club (1999)","Lord of the Rings: The Return of the King, The (2003)","Lord of the Rings: The Fellowship of the Ring, The (2001)","Silence of the Lambs, The (1991)","Lord of the Rings: The Two Towers, The (2002)","Forrest Gump (1994)","Pulp Fiction (1994)","Shawshank Redemption, The (1994)"]],"container":"<table class=\"display\">\n  <thead>\n    <tr>\n      <th> <\/th>\n      <th>rules<\/th>\n      <th>lift<\/th>\n      <th>support<\/th>\n      <th>confidence<\/th>\n      <th>source_movieId<\/th>\n      <th>source_title<\/th>\n      <th>recom_movieId<\/th>\n      <th>recom_title<\/th>\n    <\/tr>\n  <\/thead>\n<\/table>","options":{"crosstalkOptions":{"key":null,"group":null},"columnDefs":[{"className":"dt-right","targets":[2,3,4,5,7]},{"orderable":false,"targets":0}],"order":[],"autoWidth":false,"orderClasses":false,"rowCallback":"function(row, data) {\nDTWidget.formatRound(this, row, data, 2, 3, 3, ',', '.');\nDTWidget.formatRound(this, row, data, 3, 3, 3, ',', '.');\nDTWidget.formatRound(this, row, data, 4, 3, 3, ',', '.');\n}"},"selection":{"mode":"multiple","selected":null,"target":"row"}},"evals":["options.rowCallback"],"jsHooks":[]}</script><!--/html_preserve-->
