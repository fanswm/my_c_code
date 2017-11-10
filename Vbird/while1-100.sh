#!/bin/bash
# Program:
#	Repeat question until user input correct answer.
# History:
# 2005/08/29	VBird	First release
#PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
#export PATH

declare -i sum=0
#$firstnu*$secnu
declare -i n=1
echo "sum=${sum},n=${n}"
while [ $n -lt 101 ]
do
	declare -i sum=$(($sum+$n))
	declare -i n=$(($n+1))
done
echo "1+2+3+...+100:sum=${sum}"