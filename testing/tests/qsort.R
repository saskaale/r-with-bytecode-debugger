library(compiler)


#### Function downloaded from https://rosettacode.org/wiki/Sorting_algorithms/Quicksort#R
qsort <- function(v) {
  if ( length(v) > 1 )
  {
    pivot <- (min(v) + max(v))/2.0                            # Could also use pivot <- median(v)
    c(qsort(v[v < pivot]), v[v == pivot], qsort(v[v > pivot]))
  } else v
}

N <- 250000
vs <- runif(N)

invisible(cmpfun(qsort)(vs))
