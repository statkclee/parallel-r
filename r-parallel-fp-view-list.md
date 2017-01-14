# 데이터 과학




> ## 학습 목표 {.objectives}
>
> * 리스트 자료형 내부를 샅샅이 살펴본다.
> * `str` 함수로 리스트 자료형을 훑어보는 기법을 살펴본다.
> * 도구 `listviewer` 팩키지를 통해 리스트 자료형을 탐색한다.


## 1. 리스트 살펴보기 [^jennybc-purrr-listviewer]

[^jennybc-purrr-listviewer]: [Explore the example lists: Wes Anderson, Game of Thrones, GitHub](https://jennybc.github.io/purrr-tutorial/ls00_inspect-explore.html)

함수형 프로그래밍을 통해 다양한 `*apply` 계열 혹은 `map` 계열 함수를 적용시키기 전에
데이터가 리스트인 경우 리스트를 살펴보는 것이 필요하다.

- 리스트 길이가 얼마나 되는지?
- 리스트 내부 벡터는 동일한 자료형인가? 다르면 각 벡터는 어떤 자료형인가?
- 리스트 자체 뿐만 아니라, 리스트 내부 벡터 길이, 벡터명, 자료형은 각각 어떻게 되는지 파악해야 된다.

이런 문제에 봉착하는 것은 당연하다. 예를 들어 회귀분석 결과 산출되는 
`lm()` 함수 산출물 내부를 이런 관점으로 본적이 있는가? 혹은 API가 대충 되어 있는 
웹사이트에서 데이터를 긁어 온 경우, 추가 데이터 분석을 위해 
데이터 내부를 까보고 이를 바탕으로 자료분석이 가능한 형태로 변형해야 된다.

### 1.1. `str()` 함수

`str()` 함수가 언제가 가장 먼저 생각할 수 있는 것인데,
리스트 객체를 넣어 데이터구조를 파악하는 것이 데이터프레임을 넣는 경우와 비교해도 
그다지 결과물 해석이 쉽지 않다. 예를 들어 공간정보 데이터 `.shp` 파일을 
R로 불러들일 경우 이를 `str` 명령어로 들여다 보면 그 이유를 알 수 있다.

이런 문제점에 대한 해법으로 `max.level`, `list.len` 인자를 `str()` 함수에 넣어 
구조를 살펴보고, 필요한 내용을 찾아내서 `[`, `[[` 꺾쇠괄호를 사용해서 뽑아내는 
방식이 동원된다: `str(..., list.len = x, max.level = y)[[1]]`

### 1.2. 리스트 데이터

`repurrrsive` 팩키지에 예제 리스트 데이터가 담겨있다.

- wesanderson : 색상 팔레트 데이터 (리스트 자료형)
- Game of Thrones : 왕좌의 게임 캐릭터 데이터 (리스트 자료형)
- GitHub: GitHub 사용자와 저장소 데이터 (리스트 자료형)

## 2. `listviewer` 팩키지 활용 살펴보기

인터랙티브 위젯을 활용하여 리스트 자료형을 살펴보면 도움이 많이 된다.
`listviewer::jsonedit(got_chars, mode = "view")` 와 같이 명령어를 넣어
리스트 자료형을 갖는 왕좌의 게임에 등장하는 캐릭터를 살펴볼 수 있다.

### 2.1. 환경설정

리스트 예제 데이터는 `devtools::install_github("jennybc/repurrrsive")` 명령어를 통해 왕좌의 게임을 포함한 데이터를 불러들인다.
인터랙티브 위젯기능을 활용하여 리스트 데이터를 살펴보기 위해서 `listviewer` 팩키지를 설치해야만 되는데,
`reactR` 팩키지가 사전에 설치되어야 하는 의존성이 있어 함께 설치한다.


~~~{.r}
library(purrr)
library(repurrrsive) # devtools::install_github("jennybc/repurrrsive")
library(listviewer) # devtools::install_github('timelyportfolio/reactR')
~~~

### 2.2. 리스트 자료형 살펴보기

리스트형으로 된 색상 팔레트 데이터 (`wesanderson`), 왕좌의 게임 캐릭터 데이터 (`Game of Thrones`),
GitHub 사용자와 저장소 데이터 (`gh_users`) 각각을 전통적인 `str` 명령어와 `listviewer` 팩키지 `jsonedit`
명령어와 함께 살펴본다.


~~~{.r}
# 1. 리스트 살펴보기 ----------------------------------------------------
# 1.1. wesanderson 리스트 뷰어

str(wesanderson)
~~~



~~~{.output}
#> List of 15
#>  $ GrandBudapest : chr [1:4] "#F1BB7B" "#FD6467" "#5B1A18" "#D67236"
#>  $ Moonrise1     : chr [1:4] "#F3DF6C" "#CEAB07" "#D5D5D3" "#24281A"
#>  $ Royal1        : chr [1:4] "#899DA4" "#C93312" "#FAEFD1" "#DC863B"
#>  $ Moonrise2     : chr [1:4] "#798E87" "#C27D38" "#CCC591" "#29211F"
#>  $ Cavalcanti    : chr [1:5] "#D8B70A" "#02401B" "#A2A475" "#81A88D" ...
#>  $ Royal2        : chr [1:5] "#9A8822" "#F5CDB4" "#F8AFA8" "#FDDDA0" ...
#>  $ GrandBudapest2: chr [1:4] "#E6A0C4" "#C6CDF7" "#D8A499" "#7294D4"
#>  $ Moonrise3     : chr [1:5] "#85D4E3" "#F4B5BD" "#9C964A" "#CDC08C" ...
#>  $ Chevalier     : chr [1:4] "#446455" "#FDD262" "#D3DDDC" "#C7B19C"
#>  $ Zissou        : chr [1:5] "#3B9AB2" "#78B7C5" "#EBCC2A" "#E1AF00" ...
#>  $ FantasticFox  : chr [1:5] "#DD8D29" "#E2D200" "#46ACC8" "#E58601" ...
#>  $ Darjeeling    : chr [1:5] "#FF0000" "#00A08A" "#F2AD00" "#F98400" ...
#>  $ Rushmore      : chr [1:5] "#E1BD6D" "#EABE94" "#0B775E" "#35274A" ...
#>  $ BottleRocket  : chr [1:7] "#A42820" "#5F5647" "#9B110E" "#3F5151" ...
#>  $ Darjeeling2   : chr [1:5] "#ECCBAE" "#046C9A" "#D69C4E" "#ABDDDE" ...

~~~



~~~{.r}
jsonedit(wesanderson, mode = "view", elementId = "wesanderson")
~~~

<!--html_preserve--><div id="wesanderson" style="width:672px;height:480px;" class="jsonedit html-widget"></div>
<script type="application/json" data-for="wesanderson">{"x":{"data":{"GrandBudapest":["#F1BB7B","#FD6467","#5B1A18","#D67236"],"Moonrise1":["#F3DF6C","#CEAB07","#D5D5D3","#24281A"],"Royal1":["#899DA4","#C93312","#FAEFD1","#DC863B"],"Moonrise2":["#798E87","#C27D38","#CCC591","#29211F"],"Cavalcanti":["#D8B70A","#02401B","#A2A475","#81A88D","#972D15"],"Royal2":["#9A8822","#F5CDB4","#F8AFA8","#FDDDA0","#74A089"],"GrandBudapest2":["#E6A0C4","#C6CDF7","#D8A499","#7294D4"],"Moonrise3":["#85D4E3","#F4B5BD","#9C964A","#CDC08C","#FAD77B"],"Chevalier":["#446455","#FDD262","#D3DDDC","#C7B19C"],"Zissou":["#3B9AB2","#78B7C5","#EBCC2A","#E1AF00","#F21A00"],"FantasticFox":["#DD8D29","#E2D200","#46ACC8","#E58601","#B40F20"],"Darjeeling":["#FF0000","#00A08A","#F2AD00","#F98400","#5BBCD6"],"Rushmore":["#E1BD6D","#EABE94","#0B775E","#35274A","#F2300F"],"BottleRocket":["#A42820","#5F5647","#9B110E","#3F5151","#4E2A1E","#550307","#0C1707"],"Darjeeling2":["#ECCBAE","#046C9A","#D69C4E","#ABDDDE","#000000"]},"options":{"mode":"view","modes":["code","form","text","tree","view"]}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->

~~~{.r}

# 1.2. Game of Thrones 캐릭터 리스트 뷰어
str(got_chars, list.len = 3)
~~~



~~~{.output}
#> List of 29
#>  $ :List of 18
#>   ..$ url        : chr "http://www.anapioficeandfire.com/api/characters/1022"
#>   ..$ id         : int 1022
#>   ..$ name       : chr "Theon Greyjoy"
#>   .. [list output truncated]
#>  $ :List of 18
#>   ..$ url        : chr "http://www.anapioficeandfire.com/api/characters/1052"
#>   ..$ id         : int 1052
#>   ..$ name       : chr "Tyrion Lannister"
#>   .. [list output truncated]
#>  $ :List of 18
#>   ..$ url        : chr "http://www.anapioficeandfire.com/api/characters/1074"
#>   ..$ id         : int 1074
#>   ..$ name       : chr "Victarion Greyjoy"
#>   .. [list output truncated]
#>   [list output truncated]

~~~



~~~{.r}
str(got_chars[[1]], list.len = 8)
~~~



~~~{.output}
#> List of 18
#>  $ url        : chr "http://www.anapioficeandfire.com/api/characters/1022"
#>  $ id         : int 1022
#>  $ name       : chr "Theon Greyjoy"
#>  $ gender     : chr "Male"
#>  $ culture    : chr "Ironborn"
#>  $ born       : chr "In 278 AC or 279 AC, at Pyke"
#>  $ died       : chr ""
#>  $ alive      : logi TRUE
#>   [list output truncated]

~~~



~~~{.r}

jsonedit(number_unnamed(got_chars), mode = "view", elementId = "got_chars")
~~~

<!--html_preserve--><div id="got_chars" style="width:672px;height:480px;" class="jsonedit html-widget"></div>
<script type="application/json" data-for="got_chars">{"x":{"data":{"1":{"url":"http://www.anapioficeandfire.com/api/characters/1022","id":1022,"name":"Theon Greyjoy","gender":"Male","culture":"Ironborn","born":"In 278 AC or 279 AC, at Pyke","died":"","alive":true,"titles":{"1":"Prince of Winterfell","2":"Captain of Sea Bitch","3":"Lord of the Iron Islands (by law of the green lands)"},"aliases":{"1":"Prince of Fools","2":"Theon Turncloak","3":"Reek","4":"Theon Kinslayer"},"father":"","mother":"","spouse":"","allegiances":"House Greyjoy of Pyke","books":{"1":"A Game of Thrones","2":"A Storm of Swords","3":"A Feast for Crows"},"povBooks":{"1":"A Clash of Kings","2":"A Dance with Dragons"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 5","6":"Season 6"},"playedBy":"Alfie Allen"},"2":{"url":"http://www.anapioficeandfire.com/api/characters/1052","id":1052,"name":"Tyrion Lannister","gender":"Male","culture":"","born":"In 273 AC, at Casterly Rock","died":"","alive":true,"titles":{"1":"Acting Hand of the King (former)","2":"Master of Coin (former)"},"aliases":{"1":"The Imp","2":"Halfman","3":"The boyman","4":"Giant of Lannister","5":"Lord Tywin's Doom","6":"Lord Tywin's Bane","7":"Yollo","8":"Hugor Hill","9":"No-Nose","10":"Freak","11":"Dwarf"},"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/2044","allegiances":"House Lannister of Casterly Rock","books":{"1":"A Feast for Crows","2":"The World of Ice and Fire"},"povBooks":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Dance with Dragons"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 5","6":"Season 6"},"playedBy":"Peter Dinklage"},"3":{"url":"http://www.anapioficeandfire.com/api/characters/1074","id":1074,"name":"Victarion Greyjoy","gender":"Male","culture":"Ironborn","born":"In 268 AC or before, at Pyke","died":"","alive":true,"titles":{"1":"Lord Captain of the Iron Fleet","2":"Master of the Iron Victory"},"aliases":"The Iron Captain","father":"","mother":"","spouse":"","allegiances":"House Greyjoy of Pyke","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords"},"povBooks":{"1":"A Feast for Crows","2":"A Dance with Dragons"},"tvSeries":[],"playedBy":[]},"4":{"url":"http://www.anapioficeandfire.com/api/characters/1109","id":1109,"name":"Will","gender":"Male","culture":"","born":"","died":"In 297 AC, at Haunted Forest","alive":false,"titles":[],"aliases":[],"father":"","mother":"","spouse":"","allegiances":[],"books":"A Clash of Kings","povBooks":"A Game of Thrones","tvSeries":[],"playedBy":"Bronson Webb"},"5":{"url":"http://www.anapioficeandfire.com/api/characters/1166","id":1166,"name":"Areo Hotah","gender":"Male","culture":"Norvoshi","born":"In 257 AC or before, at Norvos","died":"","alive":true,"titles":"Captain of the Guard at Sunspear","aliases":[],"father":"","mother":"","spouse":"","allegiances":"House Nymeros Martell of Sunspear","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords"},"povBooks":{"1":"A Feast for Crows","2":"A Dance with Dragons"},"tvSeries":{"1":"Season 5","2":"Season 6"},"playedBy":"DeObia Oparei"},"6":{"url":"http://www.anapioficeandfire.com/api/characters/1267","id":1267,"name":"Chett","gender":"Male","culture":"","born":"At Hag's Mire","died":"In 299 AC, at Fist of the First Men","alive":false,"titles":[],"aliases":[],"father":"","mother":"","spouse":"","allegiances":[],"books":{"1":"A Game of Thrones","2":"A Clash of Kings"},"povBooks":"A Storm of Swords","tvSeries":[],"playedBy":[]},"7":{"url":"http://www.anapioficeandfire.com/api/characters/1295","id":1295,"name":"Cressen","gender":"Male","culture":"","born":"In 219 AC or 220 AC","died":"In 299 AC, at Dragonstone","alive":false,"titles":"Maester","aliases":[],"father":"","mother":"","spouse":"","allegiances":[],"books":{"1":"A Storm of Swords","2":"A Feast for Crows"},"povBooks":"A Clash of Kings","tvSeries":"Season 2","playedBy":"Oliver Ford"},"8":{"url":"http://www.anapioficeandfire.com/api/characters/130","id":130,"name":"Arianne Martell","gender":"Female","culture":"Dornish","born":"In 276 AC, at Sunspear","died":"","alive":true,"titles":"Princess of Dorne","aliases":[],"father":"","mother":"","spouse":"","allegiances":"House Nymeros Martell of Sunspear","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Dance with Dragons"},"povBooks":"A Feast for Crows","tvSeries":[],"playedBy":[]},"9":{"url":"http://www.anapioficeandfire.com/api/characters/1303","id":1303,"name":"Daenerys Targaryen","gender":"Female","culture":"Valyrian","born":"In 284 AC, at Dragonstone","died":"","alive":true,"titles":{"1":"Queen of the Andals and the Rhoynar and the First Men, Lord of the Seven Kingdoms","2":"Khaleesi of the Great Grass Sea","3":"Breaker of Shackles/Chains","4":"Queen of Meereen","5":"Princess of Dragonstone"},"aliases":{"1":"Dany","2":"Daenerys Stormborn","3":"The Unburnt","4":"Mother of Dragons","5":"Mother","6":"Mhysa","7":"The Silver Queen","8":"Silver Lady","9":"Dragonmother","10":"The Dragon Queen","11":"The Mad King's daughter"},"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/1346","allegiances":"House Targaryen of King's Landing","books":"A Feast for Crows","povBooks":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Dance with Dragons"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 5","6":"Season 6"},"playedBy":"Emilia Clarke"},"10":{"url":"http://www.anapioficeandfire.com/api/characters/1319","id":1319,"name":"Davos Seaworth","gender":"Male","culture":"Westeros","born":"In 260 AC or before, at King's Landing","died":"","alive":true,"titles":{"1":"Ser","2":"Lord of the Rainwood","3":"Admiral of the Narrow Sea","4":"Hand of the King"},"aliases":{"1":"Onion Knight","2":"Davos Shorthand","3":"Ser Onions","4":"Onion Lord","5":"Smuggler"},"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/1676","allegiances":{"1":"House Baratheon of Dragonstone","2":"House Seaworth of Cape Wrath"},"books":"A Feast for Crows","povBooks":{"1":"A Clash of Kings","2":"A Storm of Swords","3":"A Dance with Dragons"},"tvSeries":{"1":"Season 2","2":"Season 3","3":"Season 4","4":"Season 5","5":"Season 6"},"playedBy":"Liam Cunningham"},"11":{"url":"http://www.anapioficeandfire.com/api/characters/148","id":148,"name":"Arya Stark","gender":"Female","culture":"Northmen","born":"In 289 AC, at Winterfell","died":"","alive":true,"titles":"Princess","aliases":{"1":"Arya Horseface","2":"Arya Underfoot","3":"Arry","4":"Lumpyface","5":"Lumpyhead","6":"Stickboy","7":"Weasel","8":"Nymeria","9":"Squan","10":"Saltb","11":"Cat of the Canaly","12":"Bets","13":"The Blind Girh","14":"The Ugly Little Girl","15":"Mercedenl","16":"Mercye"},"father":"","mother":"","spouse":"","allegiances":"House Stark of Winterfell","books":[],"povBooks":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Feast for Crows","5":"A Dance with Dragons"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 5","6":"Season 6"},"playedBy":"Maisie Williams"},"12":{"url":"http://www.anapioficeandfire.com/api/characters/149","id":149,"name":"Arys Oakheart","gender":"Male","culture":"Reach","born":"At Old Oak","died":"In 300 AC, at the Greenblood","alive":false,"titles":"Ser","aliases":[],"father":"","mother":"","spouse":"","allegiances":"House Oakheart of Old Oak","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Dance with Dragons"},"povBooks":"A Feast for Crows","tvSeries":[],"playedBy":[]},"13":{"url":"http://www.anapioficeandfire.com/api/characters/150","id":150,"name":"Asha Greyjoy","gender":"Female","culture":"Ironborn","born":"In 275 AC or 276 AC, at Pyke","died":"","alive":true,"titles":{"1":"Princess","2":"Captain of the Black Wind","3":"Conqueror of Deepwood Motte"},"aliases":{"1":"Esgred","2":"The Kraken's Daughter"},"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/1372","allegiances":{"1":"House Greyjoy of Pyke","2":"House Ironmaker"},"books":{"1":"A Game of Thrones","2":"A Clash of Kings"},"povBooks":{"1":"A Feast for Crows","2":"A Dance with Dragons"},"tvSeries":{"1":"Season 2","2":"Season 3","3":"Season 4"},"playedBy":"Gemma Whelan"},"14":{"url":"http://www.anapioficeandfire.com/api/characters/168","id":168,"name":"Barristan Selmy","gender":"Male","culture":"Westeros","born":"In 237 AC","died":"","alive":true,"titles":{"1":"Ser","2":"Hand of the Queen"},"aliases":{"1":"Barristan the Bold","2":"Arstan Whitebeard","3":"Ser Grandfather","4":"Barristan the Old","5":"Old Ser"},"father":"","mother":"","spouse":"","allegiances":{"1":"House Selmy of Harvest Hall","2":"House Targaryen of King's Landing"},"books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Feast for Crows","5":"The World of Ice and Fire"},"povBooks":"A Dance with Dragons","tvSeries":{"1":"Season 1","2":"Season 3","3":"Season 4","4":"Season 5"},"playedBy":"Ian McElhinney"},"15":{"url":"http://www.anapioficeandfire.com/api/characters/2066","id":2066,"name":"Varamyr","gender":"Male","culture":"Free Folk","born":"At a village Beyond the Wall","died":"In 300 AC, at a village Beyond the Wall","alive":false,"titles":[],"aliases":{"1":"Varamyr Sixskins","2":"Haggon","3":"Lump"},"father":"","mother":"","spouse":"","allegiances":[],"books":"A Storm of Swords","povBooks":"A Dance with Dragons","tvSeries":[],"playedBy":[]},"16":{"url":"http://www.anapioficeandfire.com/api/characters/208","id":208,"name":"Brandon Stark","gender":"Male","culture":"Northmen","born":"In 290 AC, at Winterfell","died":"","alive":true,"titles":"Prince of Winterfell","aliases":{"1":"Bran","2":"Bran the Broken","3":"The Winged Wolf"},"father":"","mother":"","spouse":"","allegiances":"House Stark of Winterfell","books":"A Feast for Crows","povBooks":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Dance with Dragons"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 6"},"playedBy":"Isaac Hempstead-Wright"},"17":{"url":"http://www.anapioficeandfire.com/api/characters/216","id":216,"name":"Brienne of Tarth","gender":"Female","culture":"","born":"In 280 AC","died":"","alive":true,"titles":[],"aliases":{"1":"The Maid of Tarth","2":"Brienne the Beauty","3":"Brienne the Blue"},"father":"","mother":"","spouse":"","allegiances":{"1":"House Baratheon of Storm's End","2":"House Stark of Winterfell","3":"House Tarth of Evenfall Hall"},"books":{"1":"A Clash of Kings","2":"A Storm of Swords","3":"A Dance with Dragons"},"povBooks":"A Feast for Crows","tvSeries":{"1":"Season 2","2":"Season 3","3":"Season 4","4":"Season 5","5":"Season 6"},"playedBy":"Gwendoline Christie"},"18":{"url":"http://www.anapioficeandfire.com/api/characters/232","id":232,"name":"Catelyn Stark","gender":"Female","culture":"Rivermen","born":"In 264 AC, at Riverrun","died":"In 299 AC, at the Twins","alive":false,"titles":"Lady of Winterfell","aliases":{"1":"Catelyn Tully","2":"Lady Stoneheart","3":"The Silent Sistet","4":"Mother Mercilesr","5":"The Hangwomans"},"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/339","allegiances":{"1":"House Stark of Winterfell","2":"House Tully of Riverrun"},"books":{"1":"A Feast for Crows","2":"A Dance with Dragons"},"povBooks":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3"},"playedBy":"Michelle Fairley"},"19":{"url":"http://www.anapioficeandfire.com/api/characters/238","id":238,"name":"Cersei Lannister","gender":"Female","culture":"Westerman","born":"In 266 AC, at Casterly Rock","died":"","alive":true,"titles":{"1":"Light of the West","2":"Queen Dowager","3":"Protector of the Realm","4":"Lady of Casterly Rock","5":"Queen Regent"},"aliases":[],"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/901","allegiances":"House Lannister of Casterly Rock","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords"},"povBooks":{"1":"A Feast for Crows","2":"A Dance with Dragons"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 5","6":"Season 6"},"playedBy":"Lena Headey"},"20":{"url":"http://www.anapioficeandfire.com/api/characters/339","id":339,"name":"Eddard Stark","gender":"Male","culture":"Northmen","born":"In 263 AC, at Winterfell","died":"In 299 AC, at Great Sept of Baelor in King's Landing","alive":false,"titles":{"1":"Lord of Winterfell","2":"Warden of the North","3":"Hand of the King","4":"Protector of the Realm","5":"Regent"},"aliases":{"1":"Ned","2":"The Ned","3":"The Quiet Wolf"},"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/232","allegiances":"House Stark of Winterfell","books":{"1":"A Clash of Kings","2":"A Storm of Swords","3":"A Feast for Crows","4":"A Dance with Dragons","5":"The World of Ice and Fire"},"povBooks":"A Game of Thrones","tvSeries":{"1":"Season 1","2":"Season 6"},"playedBy":{"1":"Sean Bean","2":"Sebastian Croft","3":"Robert Aramayo"}},"21":{"url":"http://www.anapioficeandfire.com/api/characters/529","id":529,"name":"Jaime Lannister","gender":"Male","culture":"Westerlands","born":"In 266 AC, at Casterly Rock","died":"","alive":true,"titles":{"1":"Ser","2":"Lord Commander of the Kingsguard","3":"Warden of the East (formerly)"},"aliases":{"1":"The Kingslayer","2":"The Lion of Lannister","3":"The Young Lion","4":"Cripple"},"father":"","mother":"","spouse":"","allegiances":"House Lannister of Casterly Rock","books":{"1":"A Game of Thrones","2":"A Clash of Kings"},"povBooks":{"1":"A Storm of Swords","2":"A Feast for Crows","3":"A Dance with Dragons"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 5"},"playedBy":"Nikolaj Coster-Waldau"},"22":{"url":"http://www.anapioficeandfire.com/api/characters/576","id":576,"name":"Jon Connington","gender":"Male","culture":"Stormlands","born":"In or between 263 AC and 265 AC","died":"","alive":true,"titles":{"1":"Lord of Griffin's Roost","2":"Hand of the King","3":"Hand of the True King"},"aliases":"Griffthe Mad King's Hand","father":"","mother":"","spouse":"","allegiances":{"1":"House Connington of Griffin's Roost","2":"House Targaryen of King's Landing"},"books":{"1":"A Storm of Swords","2":"A Feast for Crows","3":"The World of Ice and Fire"},"povBooks":"A Dance with Dragons","tvSeries":[],"playedBy":[]},"23":{"url":"http://www.anapioficeandfire.com/api/characters/583","id":583,"name":"Jon Snow","gender":"Male","culture":"Northmen","born":"In 283 AC","died":"","alive":true,"titles":"Lord Commander of the Night's Watch","aliases":{"1":"Lord Snow","2":"Ned Stark's Bastard","3":"The Snow of Winterfell","4":"The Crow-Come-Over","5":"The 998th Lord Commander of the Night's Watch","6":"The Bastard of Winterfell","7":"The Black Bastard of the Wall","8":"Lord Crow"},"father":"","mother":"","spouse":"","allegiances":"House Stark of Winterfell","books":"A Feast for Crows","povBooks":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Dance with Dragons"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 5","6":"Season 6"},"playedBy":"Kit Harington"},"24":{"url":"http://www.anapioficeandfire.com/api/characters/60","id":60,"name":"Aeron Greyjoy","gender":"Male","culture":"Ironborn","born":"In or between 269 AC and 273 AC, at Pyke","died":"","alive":true,"titles":{"1":"Priest of the Drowned God","2":"Captain of the Golden Storm (formerly)"},"aliases":{"1":"The Damphair","2":"Aeron Damphair"},"father":"","mother":"","spouse":"","allegiances":"House Greyjoy of Pyke","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Dance with Dragons"},"povBooks":"A Feast for Crows","tvSeries":"Season 6","playedBy":"Michael Feast"},"25":{"url":"http://www.anapioficeandfire.com/api/characters/605","id":605,"name":"Kevan Lannister","gender":"Male","culture":"","born":"In 244 AC","died":"In 300 AC, at King's Landing","alive":false,"titles":{"1":"Ser","2":"Master of laws","3":"Lord Regent","4":"Protector of the Realm"},"aliases":[],"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/327","allegiances":"House Lannister of Casterly Rock","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Feast for Crows"},"povBooks":"A Dance with Dragons","tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 5","4":"Season 6"},"playedBy":"Ian Gelder"},"26":{"url":"http://www.anapioficeandfire.com/api/characters/743","id":743,"name":"Melisandre","gender":"Female","culture":"Asshai","born":"At Unknown","died":"","alive":true,"titles":[],"aliases":{"1":"The Red Priestess","2":"The Red Woman","3":"The King's Red Shadow","4":"Lady Red","5":"Lot Seven"},"father":"","mother":"","spouse":"","allegiances":[],"books":{"1":"A Clash of Kings","2":"A Storm of Swords","3":"A Feast for Crows"},"povBooks":"A Dance with Dragons","tvSeries":{"1":"Season 2","2":"Season 3","3":"Season 4","4":"Season 5","5":"Season 6"},"playedBy":"Carice van Houten"},"27":{"url":"http://www.anapioficeandfire.com/api/characters/751","id":751,"name":"Merrett Frey","gender":"Male","culture":"Rivermen","born":"In 262 AC","died":"In 300 AC, at Near Oldstones","alive":false,"titles":[],"aliases":"Merrett Muttonhead","father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/712","allegiances":"House Frey of the Crossing","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Feast for Crows","4":"A Dance with Dragons"},"povBooks":"A Storm of Swords","tvSeries":[],"playedBy":[]},"28":{"url":"http://www.anapioficeandfire.com/api/characters/844","id":844,"name":"Quentyn Martell","gender":"Male","culture":"Dornish","born":"In 281 AC, at Sunspear, Dorne","died":"In 300 AC, at Meereen","alive":false,"titles":"Prince","aliases":{"1":"Frog","2":"Prince Frog","3":"The prince who came too late","4":"The Dragonrider"},"father":"","mother":"","spouse":"","allegiances":"House Nymeros Martell of Sunspear","books":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Feast for Crows"},"povBooks":"A Dance with Dragons","tvSeries":[],"playedBy":[]},"29":{"url":"http://www.anapioficeandfire.com/api/characters/957","id":957,"name":"Sansa Stark","gender":"Female","culture":"Northmen","born":"In 286 AC, at Winterfell","died":"","alive":true,"titles":"Princess","aliases":{"1":"Little bird","2":"Alayne Stone","3":"Jonquil"},"father":"","mother":"","spouse":"http://www.anapioficeandfire.com/api/characters/1052","allegiances":{"1":"House Baelish of Harrenhal","2":"House Stark of Winterfell"},"books":"A Dance with Dragons","povBooks":{"1":"A Game of Thrones","2":"A Clash of Kings","3":"A Storm of Swords","4":"A Feast for Crows"},"tvSeries":{"1":"Season 1","2":"Season 2","3":"Season 3","4":"Season 4","5":"Season 5","6":"Season 6"},"playedBy":"Sophie Turner"}},"options":{"mode":"view","modes":["code","form","text","tree","view"]}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->

~~~{.r}

# 1.3. GitHub 사용자 리스트 뷰어
str(gh_users, max.level = 1)
~~~



~~~{.output}
#> List of 6
#>  $ :List of 30
#>  $ :List of 30
#>  $ :List of 30
#>  $ :List of 30
#>  $ :List of 30
#>  $ :List of 30

~~~



~~~{.r}
jsonedit(number_unnamed(gh_users), mode = "view", elementId = "gh_users")
~~~

<!--html_preserve--><div id="gh_users" style="width:672px;height:480px;" class="jsonedit html-widget"></div>
<script type="application/json" data-for="gh_users">{"x":{"data":{"1":{"login":"gaborcsardi","id":660288,"avatar_url":"https://avatars.githubusercontent.com/u/660288?v=3","gravatar_id":"","url":"https://api.github.com/users/gaborcsardi","html_url":"https://github.com/gaborcsardi","followers_url":"https://api.github.com/users/gaborcsardi/followers","following_url":"https://api.github.com/users/gaborcsardi/following{/other_user}","gists_url":"https://api.github.com/users/gaborcsardi/gists{/gist_id}","starred_url":"https://api.github.com/users/gaborcsardi/starred{/owner}{/repo}","subscriptions_url":"https://api.github.com/users/gaborcsardi/subscriptions","organizations_url":"https://api.github.com/users/gaborcsardi/orgs","repos_url":"https://api.github.com/users/gaborcsardi/repos","events_url":"https://api.github.com/users/gaborcsardi/events{/privacy}","received_events_url":"https://api.github.com/users/gaborcsardi/received_events","type":"User","site_admin":false,"name":"Gábor Csárdi","company":"Mango Solutions, @MangoTheCat ","blog":"http://gaborcsardi.org","location":"Chippenham, UK","email":"csardi.gabor@gmail.com","hireable":[],"bio":[],"public_repos":52,"public_gists":6,"followers":303,"following":22,"created_at":"2011-03-09T17:29:25Z","updated_at":"2016-10-11T11:05:06Z"},"2":{"login":"jennybc","id":599454,"avatar_url":"https://avatars.githubusercontent.com/u/599454?v=3","gravatar_id":"","url":"https://api.github.com/users/jennybc","html_url":"https://github.com/jennybc","followers_url":"https://api.github.com/users/jennybc/followers","following_url":"https://api.github.com/users/jennybc/following{/other_user}","gists_url":"https://api.github.com/users/jennybc/gists{/gist_id}","starred_url":"https://api.github.com/users/jennybc/starred{/owner}{/repo}","subscriptions_url":"https://api.github.com/users/jennybc/subscriptions","organizations_url":"https://api.github.com/users/jennybc/orgs","repos_url":"https://api.github.com/users/jennybc/repos","events_url":"https://api.github.com/users/jennybc/events{/privacy}","received_events_url":"https://api.github.com/users/jennybc/received_events","type":"User","site_admin":false,"name":"Jennifer (Jenny) Bryan","company":"University of British Columbia","blog":"https://twitter.com/JennyBryan","location":"Vancouver, BC, Canada","email":[],"hireable":[],"bio":"prof at UBC, humane #rstats, statistics, teach @STAT545-UBC, leadership of @rOpenSci, @rsheets, academic director @ubc-mds","public_repos":168,"public_gists":54,"followers":780,"following":34,"created_at":"2011-02-03T22:37:41Z","updated_at":"2016-10-24T07:20:26Z"},"3":{"login":"jtleek","id":1571674,"avatar_url":"https://avatars.githubusercontent.com/u/1571674?v=3","gravatar_id":"","url":"https://api.github.com/users/jtleek","html_url":"https://github.com/jtleek","followers_url":"https://api.github.com/users/jtleek/followers","following_url":"https://api.github.com/users/jtleek/following{/other_user}","gists_url":"https://api.github.com/users/jtleek/gists{/gist_id}","starred_url":"https://api.github.com/users/jtleek/starred{/owner}{/repo}","subscriptions_url":"https://api.github.com/users/jtleek/subscriptions","organizations_url":"https://api.github.com/users/jtleek/orgs","repos_url":"https://api.github.com/users/jtleek/repos","events_url":"https://api.github.com/users/jtleek/events{/privacy}","received_events_url":"https://api.github.com/users/jtleek/received_events","type":"User","site_admin":false,"name":"Jeff L.","company":[],"blog":"http://biostat.jhsph.edu/~jleek/","location":"Baltimore,MD","email":[],"hireable":[],"bio":[],"public_repos":67,"public_gists":12,"followers":3958,"following":6,"created_at":"2012-03-24T18:16:43Z","updated_at":"2016-10-05T13:03:04Z"},"4":{"login":"juliasilge","id":12505835,"avatar_url":"https://avatars.githubusercontent.com/u/12505835?v=3","gravatar_id":"","url":"https://api.github.com/users/juliasilge","html_url":"https://github.com/juliasilge","followers_url":"https://api.github.com/users/juliasilge/followers","following_url":"https://api.github.com/users/juliasilge/following{/other_user}","gists_url":"https://api.github.com/users/juliasilge/gists{/gist_id}","starred_url":"https://api.github.com/users/juliasilge/starred{/owner}{/repo}","subscriptions_url":"https://api.github.com/users/juliasilge/subscriptions","organizations_url":"https://api.github.com/users/juliasilge/orgs","repos_url":"https://api.github.com/users/juliasilge/repos","events_url":"https://api.github.com/users/juliasilge/events{/privacy}","received_events_url":"https://api.github.com/users/juliasilge/received_events","type":"User","site_admin":false,"name":"Julia Silge","company":[],"blog":"juliasilge.com","location":"Salt Lake City, UT","email":[],"hireable":[],"bio":"Data science and visualization, #rstats, parenthood, reading, food/wine/coffee, #NASADatanauts.","public_repos":26,"public_gists":4,"followers":115,"following":10,"created_at":"2015-05-19T02:51:23Z","updated_at":"2016-10-20T10:41:43Z"},"5":{"login":"leeper","id":3505428,"avatar_url":"https://avatars.githubusercontent.com/u/3505428?v=3","gravatar_id":"","url":"https://api.github.com/users/leeper","html_url":"https://github.com/leeper","followers_url":"https://api.github.com/users/leeper/followers","following_url":"https://api.github.com/users/leeper/following{/other_user}","gists_url":"https://api.github.com/users/leeper/gists{/gist_id}","starred_url":"https://api.github.com/users/leeper/starred{/owner}{/repo}","subscriptions_url":"https://api.github.com/users/leeper/subscriptions","organizations_url":"https://api.github.com/users/leeper/orgs","repos_url":"https://api.github.com/users/leeper/repos","events_url":"https://api.github.com/users/leeper/events{/privacy}","received_events_url":"https://api.github.com/users/leeper/received_events","type":"User","site_admin":false,"name":"Thomas J. Leeper","company":"London School of Economics","blog":"http://www.thomasleeper.com","location":"London, United Kingdom","email":[],"hireable":true,"bio":"Political scientist and R hacker. Interested in open science, public opinion research, surveys, experiments, crowdsourcing, and cloud computing.","public_repos":99,"public_gists":46,"followers":213,"following":230,"created_at":"2013-02-07T21:07:00Z","updated_at":"2016-10-20T10:36:25Z"},"6":{"login":"masalmon","id":8360597,"avatar_url":"https://avatars.githubusercontent.com/u/8360597?v=3","gravatar_id":"","url":"https://api.github.com/users/masalmon","html_url":"https://github.com/masalmon","followers_url":"https://api.github.com/users/masalmon/followers","following_url":"https://api.github.com/users/masalmon/following{/other_user}","gists_url":"https://api.github.com/users/masalmon/gists{/gist_id}","starred_url":"https://api.github.com/users/masalmon/starred{/owner}{/repo}","subscriptions_url":"https://api.github.com/users/masalmon/subscriptions","organizations_url":"https://api.github.com/users/masalmon/orgs","repos_url":"https://api.github.com/users/masalmon/repos","events_url":"https://api.github.com/users/masalmon/events{/privacy}","received_events_url":"https://api.github.com/users/masalmon/received_events","type":"User","site_admin":false,"name":"Maëlle Salmon","company":"ISGlobal","blog":"https://masalmon.github.io/","location":"Barcelona, Spain","email":[],"hireable":[],"bio":"I use R for getting, preparing, visualizing and analyzing data mostly about air quality & public health.","public_repos":31,"public_gists":0,"followers":34,"following":38,"created_at":"2014-08-05T08:10:04Z","updated_at":"2016-10-24T09:54:57Z"}},"options":{"mode":"view","modes":["code","form","text","tree","view"]}},"evals":[],"jsHooks":[]}</script><!--/html_preserve-->




