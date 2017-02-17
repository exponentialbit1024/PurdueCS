import java.util.*;

public class Sequencer{

  private String currentSequence;

  public Sequencer(){
    currentSequence = "";
  }

  public boolean stringSanitize(String inputSeq){
    boolean check = true;
    for(int j = 0; j < inputSeq.length(); j++){
      check = inputSeq.charAt(j) == 'a' || inputSeq.charAt(j) == 't' || inputSeq.charAt(j) == 'g' || inputSeq.charAt(j) == 'c';
      if(!check){
        return check;
      }
    }
    return check;
  }

  public String[] convertArraylist(ArrayList inputSeq){
    String[] arrayConvert = new String[inputSeq.size()];
    for(int j = 0; j < inputSeq.size(); j++){
      try{
          arrayConvert[j] = (String)inputSeq.get(j);
      }catch(ClassCastException e){
        e.printStackTrace();
      }
    }
    return arrayConvert;
  }

  public String concatTwoStrings(String s1, String s2){
    String combined = "";
    for(int j = 0; j < s2.length(); j++){
      String subS2 = s2.substring(0, j);
      if(s1.endsWith(subS2)){
        combined = s1 + s2.substring(j, s2.length());
      }
    }
    return combined;
  }

  public String printCombinedDNA(ArrayList inputSeq){
    String[] arrayConvert = convertArraylist(inputSeq);
    String combined = "";
    for(int k = 0; k < arrayConvert.length; k++){
      if(!stringSanitize(arrayConvert[k])){
        System.out.println("DNA is invalid");
        return "";
      }
    }
    for(int j = 0; j < arrayConvert.length; j++){
      combined = concatTwoStrings(combined, arrayConvert[j]);
    }
    return combined;
  }

  public int startCodonPosition(String fullDNA){
    return fullDNA.indexOf("atg");
  }

  public int endCodonPosition(String fullDNA, int startIndex){
    int endIndex = fullDNA.indexOf("tag");
    int checkIndex = endIndex;
    ArrayList<Integer> tagIndices = new ArrayList<>();

    if(endIndex != -1){
      while(checkIndex >= 0){
        tagIndices.add(checkIndex);
        checkIndex = fullDNA.indexOf("tag", checkIndex + 1);
      }
    }

    int endIndex2 = fullDNA.indexOf("taa");
    int checkIndex2 = endIndex2;
    ArrayList<Integer> taaIndices = new ArrayList<>();

    if(endIndex2 != -1){
      while(checkIndex2 >= 0){
        taaIndices.add(checkIndex2);
        checkIndex2 = fullDNA.indexOf("taa", checkIndex2 + 1);
      }
    }

    int endIndex3 = fullDNA.indexOf("tga");
    int checkIndex3 = endIndex3;
//    System.out.println(endIndex3);
    ArrayList<Integer> tgaIndices = new ArrayList<>();

    if(endIndex3 != -1){
      while(checkIndex3 >= 0){
        tgaIndices.add(checkIndex3);
        checkIndex3 = fullDNA.indexOf("tga", checkIndex3 + 1);
      }
    }

    if(endIndex == -1 && endIndex2 == -1 && endIndex3 == -1){
      return -1;
    }

    ArrayList<Integer> allIndices = new ArrayList<>();
    if(tagIndices.size() > 0){
      allIndices.addAll(tagIndices);
    }
    if(taaIndices.size() > 0){
      allIndices.addAll(taaIndices);
    }
    if(tgaIndices.size() > 0){
      allIndices.addAll(tgaIndices);
    }

    Collections.sort(allIndices);
    int finalEndIndex = -1;

    for(int j = 0; j < allIndices.size(); j++){
      if(((allIndices.get(j) - startIndex) % 3) == 0){
        return allIndices.get(j);
      }
    }
    return finalEndIndex;
  }

  public void printEyeColor(String gene){
    char eyeChar = gene.charAt(20);
    switch(eyeChar){
      case 'a':
        System.out.println("Eye color: blue");
        break;
      case 't':
        System.out.println("Eye color: green");
        break;
      case 'c':
        System.out.println("Eye color: brown");
        break;
      case 'g':
        System.out.println("Eye color: brown");
        break;
    }
  }

  public void printhairColor(String gene){
    char hairChar = gene.charAt(18);
    switch(hairChar){
      case 'a':
        System.out.println("Hair color: black");
        break;
      case 't':
        System.out.println("Hair color: blond");
        break;
      case 'c':
        System.out.println("Hair color: brown");
        break;
      case 'g':
        System.out.println("Hair color: red");
        break;
    }
  }

  public void printTongueTwist(String gene){
    char tongChar = gene.charAt(8);
    switch(tongChar){
      case 'a':
        System.out.println("Can roll tongue? yes");
        break;
      case 't':
        System.out.println("Can roll tongue? no");
        break;
      case 'c':
        System.out.println("Can roll tongue? no");
        break;
      case 'g':
        System.out.print("Can roll tongue? no");
        break;
    }
  }

  public static void main(String[] args){
    Scanner stdinOb = new Scanner(System.in);
    Sequencer usageObj = new Sequencer();

    ArrayList<String> allDNA = new ArrayList<String>();
    System.out.println("Input lowercase DNA fragments one line at a time. End with a blank line.");
    while(stdinOb.hasNextLine()){
      String inputSeq = stdinOb.nextLine();
      if(inputSeq.equals("")){
        break;
      }
      allDNA.add(inputSeq);
    }
    String combinedDNA = usageObj.printCombinedDNA(allDNA);
    if(combinedDNA.length() != 0 || combinedDNA.equals("")){
      System.out.print("Input DNA: ");
      System.out.println(combinedDNA);
      int startCodonPosition = usageObj.startCodonPosition(combinedDNA);
      if(startCodonPosition != -1){
        int endCodonPosition = usageObj.endCodonPosition(combinedDNA, startCodonPosition);
        if(endCodonPosition != -1){
          System.out.println("Start codon position: " + Integer.toString(startCodonPosition));
          System.out.println("End codon position: " + Integer.toString(endCodonPosition));
          String gene = combinedDNA.substring(startCodonPosition, endCodonPosition);
          System.out.println("Gene: " + gene);
          if(endCodonPosition - startCodonPosition < 30){
            System.out.println("The gene is not long enough to continue.");
          }else{
            System.out.println();
            System.out.println("Analysis Results");
            System.out.println();
            usageObj.printEyeColor(gene);
            usageObj.printhairColor(gene);
            usageObj.printTongueTwist(gene);
          }
        }else{
         System.out.println("DNA does not contain a gene end codon");
        }
      }else{
        System.out.println("DNA does not contain a gene start codon");
      }
    }
  }
}
