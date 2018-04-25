options(keep.source=TRUE)
library(compiler)

f<-function(){
    for(x in 1:5){
        if(x == 3){
            breakpoint();
        }
    }
}
f()

