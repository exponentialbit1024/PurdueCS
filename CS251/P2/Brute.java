import java.util.*;
import java.io.*;

public class Brute{

  public Brute(){
  }

  public void printerFn(Point[] colPoints){
    System.out.print("4:(");
    System.out.print(colPoints[0].xGetter());
    System.out.print(",");
    System.out.print(colPoints[0].yGetter() + ") -> (");

    System.out.print(colPoints[1].xGetter());
    System.out.print(",");
    System.out.print(colPoints[1].yGetter() + ") -> (");

    System.out.print(colPoints[2].xGetter());
    System.out.print(",");
    System.out.print(colPoints[2].yGetter() + ") -> (");

    System.out.print(colPoints[3].xGetter());
    System.out.print(",");
    System.out.println(colPoints[3].yGetter() + ")");

    BufferedWriter bw = null;
    File oFile = new File("./visualPoints.txt");
    FileWriter fw;

    try{
      if (!oFile.exists()) {
	     oFile.createNewFile();
	    }
      fw = new FileWriter(oFile, true);
      bw = new BufferedWriter(fw);

      bw.write("4:(");
      bw.write(Integer.toString(colPoints[0].xGetter()));
      bw.write(",");
      bw.write(Integer.toString(colPoints[0].yGetter()) + ") -> (");

      bw.write(Integer.toString(colPoints[1].xGetter()));
      bw.write(",");
      bw.write(Integer.toString(colPoints[1].yGetter()) + ") -> (");

      bw.write(Integer.toString(colPoints[2].xGetter()));
      bw.write(",");
      bw.write(Integer.toString(colPoints[2].yGetter()) + ") -> (");

      bw.write(Integer.toString(colPoints[3].xGetter()));
      bw.write(",");
      bw.write(Integer.toString(colPoints[3].yGetter()) + ")");
      bw.write("\n");
      bw.close();
    }catch(IOException e){

    }
  }

  public static void main(String[] args){
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
      for(int k = j + 1;k < pointAdder;k++){
        combo4[1] = allPoints[k];
        for(int i = k + 1; i < pointAdder;i++){
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
  }
}
