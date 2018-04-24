## ------------------------------------------------------------------------

library(compiler)
library(bctools)

x <- 2

bytecode <- compile(quote(x+2))

disassemble(bytecode)


## ------------------------------------------------------------------------

library(compiler)
library(bctools)

f <- function(x){
    sum <- 0
    while(x > 0){
        sum <- sum + x
    }
    sum
}

bytecode <- cmpfun(f)

disassemble(bytecode)  #internally calls print(disassemble(bytecode))


## ------------------------------------------------------------------------

library(compiler)
library(bctools)

f <- function(x){
    sum <- 0
    while(x > 0){
        sum <- sum + x
    }
    sum
}

bytecode <- cmpfun(f)

print(disassemble(bytecode), verbose=1)


## ------------------------------------------------------------------------

library(compiler)
library(bctools)

f <- function(x){
    sum <- 0
    while(x > 0){
        sum <- sum + x
    }
    sum
}

bytecode <- cmpfun(f)

print(disassemble(bytecode), verbose=2)



## ------------------------------------------------------------------------

library(compiler)
library(bctools)

f <- function(x){
    sum <- 0
    while(x > 0){
        sum <- sum + x
    }
    sum
}

bytecode <- cmpfun(f)

bcverbose()  #get default verbosity level

bcverbose(2)  #set default verbosity level to 2, notice that this function also returns this value

disassemble(bytecode) #print bytecode with default verbosity level ( currently setted to 2 )


