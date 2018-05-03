library(compiler)
library(bctools)
f<-function(x) {
    y <- x*2
    while(x < y)
	x <- x+1

    if(x %% 2 == 0)
	x
    else
	-x
}
compiled<-cmpfun(f)

disassemble(compiled)
