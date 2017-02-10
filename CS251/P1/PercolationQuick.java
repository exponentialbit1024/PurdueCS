import java.util.*;

public class PercolationQuick{
  private int size;
  public boolean[][] openedGrid;
  private QuickUnionUF quickFind;
  private int top;
  private int bottom = 0;

  public PercolationQuick(int n){
    size = n;
    top = size * size + 1;
    quickFind = new QuickUnionUF(size * size + 2);
    openedGrid = new boolean[size][size];
  }

  public void open(int x, int y){
    int usableRow = size - x - 1;
    // System.out.println(usableRow);
    // System.out.println(y);
    openedGrid[usableRow][y] = true;
    if(usableRow == (size - 1)){
      quickFind.union(top,ufoDSize(x,y));
    }
    if(usableRow == 0){
      quickFind.union(bottom, ufoDSize(x,y));
    }
    if((x + 1) < size && isOpen(x + 1,y)){
      quickFind.union(ufoDSize(x,y),ufoDSize(x+1,y));
    }
    if((x - 1) >= 0 && isOpen(x - 1,y)){
      quickFind.union(ufoDSize(x,y), ufoDSize(x - 1,y));
    }
    if((y + 1) < size && isOpen(x,y + 1)){
      quickFind.union(ufoDSize(x,y), ufoDSize(x, y + 1));
    }
    if((y - 1) >= 0 && isOpen(x, y - 1)){
      quickFind.union(ufoDSize(x,y), ufoDSize(x, y - 1));
    }
  }

  public boolean isFull(int x, int y){
    int usableX = size - x - 1;
    if(usableX >= 0 && usableX < size && y >= 0 && y < size){
      return quickFind.connected(bottom, ufoDSize(x,y));
    }
    else{
      throw new IndexOutOfBoundsException();
    }
  }

  public boolean isOpen(int x, int y){
    return openedGrid[size - x - 1][y];
  }

  public boolean percolates(){
    return quickFind.connected(top, bottom);
  }

  public int ufoDSize(int x, int y){
    //check for out of bounds
    return ((size - x - 1) * size + y);
  }

  public static void main(String[] args){
    Scanner stdinOb = new Scanner(System.in);
    int size = stdinOb.nextInt();
    Percolation usageObj = new Percolation(size);
    // System.out.println("Size " + size);

    while(stdinOb.hasNextInt()){
      int x = stdinOb.nextInt();
      int y = stdinOb.nextInt();
      usageObj.open(x,y);
    }
    boolean percolationTest = usageObj.percolates();
    if(percolationTest){
      System.out.println("Yes");
    }
    else{
      System.out.println("No");
    }
  }
}
