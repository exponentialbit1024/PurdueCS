import java.util.*;
import java.io.*;

public class PercolationVisualizer{
  private Percolation percolationUseOb;

  public PercolationVisualizer(int n){
    percolationUseOb = new Percolation(n);
  }

  public static void main(String[] args){
    Scanner stdinOb = new Scanner(System.in);
    // File file = new File("visualMatrix.txt");
    // file.createNewFile();
    // FileWriter writer = new FileWriter(file);
    // writer.write(size + "\n\n");
    int size = stdinOb.nextInt();
    PercolationVisualizer usageObj = new PercolationVisualizer(size);
    System.out.println(size + "\n");

    while(stdinOb.hasNextInt()){
      int x = stdinOb.nextInt();
      int y = stdinOb.nextInt();
      usageObj.percolationUseOb.open(x,y);
      
      for(int j = 0; j < usageObj.percolationUseOb.openedGrid.length; j++){
        for(int k = 0; k < usageObj.percolationUseOb.openedGrid[j].length; k++){
          if(usageObj.percolationUseOb.openedGrid[j][k]){
            if(usageObj.percolationUseOb.isFull(size - j - 1,k)){
              System.out.print("2 ");
            }
            else{
              System.out.print("1 ");
            }
          }
          else{
            System.out.print("0 ");
          }
        }
        System.out.print("\n");
      }
      System.out.print("\n");

    }

    // writer.flush();
    // writer.close();
  }
}
