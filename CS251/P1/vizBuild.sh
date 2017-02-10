javac -classpath .:stdlib.jar WeightedQuickUnionUF.java
javac -classpath .:stdlib.jar QuickUnionUF.java
javac -classpath .:stdlib.jar Percolation.java
javac -classpath .:stdlib.jar PercolationVisualizer.java
#java -classpath .:stdlib.jar Percolation < DemoNo.txt
java -classpath .:stdlib.jar PercolationVisualizer < DemoNo.txt
#java -classpath .:stdlib.jar PercolationVisualizer < DemoYes.txt
