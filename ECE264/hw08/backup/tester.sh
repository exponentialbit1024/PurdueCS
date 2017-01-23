$i=0
while [ true ] 
do
	gcc -o testf team.h team.c test_team.c
	./testf
	echo "Test Index $i"
	i=$[$i+1]

done
