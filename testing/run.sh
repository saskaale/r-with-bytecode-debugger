#R=../../r_source/bin/Rscript
R=../../../orig2/trunk/bin/Rscript
#R=Rscript

for FILE in ./tests/*; do
    echo "$FILE"
    for i in {1..10} do
	{ time Rscript $FILE ; } 2>&1 | grep "user" | cut -f 2 | sed "s/0m//g" | tr "s" " "
#	cat /mnt/ramdisk/out | tr '\n' ' '
#	echo $VAR
    done
    echo ""
done