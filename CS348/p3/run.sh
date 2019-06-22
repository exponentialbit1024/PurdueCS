echo exit | sqlplus shah255@csora/LWU3lh39 @drop.sql >/dev/null
echo exit | sqlplus shah255@csora/LWU3lh39 @create.sql >/dev/null
echo exit | sqlplus shah255@csora/LWU3lh39 @init.sql >/dev/null

javac -cp .:ojdbc8.jar Project3.java
java -cp .:ojdbc8.jar Project3 input.txt output.txt
