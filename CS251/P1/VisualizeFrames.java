import java.util.*;
import java.io.*;
public class VisualizeFrames {
  //0-closed, 1-open, 2- full
	public void show(int[][] matrix) {
		int N=matrix.length;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (matrix[i][j]==2) 
				{

					StdDraw.setPenColor(StdDraw.BLUE);
					               
				}
				else 	if (matrix[i][j]==1)
				{		
					StdDraw.setPenColor(StdDraw.WHITE);
				}
				else 	if (matrix[i][j]==0)
				{		
					StdDraw.setPenColor(StdDraw.BLACK);
				}
			StdDraw.filledSquare(j+0.5,N-i-0.5, 0.45); 
            }
        }
    }

     public static void main(String[] args) throws IOException
     {
		BufferedReader br=new BufferedReader(new FileReader("visualMatrix.txt"));
		String line=null;
        line=br.readLine();
		br.readLine();
		int n=Integer.parseInt(line);
		StdDraw.setXscale(0, n);
        StdDraw.setYscale(0, n);
        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.show(0);
		while((line=br.readLine())!=null)		
		{
			List<String> list=new ArrayList<String>();
			int[][] temp=new int[n][n];
			for(int i=0;i<n;i++)
			{
				String[] data=line.split(" ");
				for(int j=0;j<n;j++)
				{
					temp[i][j]=Integer.parseInt(data[j]);				
				}
				line=br.readLine();
			}
			new VisualizeFrames().show(temp);
			StdDraw.show(200);
		}
     }
}
