options(keep.source=TRUE)
debugVerbose(TRUE)
enableBCDebug(TRUE)
library(compiler)

f<-function(a){
    c<-a+1
    d<-c+a
    c-d
}
compiled <- cmpfun(f)
debug(compiled)
compiled(2)

