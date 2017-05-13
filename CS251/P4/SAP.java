import java.io.*;

public class SAP{
  private Digraph G;

  public SAP(Digraph G){
    this.G = G;
  }

  public int length(int v, int w) {
    BreadthFirstDirectedPaths bfsV = new BreadthFirstDirectedPaths(G, v);
    BreadthFirstDirectedPaths bfsW = new BreadthFirstDirectedPaths(G, w);
    int ancestor = ancestor(v, w);
    int pathLength;
    if (ancestor == - 1) {
        pathLength = -1;
    } else {
        pathLength = bfsV.distTo(ancestor) + bfsW.distTo(ancestor);
    }
    return pathLength;
  }

  public int ancestor(int v, int w) {
    BreadthFirstDirectedPaths bfsV = new BreadthFirstDirectedPaths(G, v);
    BreadthFirstDirectedPaths bfsW = new BreadthFirstDirectedPaths(G, w);
    int shortesAncestor = -1;
    int shortesPath = Integer.MAX_VALUE;
    Bag<Integer> ancestors = new Bag<Integer>();
    for (int i = 0; i < this.G.V(); i++) {
      if (bfsV.hasPathTo(i) && bfsW.hasPathTo(i)) {
          ancestors.add(i);
      }
    }
    for (Integer integer : ancestors) {
      if ((bfsV.distTo(integer) + bfsW.distTo(integer)) < shortesPath) {
        shortesPath = (bfsV.distTo(integer) + bfsW.distTo(integer));
        shortesAncestor = integer;
      }
    }
    return shortesAncestor;
  }

  public static void main(String[] args){
    if(args.length < 2){
      return;
    }
    In stdinOb = new In(args[0]);
    Digraph D = new Digraph(stdinOb);
    SAP usageObj = new SAP(D);
    In checkIn = new In(args[1]);
    while(!checkIn.isEmpty()){
      int v = checkIn.readInt();
      int w = checkIn.readInt();
      int length = usageObj.length(v,w);
      int ancestor = usageObj.ancestor(v,w);
      System.out.println("sap = " + length + " ancestor = " + ancestor);
    }
  }
}
