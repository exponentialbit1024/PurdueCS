import java.io.*;
import java.util.ArrayList;

public class FileParse{
  public static int countWords(String fileName, String searchWord) throws Exception{
    File f = new File(fileName);
    FileInputStream fis = new FileInputStream(f);
    BufferedReader bfr = new BufferedReader(new InputStreamReader(fis));
    String read;
    int totalCount = 0;
    do{
      read = bfr.readLine();
      if(read != null){
          String[] allWords = read.split(" ");
          for(int i = 0; i < allWords.length; i++){
              if(allWords[i].equals(searchWord)){
                  totalCount++;
              }
          }
      }
    }while(read != null && read.length() != 0);

    bfr.close();
    System.out.println("Total number of occurrences: " + totalCount);
    return totalCount;
  }

  public static boolean deleteLine(String fileName, int lineNum) throws Exception{
      File f = new File(fileName);
      FileInputStream fis = new FileInputStream(f);
      BufferedReader bfr = new BufferedReader(new InputStreamReader(fis));
      String read;
      ArrayList<String> allLines = new ArrayList<String>();
      do{
          read = bfr.readLine();
          if(read != null){
              allLines.add(read);
          }
      }while(read != null && read.length() != 0);
      try {
          allLines.remove(lineNum);
          FileWriter fw = new FileWriter(f);
          for(int i = 0;i < allLines.size();i++){
              fw.write(allLines.get(i));
          }
          fw.close();
          System.out.println("Line deleted!");
          return true;
      }catch (Exception e){
          System.out.println("Line not found");
      }
      bfr.close();
      return false;
  }

  public static int refactor(String fileName, String original, String replace) throws Exception{
      File f = new File(fileName);
      FileInputStream fis = new FileInputStream(f);
      BufferedReader bfr = new BufferedReader(new InputStreamReader(fis));
      String read;
      ArrayList<String> allLines = new ArrayList<String>();
      int refCt = 0;
      do{
          read = bfr.readLine();
          if(read != null){

          }
      }while(read != null && read.length() != 0);
      bfr.close();
      FileWriter fw = new FileWriter(f);
      for(int j = 0; j < allLines.size();j++){
          fw.write(allLines.get(j));
      }
      fw.close();
      return refCt;
  }

  public static void main(String[] args){
      FileParse usageObj = new FileParse();
  }
}
