/*************************************************************************
 *  Compilation:  
 *  Windows: javac -classpath ".;stdlib.jar;" PointPlotter.java
 *  Unix: javac -classpath .:stdlib.jar PointPlotter.java
 *
 *  Execution: 
 *  Windows: java -classpath ".;stdlib.jar;" PointPlotter < inputFile.txt
 *  Unix: java -classpath .:stdlib.jar PointPlotter < inputFile.txt
 *
 *  Dependencies: stdlib.jar
 *
 *  Reads the file using StdIn
 *  Reads in an integer N followed by N pairs of points (x, y)
 *  with coordinates between 0 and 32767, and plots them using
 *  standard drawing.
 *
 *  PURDUE CS 25100 PROJECT 2, FEBRUARY 6, SPRING 2017 
 *
 *************************************************************************/
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class PointPlotter 
{
    public static void drawTo(int x, int y, int x2, int y2) 
    {
        StdDraw.line(x, y, x2, y2);
    }
    public static void draw(int x,int y) {
        StdDraw.point(x, y);
    }
    public static void main(String[] args) 
    {

        
        // rescale coordinates and turn on animation mode
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        StdDraw.show(0);
        StdDraw.setPenRadius(0.01);  // make the points a bit larger

        // read in the input
        int n = StdIn.readInt();
        while (!StdIn.isEmpty()) 
        {
            int x = StdIn.readInt();
            int y= StdIn.readInt();
            //plot the point
            draw(x, y);

        }

        StdDraw.setPenRadius();
        StdDraw.setPenColor(StdDraw.RED);
        
        try 
        {
            //open file which has output of Fast or Brute
            File file = new File("visualPoints.txt");
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            StringBuffer stringBuffer = new StringBuffer();
            String line;
            StringTokenizer st;
            //coordinates for points in a line
            int [] coordinates = new int [100];
            //counter for number of x and y coordinates(counter/2=no of points)
            int counter=0;
            while ((line = bufferedReader.readLine()) != null) 
            {
                //tokenize the line in the file so as to extract coordinates
                st = new StringTokenizer(line,"(,):-> ");
                while (st.hasMoreElements()) 
                {
                    coordinates[counter]=Integer.parseInt((st.nextElement()).toString());
                    counter++;
                }
                //plot a line with the first and last point
                drawTo(coordinates[1],coordinates[2],coordinates[counter-2],coordinates[counter-1]);
                counter=0;
            }
            fileReader.close();
        }
        catch (IOException e) 
        {
            e.printStackTrace();
        }
        // display
        StdDraw.show(0);

        // reset the pen radius
        StdDraw.setPenRadius();



    }
}
