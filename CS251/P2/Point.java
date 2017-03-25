/*************************************************************************
 * Compilation:  javac Point.java
 *
 * Description: An immutable data type for points in the plane.
 *
 *************************************************************************/

import java.util.Comparator;

public class Point implements Comparable<Point>{
    // compare points by slope

    public final Comparator<Point> BY_SLOPE_ORDER = new Comparator<Point>(){
      public int compare(Point p1, Point p2) {
        double slope1 = slopeCalc(p1);
        double slope2 = slopeCalc(p2);
        if (slope1 == slope2) {
            return 0;
        }
        if (slope1 < slope2) {
            return -1;
        }
        return 1;
      }
    };

    private final int x;                              // x coordinate
    private final int y;                              // y coordinate

    public double slopeCalc(Point point){
      if (point == null) {
          throw new NullPointerException();
      }
      if (point.x == x) {
          if (point.y == y) {
              return Double.NEGATIVE_INFINITY;
          }
          return Double.POSITIVE_INFINITY;
      }
      if (point.y == y) {
          return 0.0;
      }
      return (double) (point.y - this.y) / (point.x - this.x);
    }

    // constructor
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX(){
      return this.x;
    }

    public int getY(){
      return this.y;
    }

    // are the 3 points p, q, and r collinear?
    public static boolean areCollinear(Point p, Point q, Point r) {
        int x1 = p.x;
        int x2 = q.x;
        int x3 = r.x;
        int y1 = p.y;
        int y2 = q.y;
        int y3 = r.y;
        int area = 0;

        int d1 = (x2 * y3) - (x3 * y2);
        int d2 = (x3 * y1) - (x1 * y3);
        int d3 = (x1 * y2) - (x2 * y1);

        area = d1 + d2 + d3;
        if(area == 0){
          return true;
        }
        else{
          return false;
        }
    }

    // are the 4 points p, q, r, and s collinear?
    public static boolean areCollinear(Point p, Point q, Point r, Point s) {
      boolean checkf3 = Point.areCollinear(p,q,r);
      if(!checkf3){
        return false;
      }
      else{
        boolean checkf4 = Point.areCollinear(q,r,s);
        if(!checkf4){
          return false;
        }
        else{
          return true;
        }
      }
    }

    // is this point lexicographically smaller than that one?
    public int compareTo(Point comPoint) {
      if (y == comPoint.y && x == comPoint.x) {
          return 0;
      }
      if (x < comPoint.x || (x == comPoint.x && y < comPoint.y)) {
          return -1;
      }
      return 1;
    }

    @Override
    public int hashCode() {
        return (x + "" + y).hashCode();
    }
}
