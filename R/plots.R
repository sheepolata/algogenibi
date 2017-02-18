#fitness, p, a
best <- read.table('final.tsv', header=TRUE, sep="\t")

jpeg('besta.jpg')
plot(best$a, type='l', col="red", ylab="a()", xlab="Generations")
dev.off()

jpeg('bestp.jpg')
plot(best$p, type='l', col="red", ylab="p()", xlab="Generations")
dev.off()

jpeg('bestr1.jpg')
plot(best$r1, type='l', col="red", ylab="r1()", xlab="Generations")
dev.off()

jpeg('bestteta.jpg')
plot(best$teta, type='l', col="red", ylab="teta()", xlab="Generations")
dev.off()