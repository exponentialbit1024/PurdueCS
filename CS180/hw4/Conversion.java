import java.util.*;

public class Conversion{

  public int binaryToDecimal(int binary){
    int rem = 0;
    int dec = 0;
    int count = 0;
    while(binary != 0){
      rem = binary % 10;
      binary /= 10;
      dec += rem * Math.pow(2,count);
      count++;
    }
    return dec;
  }

  public int decimalToBinary(int decimal){
    int rem = 0;
    int bin = 0;
    int count = 0;
    int fullbin = 0;
    Stack<Integer> stack = new Stack<Integer>();
    while(decimal > 0){
      bin = decimal % 2;
      decimal /= 2;
      stack.push(bin);
    }
    int revertBin = 0;
    while(!(stack.isEmpty())){
      revertBin = revertBin * 10 + stack.pop();
    }
    return revertBin;
  }

  public static void main(String[] args){
    Conversion usageObj = new Conversion();
    System.out.println(usageObj.binaryToDecimal(1001000));  // Prints 72
    System.out.println(usageObj.binaryToDecimal(1011000));  // Prints 88
    System.out.println(usageObj.decimalToBinary(113));  // Prints 1110001
    System.out.println(usageObj.decimalToBinary(64));  // Prints 1000000
  }
}
