import java.util.*;
import java.io.*;

public class Brute{

  public String finalStr = "";

  public Brute(){
  }

  public void printerFn(Point[] colPoints){

    StringBuilder sb = new StringBuilder();

    sb.append("4:(").append(colPoints[0].getX()).append(", ").append(colPoints[0].getY() + ") -> (").append(colPoints[1].getX());
    sb.append(", ").append(colPoints[1].getY() + ") -> (").append(colPoints[2].getX()).append(", ").append(colPoints[2].getY() + ") -> (");
    sb.append(colPoints[3].getX()).append(", ").append(colPoints[3].getY() + ")");

    System.out.println(sb.toString());
    finalStr += sb.toString();
    finalStr += "\n";
  }

  public static void main(String[] args){

    long startTime = System.currentTimeMillis();

    Scanner stdinOb = new Scanner(System.in);
    int numPoints = stdinOb.nextInt();
    Brute usageObj = new Brute();

    Point[] allPoints = new Point[numPoints];
    int pointAdder = 0;
    while(stdinOb.hasNextInt()){
      int x = stdinOb.nextInt();
      int y = stdinOb.nextInt();
      Point newPoint = new Point(x,y);
      allPoints[pointAdder] = newPoint;
      pointAdder++;
    }

    Arrays.sort(allPoints);

    Point[] combo4 = new Point[4];

    for(int j = 0; j < pointAdder - 3; j++){
      combo4[0] = allPoints[j];
      for(int k = j + 1;k < pointAdder - 2;k++){
        combo4[1] = allPoints[k];
        for(int i = k + 1; i < pointAdder - 1;i++){
          combo4[2] = allPoints[i];
          for(int y = i + 1;y < pointAdder; y++){
            combo4[3] = allPoints[y];
            boolean collinearCheck = Point.areCollinear(combo4[0],combo4[1],combo4[2],combo4[3]);
            if(collinearCheck){
              usageObj.printerFn(combo4);
            }
          }
        }
      }
    }

    BufferedWriter bw = null;
    File oFile = new File("./visualPoints.txt");
    FileWriter fw;

    try{
      if (!oFile.exists()) {
	     oFile.createNewFile();
	    }
      fw = new FileWriter(oFile);
      bw = new BufferedWriter(fw);

      bw.write(usageObj.finalStr);
      bw.write("\n");
      bw.close();
    }catch(IOException e){

    }

    // long endTime = System.currentTimeMillis();
    // double difference = ((double)endTime - startTime) / 1000;
//    System.out.println("Fast Time:" + difference);
  }
}
