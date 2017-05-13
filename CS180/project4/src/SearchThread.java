import java.util.ArrayList;

/**
 * Created by sidshah on 4/13/17.
 */
public class SearchThread extends Object implements Runnable {

    private int finish;
    private int start;
    private String[] terms;

    @Override
    public synchronized void run() {
        for(String term : terms){
            Word newW = findTerm(term);
            if(newW != null){
                for(Integer id : newW.getList()){
                    boolean newFlag = true;
                    for(int i = 0; i < Search.resultSet.size(); i++){
                        if(Search.resultSet.get(i).getURLID() == id){
                            Search.resultSet.get(i).incrementScore();
                            newFlag = false;
                        }
                    }
                    if(newFlag){
                        Page newP = Search.pageList.get(id);
                        Search.resultSet.add(new Result(newP.getURL(), newP.getURLID()));
                    }
                }
            }
        }
    }

    public SearchThread(int start, int finish, String[] terms){
        this.start = start;
        this.finish = finish;
        this.terms = terms;
    }

    public Word findTerm(String term){
        term = term.toLowerCase();
        for(int i = this.start; i < this.finish; i++){
            Word newW = Search.wordList.get(i);
            if(newW.getWord().equalsIgnoreCase(term)){
                return newW;
            }
        }
        return null;
    }
}
