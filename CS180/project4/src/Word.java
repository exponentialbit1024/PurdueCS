import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Sabrina19 on 3/31/17.
 */
public class Word extends Object implements Serializable{

    private String word;
    private List<Integer> postings = new ArrayList<Integer>();
    public static final long serialVersionUID = -3696191086353573895L;

    public Word(String word, int urlID){
        this.word = word;
        this.postings.add(urlID);
    }
    public void addURLID(int urlID){
        this.postings.add(urlID);
    }

    @Override
    public boolean equals(Object obj){
        Word objT = (Word) obj;
        if( this.word.equals(objT.word)){
            return true;
        }
        return false;
    }
    List<Integer> getList(){
            return this.postings;
    }
    String getWord(){
        return this.word;
    }

}
