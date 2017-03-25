import java.util.*;
import java.io.*;

public class Fast2 {
    private static HashMap<Point, ArrayList<Double>> lines = new HashMap<Point, ArrayList<Double>>();

    public static void main(String[] args) {
      Scanner stdinOb = new Scanner(System.in);
      int N = stdinOb.nextInt();
      Fast usageObj = new Fast();

      Point[] points = new Point[N];
      int n = 0;
      while(stdinOb.hasNextInt()){
        int x = stdinOb.nextInt();
        int y = stdinOb.nextInt();
        Point newPoint = new Point(x,y);
        points[n] = newPoint;
        n++;
      }

        Point[] sortedPoints = new Point[N];
        Arrays.sort(points);
        System.arraycopy(points, 0, sortedPoints, 0, N);

        for (int i = 0; i < N - 3; i++) {
            System.arraycopy(sortedPoints, 0, points, 0, N);
            Arrays.sort(points, points[i].BY_SLOPE_ORDER);

            int start = 1;
            int j = 2;
            double slope = points[0].slopeCalc(points[start]);
            while (j < N) {
              double slope1 = points[0].slopeCalc(points[j]);
              if ((slope1 != slope || j == N - 1)) {
                  if (slope1 == slope) {
                      j++;
                  }
              if (j >= start + 3 && !existed(points[0], slope)) {
                  System.out.println("SLOPE " + slope);
                  System.out.print(points[0].getX() + "," + points[0].getY());
                  addLine(points[0], slope);
                  for (int k = start; k < j; k++) {
                      System.out.print(" -> " + points[k].getX() + "," + points[k].getY());
                      addLine(points[k], slope);
                  }
                  System.out.println();
              }
              start = j;
              slope = slope1;
            }
            j++;
        }
      }
    }

    private static boolean existed(Point p, double slope) {
        if (lines.containsKey(p)) {
            for (double val : lines.get(p)) {
                if (val == slope) {
                    return true;
                }
            }
        }
        return false;
    }

    private static void addLine(Point p, double slope) {
        if (!lines.containsKey(p)) {
            lines.put(p, new ArrayList<Double>());
        }
        lines.get(p).add(slope);
    }
}
