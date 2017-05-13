import java.io.Serializable;

/**
 * Created by sidshah on 4/10/17.
 */
public class Result extends Object implements Serializable, Comparable<Result>{
    public static final long serialVersionUID = -938761094876384658L;
    private String url;
    private int urlID;
    public int score = 1;

    public Result(String url, int urlID){
        this.url = url;
        this.urlID = urlID;
    }

    public void updateScore(int score){
        this.score += score;
    }

    public void incrementScore(){
        this.score += 1;
    }

    public int getScore(){
        return this.score;
    }

    public String getURL(){
        return this.url;
    }

    public int getURLID(){
        return this.urlID;
    }

    @Override
    public int compareTo(Result candidate){
        if(this.getScore() > candidate.getScore()){
            return -1;
        }else if(candidate.getScore() > this.getScore()){
            return 1;
        }else{
            return 0;
        }
    }

    @Override
    public boolean equals(Object obj){
        Result candidate = (Result) obj;
        if(this.score == candidate.getScore()){
            if(this.url.equals(candidate.getURL())){
                if(this.urlID == candidate.getURLID()){
                    return true;
                }
            }
        }
        return false;
    }
}
