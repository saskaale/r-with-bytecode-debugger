options(keep.source=TRUE)
library(compiler)
library(bctools)

f<-function(a){
    c<-a+1
    d<-c+a
    c-d
}

compiled <- cmpfun(f)

#set breakpoints

 #this breakpoint would be set into position 12, because at 11 is argument
 # and the implemented functionality is setting the breakpoint in that cases
 # to the first following instruction
bcSetBreakpoint(compiled, 11);
 #14 is regular instruction
bcSetBreakpoint(compiled, 14);

#print the current function - notice the (BR) in the instruction
print(disassemble(compiled),verbose=2)

#print the bytecode instructions - see the 12 and 14
print(bcListBreakpoints(compiled))
