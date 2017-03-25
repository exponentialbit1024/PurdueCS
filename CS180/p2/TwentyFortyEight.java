import java.util.Random;
import java.util.Scanner;

public class TwentyFortyEight {
    //This instance variable represents the board. Use this to make changes.
    private int[][] board;
    //This variable keeps track of the current score.
    private int score;
    private int boardWidth;

    //Constructor
    public TwentyFortyEight(int boardWidth){
        this.boardWidth = boardWidth;
        this.score = 0;
        this.board = new int[boardWidth][boardWidth];
        placeRandom();
    }

    //This function resets the board to its initial state
    public void reset() {
        for(int i = 0; i < boardWidth; i++){
          for(int j = 0; j < boardWidth; j++){
            this.board[i][j] = 0;
          }
        }
        this.score = 0;
        placeRandom();
    }

    //This function returns the total number of blank spaces on the board
    public int numBlanks() {
      int blanks = 0;
        for(int i = 0; i < boardWidth; i++){
          for(int j = 0; j < boardWidth; j++){
            if(this.board[i][j] == 0){
              blanks++;
            }
          }
        }
        return blanks;
    }

    //This function places a 2 at a random blank space on the board.
    //It does nothing if there are no blank spaces.
    public void placeRandom(){
      int totBlanks = numBlanks();
      if(totBlanks != 0){
        Random tempRand = new Random();
        int xRand = tempRand.nextInt(boardWidth);
        int yRand = tempRand.nextInt(boardWidth);
        do{
          xRand = tempRand.nextInt(boardWidth);
          yRand = tempRand.nextInt(boardWidth);
        }while(!isEmpty(xRand, yRand));
        this.board[xRand][yRand] = 2;
      }
    }

    public boolean isEmpty(int xRand, int yRand){
      return this.board[xRand][yRand] == 0;
    }

    //This function attempts to move a cell at coordinates fromRow,fromCol to
    //the cell toRow,toCol. Refer to the handout for movement rules.
    public boolean moveTo(int fromRow, int fromCol, int toRow, int toCol) {
        if(Math.abs(fromRow - toRow) > 1){
          return false;
        }
        if(Math.abs(fromCol - toCol) > 1){
          return false;
        }
        if(fromRow >= boardWidth || fromRow < 0){
          return false;
        }
        if(fromCol >= boardWidth || fromCol < 0){
          return false;
        }
        if(toRow >= boardWidth || toRow < 0){
          return false;
        }
        if(toCol >= boardWidth || toCol < 0){
          return false;
        }
        if(this.board[fromRow][fromCol] == 0){
          return false;
        }
        if(this.board[toRow][toCol] == 0){
          this.board[toRow][toCol] = this.board[fromRow][fromCol];
          this.board[fromRow][fromCol] = 0;
          return true;
        }
        if(this.board[fromRow][fromCol] == this.board[toRow][toCol]){
          this.board[toRow][toCol] += this.board[fromRow][fromCol];
          this.board[fromRow][fromCol] = 0;
          return true;
        }
        return false;
    }

    //The following four functions move the board in a single direction.
    public boolean moveUp(){
      boolean succesfulMove;
      boolean upSuc = false;
      for(int i = 0; i < boardWidth; i++){
        for(int j = 0; j < boardWidth - 1; j++){
          succesfulMove = moveTo(j + 1, i, j, i);
          if(succesfulMove){
            upSuc = true;
          }
        }
      }
      this.score = getMax();
      return upSuc;
    }

    public boolean moveDown() {
      boolean succesfulMove;
      boolean upSuc = false;
      for(int i = 0; i < boardWidth; i++){
        for(int j = boardWidth - 1; j > 0; j--){
          succesfulMove = moveTo(j - 1, i, j, i);
          if(succesfulMove){
            upSuc = true;
          }
        }
      }
      this.score = getMax();
      return upSuc;
    }

    public boolean moveRight() {
      boolean succesfulMove;
      boolean upSuc = false;
      for(int i = 0; i < boardWidth; i++){
        for(int j = boardWidth - 1; j > 0; j--){
          succesfulMove = moveTo(i, j - 1, i, j);
          if(succesfulMove){
            upSuc = true;
          }
        }
      }
      this.score = getMax();
      return upSuc;
    }

    public boolean moveLeft() {
      boolean succesfulMove;
      boolean upSuc = false;
      for(int i = 0; i < boardWidth; i++){
        for(int j = 0; j < boardWidth - 1; j++){
          succesfulMove = moveTo(i, j + 1, i, j);
          if(succesfulMove){
            upSuc = true;
          }
        }
      }
      this.score = getMax();
      return upSuc;
    }

    public int getMax(){
      int max = this.board[0][0];
      for(int i = 0; i < boardWidth; i++){
        for(int j = 0; j < boardWidth; j++){
          if(this.board[i][j] > max){
            max = this.board[i][j];
          }
        }
      }
      return max;
    }

    ////////////////////////////////////////////////////////////////////////
    // Do not edit the methods below, they are for testing and running the
    // program.
    ////////////////////////////////////////////////////////////////////////
    public int[][] getBoard() {
        return board;
    }

    public void setBoard(int[][] newBoard) {
        board = newBoard;
    }


    /**
     * The main will allow you to play the game.
     *
     * @param args
     */
    public static void main(String args[]) {
        TwentyFortyEight tfe = new TwentyFortyEight(4);


        Scanner s = new Scanner(System.in);
        int bestScore = 0;
        boolean resetFlag = false;

        while(true) {
            System.out.println("Current score: " + tfe.getScore() + " | Best score: " + bestScore);
            tfe.showBoard();

            System.out.println("Enter up, down, left or right to move in that direction.");
            System.out.println("Enter reset to reset the game or quit to exit.");
            String line = s.nextLine();

            switch(line){
                case "up":
                    while(tfe.moveUp()){
                        // do nothing
                    }
                    break;
                case "down":
                    while(tfe.moveDown()){
                        // do nothing
                    }
                    break;
                case "left":
                    while(tfe.moveLeft()){
                        // do nothing
                    }
                    break;
                case "right":
                    while(tfe.moveRight()){
                        // do nothing
                    }
                    break;
                case "reset":
                    tfe.reset();
                    resetFlag = true;
                    break;
                case "quit":
                    return;
                default:
                    System.out.println("Invalid move, Please try again!!!!\n");
                    continue;

            }

            bestScore = Math.max(bestScore, tfe.getScore());
            if(!resetFlag) {
                tfe.placeRandom();
                resetFlag = false;
            }
        }
    }



    public void showBoard() {
        for(int x = 0; x < boardWidth * 6 + 1; x++){
            System.out.print("-");
        }
        System.out.println();

        for(int x = 0; x < boardWidth; x++) {
            for(int y = 0; y < boardWidth; y++) {
                String square = (board[x][y] == 0)? "":board[x][y] + "";
                System.out.printf("|%5s", square);
            }
            System.out.println("|");

            for(int y = 0; y < boardWidth * 6 + 1; y++){
                System.out.print("-");
            }
            System.out.println();
        }
    }

    public int getScore() {
        return score;
    }

}
