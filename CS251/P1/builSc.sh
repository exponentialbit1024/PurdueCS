javac -classpath .:stdlib.jar WeightedQuickUnionUF.java
javac -classpath .:stdlib.jar QuickUnionUF.java
javac -classpath .:stdlib.jar Percolation.java
java -classpath .:stdlib.jar Percolation < DemoNo.txt
#echo "\nDemo Yes"
#java -classpath .:stdlib.jar Percolation < DemoYes.txt
