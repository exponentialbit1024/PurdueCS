import java.util.*;
import java.io.*;

public class Fast{

  private static HashMap<Point, ArrayList<Double>> pointCol = new HashMap<Point, ArrayList<Double>>();
  public String finalStr = "";

  public boolean mapExist(Point point, double slope){
    if(pointCol.containsKey(point)){
      for(double allSl : pointCol.get(point)){
        if(allSl == slope){
          return true;
        }
      }
    }
    return false;
  }

  public void addMap(Point point, double slope){
    if(!pointCol.containsKey(point)){
      pointCol.put(point, new ArrayList<Double>());
    }
    pointCol.get(point).add(slope);
  }

  public static void main(String[] args){

    long startTime = System.currentTimeMillis();

    Scanner stdinOb = new Scanner(System.in);
    int numPoints = stdinOb.nextInt();
    Fast usageObj = new Fast();

    Point[] allPoints = new Point[numPoints];
    int pointAdder = 0;
    while(stdinOb.hasNextInt()){
      int x = stdinOb.nextInt();
      int y = stdinOb.nextInt();
      Point newPoint = new Point(x,y);
      allPoints[pointAdder] = newPoint;
      pointAdder++;
    }

    Point[] tempAllPts = new Point[numPoints];
    System.arraycopy(allPoints, 0 , tempAllPts, 0, numPoints);

    ArrayList<Point[]> tracker = new ArrayList<Point[]>();

    for(int i = 0; i < pointAdder;i++){
      System.arraycopy(tempAllPts, 0 , allPoints, 0, numPoints);
      Arrays.sort(allPoints, allPoints[i].BY_SLOPE_ORDER);

      double lastSlope = allPoints[0].slopeCalc(allPoints[1]);
      double curSlope = 0.0;
      int newIdx = 1;
      for(int j = 2; j < pointAdder; j++){
        curSlope = allPoints[0].slopeCalc(allPoints[j]);
        if(curSlope != lastSlope || j == pointAdder - 1){
          if(curSlope == lastSlope){
            j++;
          }
          if(j >= newIdx + 3 && !usageObj.mapExist(allPoints[0], lastSlope)){
            Point[] subTracker = new Point[j - newIdx + 1];
            subTracker[0] = allPoints[0];
            usageObj.addMap(allPoints[0], lastSlope);
            int m = 1;
            for(int k = newIdx; k < j;k++){
              subTracker[m] = allPoints[k];
              m++;
              usageObj.addMap(allPoints[k], lastSlope);
            }
            tracker.add(subTracker);
          }
          newIdx = j;
          lastSlope = curSlope;
        }
      }
    }

    for(int t = 0; t < tracker.size(); t++){
      Arrays.sort(tracker.get(t));
      int arrayl = tracker.get(t).length;
      StringBuilder sb = new StringBuilder();
      sb.append(arrayl + ":(").append(tracker.get(t)[0].getX() + ", " + tracker.get(t)[0].getY() + ")");
      for(int q = 1; q < arrayl - 1;q++){
        sb.append(" -> (").append(tracker.get(t)[q].getX() + ", " + tracker.get(t)[q].getY() +")");
      }
      sb.append(" -> (" + tracker.get(t)[arrayl - 1].getX() + ", " + tracker.get(t)[arrayl - 1].getY() + ")");

      System.out.println(sb);
      usageObj.finalStr += sb.toString();
      usageObj.finalStr += "\n";
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
      e.printStackTrace();
    }
    //long endTime = System.currentTimeMillis();
  //  double difference = ((double)endTime - startTime) / 1000;
    //System.out.println("Fast Time:" + difference);
  }
}
