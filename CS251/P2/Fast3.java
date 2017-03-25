import java.io.PrintWriter;
import java.util.*;

public class Fast {
    public void maxPoints(Point[] points) {
        if(points.length <= 0) return;
        if(points.length <= 2) return;

        int result = 0;
        Map<Double, Set<Point>> myMap = new HashMap<>();
        for(int i = 0; i < points.length; i++){

            HashMap<Double, List<Point>> hm = new HashMap<>();

            for(int j = 0; j < points.length; j++){
                if(j != i){
                    if(points[j].getX() == points[i].getX()){
                        continue;
                    }
                    double k = (double)(points[j].getY() - points[i].getY()) / (double)(points[j].getX() - points[i].getX());
                    if(hm.containsKey(k)){
                        hm.get(k).add(points[j]);
                    }else{
                        if(Math.abs(k) == 0.0) {
                            hm.put(0.0, new ArrayList<>());
                            hm.get(0.0).add(points[j]);
                        } else {
                            hm.put(k, new ArrayList<>());
                            hm.get(k).add(points[j]);
                        }
                    }
                }
            }

            for(double d: hm.keySet()) {
                List<Point> tempList = hm.get(d);
                for(Point p : tempList) {
                    if(!myMap.containsKey(d))
                        myMap.put(d, new HashSet<>());
                    myMap.get(d).add(p);
                }
            }
        }

        try {
            int z = 0;

            PrintWriter printWriter = new PrintWriter("visualPoints.txt");
            for(double d : myMap.keySet()) {
                Set<Point> pointsTemp = myMap.get(d);
                StringBuilder sb = new StringBuilder();
                if(pointsTemp.size() >= 3) {
                    List<Point> pointsList = new ArrayList<>(pointsTemp);
                    z++;
                    Collections.sort(pointsList, new Comparator<Point>() {
                        @Override
                        public int compare(Point o1, Point o2) {
                            return o1.getX() - o2.getX();
                        }
                    });
                    sb.append(pointsList.size()).append(":");
                    System.out.println("SLOPE: " + d);
                    for(int i = 0; i < pointsList.size(); i++) {
                        Point currentPoint = pointsList.get(i);
                        if(i != pointsList.size() - 1) {
                            sb.append("(").append(currentPoint.getX()).append(", ").append(currentPoint.getY()).append(")").append(" -> ");
                        } else {
                            sb.append("(").append(currentPoint.getX()).append(", ").append(currentPoint.getY()).append(")");
                        }
                    }

                    System.out.println(sb.toString());
                    printWriter.println(sb.toString());
                }
            }
            System.out.println(z);
            printWriter.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        Point[] points = new Point[n];
        int i = 0;
        while(i != n) {

            int x = scanner.nextInt();
            int y = scanner.nextInt();

            Point p = new Point(x, y);
            points[i++] = p;
        }

        new Fast().maxPoints(points);
    }
}
