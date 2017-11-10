#!/bin/bash
# Program:
#	User input dir name, I find the permission of files.
# History:
# 2005/08/29	VBird	First release
#PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
#export PATH

s=0
for((i=1; i<101; i=i+1))
do
	s=$(($s+$i))
done
echo "s=$s"