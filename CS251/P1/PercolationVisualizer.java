import java.util.*;
import java.io.*;

public class PercolationVisualizer{
  private Percolation percolationUseOb;

  public PercolationVisualizer(int n){
    percolationUseOb = new Percolation(n);
  }

  public static void main(String[] args){
    Scanner stdinOb = new Scanner(System.in);

    int size = stdinOb.nextInt();
    PercolationVisualizer usageObj = new PercolationVisualizer(size);

    BufferedWriter bw = null;
    File oFile = new File("./visualMatrix.txt");
    FileWriter fw;
    try{
      if (!oFile.exists()) {
	     oFile.createNewFile();
	    }
      fw = new FileWriter(oFile);
      bw = new BufferedWriter(fw);
      bw.write(Integer.toString(size) + "\n\n");

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
                bw.write("2 ");
              }
              else{
                System.out.print("1 ");
                bw.write("1 ");
              }
            }
            else{
              System.out.print("0 ");
              bw.write("0 ");
            }
          }
          System.out.print("\n");
          bw.write("\n");
        }
        System.out.print("\n");
        bw.write("\n");
      }

      bw.close();

  }catch(IOException e){
    e.printStackTrace();
    }
  }
}
