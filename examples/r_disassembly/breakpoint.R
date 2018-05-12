options(keep.source=TRUE)
library(compiler)
library(bctools)

f<-function(a){
    c<-a+1
    d<-c+a
    c-d
}
compiled <- cmpfun(f)
print(disassembly(compiled))
