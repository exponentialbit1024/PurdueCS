#!/bin/bash

#DO NOT REMOVE THE FOLLOWING TWO LINES
git add $0 >> .local.git.out
git commit -a -m "Lab 2 commit" >> .local.git.out
git push >> .local.git.out || echo


#Your code here
pswd_to_check=$(cat "$1")
pswd_len=`expr length $pswd_to_check`

if [ $pswd_len -gt 32 ] || [ $pswd_len -lt 6 ];
then
	echo "Error: Password length invalid."
	exit -1
fi
fin_score=$pswd_len

if egrep -q [#$+%@] $1;
then
	fin_score=$(($fin_score + 5))
fi

if egrep -q [0-9] $1;
then
	fin_score=$(($fin_score + 5))
fi

if egrep -q [A-Za-z] $1;
then
	fin_score=$(($fin_score + 5))
fi

if egrep -q '([A-Za-z0-9])\1+' $1;
then
	fin_score=$(($fin_score - 10))
fi

if egrep -q '[a-z][a-z][a-z]' $1;
then
	fin_score=$(($fin_score - 3))
fi

if egrep -q '[A-Z][A-Z][A-Z]' $1;
then
	fin_score=$(($fin_score - 3))
fi

if egrep -q '[0-9][0-9][0-9]' $1;
then
	fin_score=$(($fin_score - 3))
fi

echo "Password Score : $fin_score"

