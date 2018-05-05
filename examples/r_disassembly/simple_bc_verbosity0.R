options(keep.source=TRUE)
library(compiler)
library(bctools)
f<-function(a) while(a) a <- a-1
compiled<-cmpfun(f)

print(disassemble(compiled),verbose=1)
