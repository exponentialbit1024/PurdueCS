public class MatrixNeighbors{
  int rows;
  int columns;
  int[][] matrix;

  public MatrixNeighbors(int rows, int columns){
    this.rows = rows;
    this.columns = columns;
    this.matrix = new int[rows][columns];
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < columns; j++){
        matrix[i][j] = j;
      }
    }
  }

  public String neighbors(int row, int column){
    if(row > this.rows - 1 || column > this.columns - 1){
      return "cell does not exist";
    }

    String retStr = "";

    if((row - 1) >= 0){
      retStr += Integer.toString(row - 1) + "," + Integer.toString(column) + ";";
      if((column + 1) < this.columns){
        retStr += Integer.toString(row - 1) + "," + Integer.toString(column + 1) + ";";
      }
    }

    if((column + 1) < this.columns){
      retStr += Integer.toString(row) + "," + Integer.toString(column + 1) + ";";
      if((row + 1) < this.rows){
        retStr += Integer.toString(row + 1) + "," + Integer.toString(column + 1) + ";";
      }
    }
    if((row + 1) < this.rows){
      retStr += Integer.toString(row + 1) + "," + Integer.toString(column) + ";";
      if((column - 1) >= 0){
        retStr += Integer.toString(row + 1) + "," + Integer.toString(column - 1) + ";";
      }
    }

    if((column - 1) >= 0){
      retStr += Integer.toString(row) + "," + Integer.toString(column - 1) + ";";
      if((row - 1) >= 0){
        retStr += Integer.toString(row - 1) + "," + Integer.toString(column - 1) + ";";
      }
    }
    return retStr;
  }

  public static void main(String[] args){
    MatrixNeighbors m = new MatrixNeighbors(3, 3);
    System.out.println(m.neighbors(0, 0));
    System.out.println(m.neighbors(2, 2));
    System.out.println(m.neighbors(1, 1));
    System.out.println(m.neighbors(3, 0));
  }
}
