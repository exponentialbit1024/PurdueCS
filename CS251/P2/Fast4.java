import java.util.Arrays;
import java.util.*;
import java.io.*;

public class Fast4 {
   public static void main(String[] args) {
     Scanner stdinOb = new Scanner(System.in);
     int numberOfPoints = stdinOb.nextInt();
     Fast usageObj = new Fast();

     Point[] points = new Point[numberOfPoints];
     int counter = 0;
     while(stdinOb.hasNextInt()){
       int x = stdinOb.nextInt();
       int y = stdinOb.nextInt();
       Point newPoint = new Point(x,y);
       points[counter] = newPoint;
       counter++;
     }

      counter = 1;
      /* iterate through all the input Points */
      for (int i = 0; i < numberOfPoints; i++) {
         /* All points except the current one ordered by the slope formed
            with the first one, points[i]*/
         Arrays.sort(points, i + 1, numberOfPoints, points[i].BY_SLOPE_ORDER);
         counter = 1;
         double previousSlope = 0;
         double currentSlope = 0;
         for (int j = i + 1; j < numberOfPoints; j++) {
            if (counter == 1) {
               previousSlope = points[i].slopeCalc(points[j]);
               counter++;
            } else {
               currentSlope = points[i].slopeCalc(points[j]);
               if (currentSlope != previousSlope) {
                  if (counter >= 4)
                     printLine(points, i, j - 1, counter);
                  previousSlope = currentSlope;
                  counter = 2;
               } else {
                  counter++;
               }
            }
         }
         if (counter >= 4)
            printLine(points, i, numberOfPoints - 1, counter);
      }
   }

   private static void printLine(Point[] points, int i, int j, int counter) {
      Point[] result = new Point[counter];
      result[0] = points[i];
      for (int k = 0; k < counter - 1; k++) {
         result[k + 1] = points[j - k];
      }
      Arrays.sort(result);
      // result[0].drawTo(result[counter - 1]);
      StdOut.print(result[0].getX());
      for (int k = 1; k < counter; k++) {
         StdOut.print(" -> " + result[k].getX());
      }
      StdOut.println("");
   }
}
