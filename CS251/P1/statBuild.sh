javac -classpath .:stdlib.jar WeightedQuickUnionUF.java
javac -classpath .:stdlib.jar QuickUnionUF.java
javac -classpath .:stdlib.jar Percolation.java
javac -classpath .:stdlib.jar PercolationQuick.java
javac -classpath .:stdlib.jar PercolationStats.java
java -classpath .:stdlib.jar PercolationStats 500 30 fast
