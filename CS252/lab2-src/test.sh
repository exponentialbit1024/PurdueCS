echo $1 > tmpfile

if egrep -q '[1 0-9]' tmpfile ;
then
	echo "valid"
	exit 1
fi

echo "invalid"
