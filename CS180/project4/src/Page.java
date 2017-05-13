import java.io.Serializable;
import java.util.Objects;

/**
 * Created by Sabrina19 on 3/31/17.
 */
public class Page implements Comparable<Page>, Serializable{

    public static final long serialVersionUID = -1827677255104766839L;
    String url;
    private int urlID;

    public Page(String url, int urlID){
        this.urlID = urlID;
        this.url = url;

    }

    public int compareTo(Page candidate){
        if(this.urlID > candidate.urlID){
            return 1;
        }
        else if(this.urlID < candidate.urlID){
            return -1;
        }
        else{
            return 0;
        }
    }

    @Override
    public boolean equals(Object obj){
        Page objT = (Page) obj;
        if(this.url.equals(objT.url)){
            return true;
        }
        if(this.urlID ==objT.urlID){
            return true;
        }
        return false;

    }
    String getURL(){
        return url;

    }
    int getURLID(){
        return urlID;
    }

}
