import java.util.*;

public class Sequencer{

  private String currentSequence;

  public Sequencer(){
    currentSequence = "";
  }

  public String currentSequenceGetter(){
    return this.currentSequence;
  }

  public String printCombinedDNA(ArrayList inputSeq){
    String[] arrayConvert = new String[inputSeq.size()];
    for(int j = 0; j < inputSeq.size(); j++){
      try{
          arrayConvert[j] = (String)inputSeq.get(j);
      }catch(Exception e){
        e.printStackTrace();
      }

    }
    return arrayConvert[0];
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
    System.out.println(usageObj.printCombinedDNA(allDNA));
  }
}
