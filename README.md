# r-with-bytecode-debugger

GNU R with implemented support for bytecode debugger

## howto compile

```bash
 cd r_source && ./configure --without-recommended-packages --with-x=no && make -j10
```

## howto run

execute R with 
```bash
./r_source/bin/R
```

and then debug the bytecode compiled function:

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


