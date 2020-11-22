options(keep.source=TRUE)

library(tidyverse)

data("diamonds")
# 1. 산점도
plot(price ~ carat, data=diamonds)
# 2. 선형모형 적합
lm.m <- lm(price ~ carat, data=diamonds)
# 3. 데이터와 모형 적합 평가
abline(lm.m, col = "blue")
