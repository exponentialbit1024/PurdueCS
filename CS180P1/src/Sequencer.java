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
    String combined = arrayConvert[0];
    for(int k = 0; k < arrayConvert.length; k++){
      if(!stringSanitize(arrayConvert[k])){
        return "DNA is invalid";
      }
    }
    for(int j = 0; j < arrayConvert.length - 1; j++){
      combined = concatTwoStrings(arrayConvert[j], arrayConvert[j + 1]);
    }
    return combined;
  }

  public int startCodonPosition(String fullDNA){
    return fullDNA.indexOf("atg");
  }

  public int endCodonPosition(String fullDNA){
    int endIndex = fullDNA.lastIndexOf("tag");
    if(endIndex == -1){
      endIndex = fullDNA.lastIndexOf("taa");
    }
    if(endIndex == -1){
      endIndex = fullDNA.lastIndexOf("tga");
    }
    return endIndex;
  }

  public static void main(String[] args){
    System.out.println("Input lowercase DNA fragments one line at a time. End with a blank line.");
    Scanner stdinOb = new Scanner(System.in);
    Sequencer usageObj = new Sequencer();

    ArrayList<String> allDNA = new ArrayList<String>();

    while(stdinOb.hasNextLine()){
      String inputSeq = stdinOb.nextLine();
      if(inputSeq.equals("")){
        break;
      }
      allDNA.add(inputSeq);
    }
    if(allDNA.size() == 0){
      // System.out.println("DNA is invalid");
    }else{
        System.out.print("Input DNA: ");
        String combinedDNA = usageObj.printCombinedDNA(allDNA);
        System.out.println(combinedDNA);
        int startIndex = usageObj.startCodonPosition(combinedDNA);
        if(startIndex == -1){
          System.out.println("DNA does not contain a gene start codon");
        }
        else{
          System.out.println("Start codon position: " + startIndex);
          int endIndex = usageObj.endCodonPosition(combinedDNA);
          if(endIndex == -1){
            System.out.println("DNA does not contain a gene end codon");
          }
          else{
            System.out.println("End codon position: " + endIndex);
            String snp = combinedDNA.substring(startIndex, endIndex);
            System.out.println("Gene: " + snp);
            if(snp.length() < 30){
              System.out.println("The gene is not long enough to continue.");
            }
            else{
              System.out.println();
              System.out.println("Analysis Results\n");
              char eyeChar = snp.charAt(20);
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
              char hairChar = snp.charAt(18);
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
              char tongChar = snp.charAt(8);
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
          }
        }
    }
  }
}
