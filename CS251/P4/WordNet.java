import java.io.*;
import java.util.*;

public class WordNet{

  private SAP sapObj;
  private HashMap<String, Stack<Integer>> wMap;
  private HashMap<Integer, Stack<String>> iMap;

  public WordNet(String synsets, String hypernyms) {
    In synsetIn = new In(new File(synsets));
    In hypernymIn = new In(new File(hypernyms));
    this.wMap = new HashMap<String, Stack<Integer>>();
    this.iMap = new HashMap<Integer, Stack<String>>();
    int lengthDGraph = 0;
    while(synsetIn.hasNextLine()){
      String line = synsetIn.readLine();
      String[] elements = line.split(",");
      int wordId = Integer.parseInt(elements[0]);
      String[] allNouns = elements[1].split(" ");
      Stack<String> words = new Stack<String>();
      for(int i = 0; i < allNouns.length;i++){
        words.push(allNouns[i]);
        Stack<Integer> aIds = new Stack<Integer>();
        if(this.wMap.containsKey(allNouns[i])){
          aIds = this.wMap.get(allNouns[i]);
        }
        aIds.push(wordId);
        this.wMap.put(allNouns[i], aIds);
      }
      this.iMap.put(wordId, words);
      if(wordId > lengthDGraph){
        lengthDGraph = wordId;
      }
    }
    Digraph G = new Digraph(lengthDGraph + 1);
    while(hypernymIn.hasNextLine()){
      String lineH = hypernymIn.readLine();
      String[] elementsH = lineH.split(",");
      int vertex = Integer.parseInt(elementsH[0]);
      for(int i = 1; i < elementsH.length; i++){
        int wedge = Integer.parseInt(elementsH[i]);
        G.addEdge(vertex, wedge);
      }
    }
    sapObj = new SAP(G);
  }

  public boolean isNoun(String word) {
    return this.wMap.containsKey(word);
  }

  public void printSap(String nounA, String nounB) {
    if(isNoun(nounA) && isNoun(nounB)){
      Stack<Integer> A = this.wMap.get(nounA);
      Stack<Integer> B = this.wMap.get(nounB);

      HashMap<String, Integer> printer = new HashMap<String, Integer>();
      int shortestLength = Integer.MAX_VALUE;

      for(Integer a : A){
        for(Integer b : B){
          String ancestor = this.iMap.get(sapObj.ancestor(a,b)).peek();
          int sLen = sapObj.length(a, b);
          if(sLen < shortestLength){
            printer.put(ancestor, sLen);
            shortestLength = sLen;
          }
        }
      }
      for(Map.Entry<String,Integer> entry : printer.entrySet()){
          System.out.println("sap = " + entry.getValue() + " ancestor = " + entry.getKey());
      }

    }else{
      System.out.println("sap = -1, ancestor = null");
    }
  }

  public static void main(String[] args){
    if(args.length < 3){
      return;
    }
    WordNet usageObj = new WordNet(args[0], args[1]);
    In stdinOb = new In(args[2]);
    while(stdinOb.hasNextLine()){
      String line = stdinOb.readLine();
      String[] inputs = line.split(" ");
      String nounA = inputs[0];
      String nounB = inputs[1];
      usageObj.printSap(nounA, nounB);
    }
  }
}
