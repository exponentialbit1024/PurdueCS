import java.util.*;

public class PercolationStats{

  public PercolationStats(int n){
  }

  public int threshLoop(int N){
    int openBoxes = 0;
    Percolation percolationUseOb = new Percolation(N);
    while(!percolationUseOb.percolates()){
      int randx = (int)StdRandom.uniform(0, N);
      int randy = (int)StdRandom.uniform(0, N);
      if(!percolationUseOb.isOpen(randx, randy)){
        percolationUseOb.open(randx, randy);
        openBoxes++;
      }
    }
    return openBoxes;
  }

  public int threshSlowLoop(int N){
    int openBoxes = 0;
    PercolationQuick percolationUseOb = new PercolationQuick(N);
    while(!percolationUseOb.percolates()){
      int randx = (int)StdRandom.uniform(0, N);
      int randy = (int)StdRandom.uniform(0, N);
      if(!percolationUseOb.isOpen(randx, randy)){
        percolationUseOb.open(randx, randy);
        openBoxes++;
      }
    }
    return openBoxes;
  }

  public double[] threshColLoop(int n, int t){
    double[] openCollection = new double[t];
    for(int k = 0; k < t; k++){
      openCollection[k] = (double)threshLoop(n) / (n * n);
    }
    return openCollection;
  }

  public double[] threshColSlowLoop(int n, int t){
    double[] openCollection = new double[t];
    long startMean = System.currentTimeMillis();
    for(int k = 0; k < t; k++){
      openCollection[k] = (double)threshSlowLoop(n) / (n * n);
    }
    return openCollection;
  }

  public static void main(String[] args){

    long startTime = System.currentTimeMillis();
    Scanner stdinOb = new Scanner(System.in);
    int N = Integer.parseInt(args[0]);
    int reps = Integer.parseInt(args[1]);
    String typeAlgo = args[2];

    PercolationStats usageObj = new PercolationStats(N);
    System.out.println("***OUTPUT BELOW***");

    if(typeAlgo.equals("fast")){
      long trialStartTime = System.currentTimeMillis();
      double[] trials = usageObj.threshColLoop(N, reps);
      long trialTime = System.currentTimeMillis() - trialStartTime;

      long meanStartTime = System.currentTimeMillis();
      System.out.println("mean threshold="+StdStats.mean(trials));
      long meanTime = System.currentTimeMillis() - meanStartTime;

      long stdStartTime = System.currentTimeMillis();
      System.out.println("std dev="+StdStats.stddev(trials));
      long stdTime = System.currentTimeMillis() - stdStartTime;

      System.out.println("time="+((double)System.currentTimeMillis() - startTime) / 1000);
      System.out.println("mean time="+((double)meanTime + trialTime) / 1000);
      System.out.println("stddev time="+((double)stdTime + trialTime) / 1000);
    }
    else if(typeAlgo.equals("slow")){
      long trialStartTime = System.currentTimeMillis();
      double[] trials = usageObj.threshColSlowLoop(N, reps);
      long trialTime = System.currentTimeMillis() - trialStartTime;

      long meanStartTime = System.currentTimeMillis();
      System.out.println("mean threshold="+StdStats.mean(trials));
      long meanTime = System.currentTimeMillis() - meanStartTime;

      long stdStartTime = System.currentTimeMillis();
      System.out.println("std dev="+StdStats.stddev(trials));
      long stdTime = System.currentTimeMillis() - stdStartTime;

      System.out.println("time="+((double)System.currentTimeMillis() - startTime) / 1000);
      System.out.println("mean time="+((double)meanTime + trialTime) / 1000);
      System.out.println("stddev time="+((double)stdTime + trialTime) / 1000);
    }
  }
}
