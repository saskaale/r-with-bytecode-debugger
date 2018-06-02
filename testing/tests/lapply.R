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
  for(i in 1:500){
    lapply(v1, function(v){v+1})
  }
}

print(cmpfun(vecOp)())
