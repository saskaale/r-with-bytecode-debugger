library(compiler)
library(bctools)
f<-function(a) a+1
compiled<-cmpfun(f)

disassemble(compiled)