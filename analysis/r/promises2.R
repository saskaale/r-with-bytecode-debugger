getB <- function(){
	print("getB")
	5
}

calc <- function(a,b){
	print("calc enter")
	ret <- a*2
	print("accessB")
	ret <- b*10
	print("calc exit")
}
calc(2,getB())
