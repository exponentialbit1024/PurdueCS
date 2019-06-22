#!/bin/bash

username="username@csora"
pword="pword"

echo "$1"

declare -a queries=("1.0-0" "1.1-1" "1.2-2" "1.3-3" "1.4-4" "2.0-2" "2.3-6" "2.7-9" "2.10-14" "2.15-17" "3.0-3" "3.4-5" "3.6-7" "3.8-9" "3.10-11" "3.12-13" "4.0-6" "5.0-5" "5.6-7")

get_result () {
	sqlplus -s $1/$2 << EOF
	set feedback off
	set serveroutput on
	$3
	exit
EOF
}

parse_result () {
	IFS=$'\n' lines=($1)
	if [[ ${lines[0]} == "No errors." ]]; then
		lines=("${lines[@]:1}")
	fi
	for i in $(seq $2 $3);
	do
		echo ${lines[i]};
	done
}

if [[ -z "$1"  ]] 
then
	echo "Testing all procedures"
	count=0
	for i in {1..5};
	do
		sql=$(awk -v n=$i '/-- Question/{l++;next}(l==n){print}' answer.sql)
		echo ">>>> Test Procedure $i"
		echo "---- Student Procedure:"
		echo "$sql"
		for sq in "${queries[@]}" 
		do
			q=${sq:0:1}
			if [[ "$q" = "$i" ]]; then
				offsets=${sq:2}
	        	start_idx="$(cut -d'-' -f1 <<<"$offsets")"
	        	end_idx="$(cut -d'-' -f2 <<<"$offsets")"
				v1=$(get_result "$username" "$pword" "$sql")
				echo "---- Result of Procedure $i:"
				if [[ $v1 == *"ERROR"* ]]; then
					echo "$v1"
					exit 1
				fi
				if [[ $v1 != *"compilation error"* ]]; then
					v1=$(parse_result "$v1" "$start_idx" "$end_idx")
	        	fi
				for j in "${v1[@]}"
				do
					echo "$j"
				done
				ans=$(awk -v n=$i '/>>> Question/{l++;next}(l==n){print}' result.txt )
				ans=$(parse_result "$ans" "$start_idx" "$end_idx")
				ans_split=()
				for str in $ans
				do 
					ans_split+=($str)
				done
				v1_split=()
				for str in $v1
				do
					v1_split+=($str)
				done
				diff=$(diff <(printf "%s\n" "${v1_split[@]}") <(printf "%s\n" "${ans_split[@]}"))
				if [[ -z "$diff" ]]
				then
					echo -e "\e[42mPass\e[0m"
					count=$((count + 1))
				else
					echo -e "\e[31mFail\e[0m"
					echo "Expected:"
					echo "$ans"
				fi
			fi
		done
		echo -e "\e[34m====================================\e[0m"
	done
	echo -e "+++++ Total pass: \e[32m$count\e[0m / ${#queries[@]}"
else
	sql=$(awk -v n=$1 '/-- Question/{l++;next}(l==n){print}' answer.sql)
	if [[ ! -z "$sql" ]]; then
        echo ">>> Test Procedure $1"
        echo "---- Student Procedure:"
        echo "$sql"
	fi	
	for sq in "${queries[@]}" 
	do
		q=${sq:0:1}
		if [[ "$q" = "$1" ]]; then
			offsets=${sq:2}
	        start_idx="$(cut -d'-' -f1 <<<"$offsets")"
	        end_idx="$(cut -d'-' -f2 <<<"$offsets")"
			v1=$(get_result "$username" "$pword" "$sql")
			echo "---- Result of Procedure $1:"
			if [[ $v1 == *"ERROR"* ]]; then
				echo "$v1"
				exit 1
			fi
			if [[ $v1 != *"compilation error"* ]]; then
				v1=$(parse_result "$v1" "$start_idx" "$end_idx")
			fi
			for i in "${v1[@]}"
			do
				echo "$i"
			done
			ans=$(awk -v n=$1 '/>>> Question/{l++;next}(l==n){print}' result.txt)
			ans=$(parse_result "$ans" "$start_idx" "$end_idx")
			ans_split=()
			for str in $ans
			do 
				ans_split+=($str)
			done
			v1_split=()
			for str in $v1
			do
				v1_split+=($str)
			done
			diff=$(diff <(printf "%s\n" "${v1_split[@]}") <(printf "%s\n" "${ans_split[@]}"))
			if [[ -z "$diff" ]]
			then
				echo -e "\e[42mPass\e[0m"
			else
				echo -e "\e[31mFail\e[0m"
				echo "Expected:"
				echo "$ans"
			fi
		fi
	done
fi
