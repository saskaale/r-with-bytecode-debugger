library(compiler)

# Program to display the Fibonacci sequence up to n-th term using recursive functions
recurse_fibonacci <- function(n) {
if(n <= 1) {
return(n)
} else {
return(recurse_fibonacci(n-1) + recurse_fibonacci(n-2))
}
}

print(cmpfun(recurse_fibonacci)(30))
