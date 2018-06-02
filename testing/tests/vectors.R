library(compiler)

initVec <- function(){
    veclength <- 10*1000;
    v <- vector(mode="numeric", length=veclength);
    for(i in 1:veclength)
        v[i] = i
    v
}


vecOp <- function(){
  v1 <- initVec();
  v2 <- initVec();
  v3 <- initVec();
  v4 <- initVec();
  for(i in 1:20000){
    v5 <- v1+v2
    v6 <- v2+v4
    v7 <- v2*3
#    v6 <- lapply(v6, function(v){v+1})
  }
}

print(cmpfun(vecOp)())
