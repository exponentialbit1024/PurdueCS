setwd("//myhome.itap.purdue.edu/puhome/pu.data/Desktop/Junior/sem2/CS373/hw1")
yelp = read.csv(file = "yelp.csv", header = TRUE)
names(yelp)
summary(yelp)
summary(yelp$noiseLevel)
summary(yelp$stars)

jpeg("checkinhist.jpg")
hist(yelp$checkins)
dev.off()

logCheckin = log(yelp$checkins)
jpeg("logcheckin.jpg")
hist(logCheckin)
dev.off()

isAmerican <- grepl("American", yelp$categories)
goodForDinner <- grepl("dinner", yelp$recommendedFor)

yelp <- cbind(yelp, isAmerican)
yelp <- cbind(yelp, goodForDinner)

summary(yelp$isAmerican)
summary(yelp$goodForDinner)

quantiles = quantile(yelp$reviewCount)
yelp_subset <- subset(yelp, yelp$reviewCount <= quantile(yelp$reviewCount, 0.25))

summary(yelp_subset$reviewCount)
summary(yelp_subset$stars)
summary(yelp_subset$attire)
summary(yelp_subset$priceRange)
summary(yelp_subset$delivery)
summary(yelp_subset$goodForKids)

summary(yelp$reviewCount)
summary(yelp$stars)
summary(yelp$attire)
summary(yelp$priceRange)
summary(yelp$delivery)
summary(yelp$goodForKids)

pairs(~yelp$stars+yelp$reviewCount+yelp$checkins+yelp$longitude+yelp$latitude, data = yelp, main="Scatterplot Matrix")

cor(yelp$stars, yelp$reviewCount)
cor(yelp$stars, yelp$checkins)
cor(yelp$stars, yelp$longitude)
cor(yelp$stars, yelp$latitude)

cor(yelp$reviewCount, yelp$checkins)
cor(yelp$reviewCount, yelp$longitude)
cor(yelp$reviewCount, yelp$latitude)

cor(yelp$checkins, yelp$longitude)
cor(yelp$checkins, yelp$latitude)

cor(yelp$longitude, yelp$latitude)


boxplot(yelp$checkins~yelp$goodForGroups, data = yelp, main = "checkins vs goodForGroups", xlab="checkin", ylab="goodForGroups")
boxplot(yelp$reviewCount~yelp$goodForGroups, data = yelp, main = "reviewCount vs goodForGroups", xlab="reviewCount", ylab="goodForGroups")
boxplot(yelp$longitude~yelp$goodForGroups, data = yelp, main = "longitude vs goodForGroups", xlab="longitude", ylab="goodForGroups")
boxplot(yelp$latitude~yelp$goodForGroups, data = yelp, main = "latitude vs goodForGroups", xlab="latitude", ylab="goodForGroups")


tru_ch <- subset(yelp, yelp$goodForGroups == TRUE)
quantile(tru_ch$checkins)
quantile(tru_ch$reviewCount)
quantile(tru_ch$longitude)
quantile(tru_ch$latitude)


false_ch <- subset(yelp, yelp$goodForGroups == FALSE)
quantile(false_ch$checkins)
quantile(false_ch$reviewCount)
quantile(false_ch$longitude)
quantile(false_ch$latitude)

boxplot(yelp$priceRange~yelp$attire, data = yelp, main = "attire vs priceRange", xlab="attire", ylab="priceRange")

