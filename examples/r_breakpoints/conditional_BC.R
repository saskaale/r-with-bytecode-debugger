options(keep.source=TRUE)
debugVerbose(TRUE)
enableBCDebug(TRUE)
library(compiler)

f<-function(){
    for(x in 1:5){
        if(x == 3){
            breakpoint();
        }
    }
}
compiled <- cmpfun(f)
compiled()

