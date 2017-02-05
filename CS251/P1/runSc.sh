echo "Enter test case file: \c"
read testFile
java -classpath .:stdlib.jar Percolation < $testFile
