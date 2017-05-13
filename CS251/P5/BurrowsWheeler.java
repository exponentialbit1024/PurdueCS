import java.util.*;

public class BurrowsWheeler {

    // apply Burrows-Wheeler encoding, reading from standard input and writing to standard output
    public static void encode(){
      String input = BinaryStdIn.readString();

      CircularSuffixArray circularSuffixArray = new CircularSuffixArray(input);

      for (int i = 0; i < circularSuffixArray.length(); i++) {
         if (circularSuffixArray.index(i) == 0) {
            BinaryStdOut.write(i);
            break;
         }
      }

      for (int i = 0; i < circularSuffixArray.length(); i++) {
         int index = circularSuffixArray.index(i);
         if (index == 0) {
            char printer = input.charAt(input.length() - 1);
            BinaryStdOut.write(printer);
            continue;
         }
        BinaryStdOut.write(input.charAt(index - 1));
      }
      // BinaryStdOut must be closed
      BinaryStdOut.close();

    }
    // apply Burrows-Wheeler decoding, reading from standard input and writing to standard output
    public static void decode(){
      int first = BinaryStdIn.readInt();
      String chars = BinaryStdIn.readString();
      char[] t = chars.toCharArray();
      chars = null;
      // construct next[]
      int next[] = new int[t.length];
      // Algorithm: Brute Force requires O(n^2) =>
      // go through t, consider t as key remember positions of t's in the Queue
      Map<Character, Queue<Integer>> positions = new HashMap<Character, Queue<Integer>>();
      for (int i = 0; i < t.length; i++) {
         if(!positions.containsKey(t[i]))
            positions.put(t[i], new Queue<Integer>());
         positions.get(t[i]).enqueue(i);
      }
      // get first chars array
      Arrays.sort(t);
      // go consistently through sorted firstChars array
      for (int i = 0; i < t.length; i++) {
         next[i] = positions.get(t[i]).dequeue();
      }
      // decode msg
      // for length of the msg
      for (int i = 0, curRow = first; i < t.length; i++, curRow = next[curRow])
         // go from first to next.
         BinaryStdOut.write(t[curRow]);
      BinaryStdOut.close();
    }
    // if args[0] is '-', apply Burrows-Wheeler encoding
    // if args[0] is '+', apply Burrows-Wheeler decoding
    public static void main(String[] args){
    	if(args[0].equals("-")){
        encode();
      }else if(args[0].equals("+")){
        decode();
      }
    }
}
