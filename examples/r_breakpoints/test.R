options(keep.source=TRUE)
debugVerbose(TRUE)
enableBCDebug(TRUE)
library(compiler)

g<-function(x){ x+1 }

f<-function(){
    for(x in 1:5){
        if(x == 3)
            g(x)
#        if(x == 3){
#      	    print("BREAKPOINT")
#      	    breakpoint();
#      	}
    }
}
debug(g)
#compiled <- cmpfun(f)
#compiled()
f()
