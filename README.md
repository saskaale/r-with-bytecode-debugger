# r-with-bytecode-debugger

GNU R with implemented bytecode debugger and support for conditional breakpoints

## howto compile

```bash
 cd r_source && ./configure --without-recommended-packages --with-x=no && make -j10
```

## howto run

execute R with 
```bash
./r_source/bin/R
```

and then type some R input:

### bytecode debugger example

```R

# initialization
library(compiler)
enableBCDebug(TRUE)
debugVerbose(TRUE)

# function to run
f<-function(x){
 for(i in 1:x)
  print(i)
}

# byte-compile that function
cf <- cmpfun(f)

#the bytecode compiled function for debugging
debug(cf)

#run and enjoy :)
cf(5)

```

### conditional breakpoint example

```R

# initialization
library(compiler)
enableBCDebug(TRUE)
debugVerbose(TRUE)

# function to run
f<-function(x){
 for(i in 1:x){
  if(i == 3)
   breakpoint();
  print(i)
 }
}

# byte-compile that function
cf <- cmpfun(f)

#the bytecode compiled function for debugging
debug(cf)

#run and enjoy stopping when loop reach 3 :)
cf(5)

```

## more info

This work was part of 2018 diploma thesis. For more details about implementation and all configuration see it's content in `thesis/DP_Saska_Ales_2018.pdf`.



