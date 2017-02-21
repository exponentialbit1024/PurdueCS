import java.util.*;
import java.io.*;

public class Fast{
  public Fast(){

  }

  public void getOverlapped(Point[] first, Point[] second){
    HashSet<Point> set1 = new HashSet<Point>(Arrays.asList(first));
    HashSet<Point> setT = new HashSet<Point>(Arrays.asList(first));
    HashSet<Point> set2 = new HashSet<Point>(Arrays.asList(second));
    set1.retainAll(set2);

    Point[] differences = set1.toArray(new Point[0]);
    for(int u = 0; u < differences.length; u++){
      System.out.print(differences[u].xGetter() + " ");
    }
    System.out.println();
  }

  public static void main(String[] args){
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
    ArrayList<Point[]> collinearPts = new ArrayList<Point[]>();
    for(int i = 0; i < pointAdder; i++){
      Arrays.sort(allPoints, allPoints[i].BY_SLOPE_ORDER);

        // System.out.println("Here");
        // for(int l = 0; l < allPoints.length;l++){
          // System.out.print(allPoints[l].xGetter() + " ");
        // }
        // System.out.println();

      ArrayList<Point> subColPts = new ArrayList<Point>();
      for(int j = 0; j < pointAdder - 1; j++){
        for(int r = 0; r < pointAdder - 1; r++){
          if(i == j){
            continue;
          }
          if(subColPts.isEmpty()){
            subColPts.add(allPoints[i]);
          }
          if(allPoints[i].slopeCalc(allPoints[r]) == allPoints[j].slopeCalc(allPoints[r])){
            subColPts.add(allPoints[j]);
          }
        }

      }
      Point[] tsubColpt = subColPts.toArray(new Point[subColPts.size()]);
      collinearPts.add(tsubColpt);
    }
    for(int y = 0; y < collinearPts.size() - 1; y++){
      Point[] first = collinearPts.get(y);
      Point[] second = collinearPts.get(y+1);
      usageObj.getOverlapped(first, second);
      // for(int u = 0; u < collinearPts.get(y).length; u++){
        // System.out.print(collinearPts.get(y)[u].xGetter() + " ");
      // }
      // System.out.println();
    }
  }
}
