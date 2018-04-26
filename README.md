# r-with-bytecode-debugger

GNU R with implemented bytecode debugger and support for conditional breakpoints

builded and tested on Ubuntu 16.04 LTS

## how-to compile

install dependencies
```bash
sudo apt-get install build-essential r-recommended gfortran libbz2-dev liblzma-dev libpcre3-dev libcurl4-openssl-dev libreadline-dev xorg-dev texinfo subversion
```

<!--
download R recommended package sources
```bash
./r_source/tools/rsync-recommended
```
-->

compile GNU R
```bash
cd r_source && ./configure --without-recommended-packages && make -j10
```

install bctools package
```bash
./r_source/bin/R CMD INSTALL ./bctools_0.1.0.tar.gz
```

## how-to run

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
debugVerbose(TRUE) # try to comment this line out

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
sudo ap
### simulated conditional breakpoint example

```R

# initialization
library(compiler)
enableBCDebug(TRUE)
debugVerbose(TRUE)

# function to run
f<-function(x){
 for(i in 1:x){
  if(i == 3)
   breakpoint()
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

This work was part of my 2018 diploma thesis.

See `examples` directory for more detailed examples about implementation or read the thesis content in `thesis/DP_Saska_Ales_2018.pdf` for more details about implementation and all configuration parameters.
