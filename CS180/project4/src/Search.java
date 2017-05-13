import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Created by sidshah on 4/16/17.
 */
public class Search {

    static List<Page> pageList = new ArrayList<>();
    private String pageListFile;
    static List<Result> resultSet;
    public static List<Word> wordList = new ArrayList<>();
    private String wordListFile;

    public Search(String wordListFile, String pageListFile){
        this.wordListFile = wordListFile;
        this.pageListFile = pageListFile;
        setup(wordListFile, pageListFile);
        resultSet = Collections.synchronizedList(new ArrayList<Result>());
    }

    public List<Result> executeQuery(String query){
        nullCheck();

        String terms[] = query.split(" ");

        Thread[] threads = new Thread[5];
        int j = 0;
        int perThLen = wordList.size() / 5;
        for(int i = 0; i < 5;i++){
            threads[i] = new Thread(new SearchThread(j, j + perThLen, terms));
            j += perThLen;
        }
        for(Thread t : threads){
            t.start();
        }
        for(Thread t : threads){
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        Collections.sort(resultSet);
        return resultSet;
    }

    public void setup(String wordListFile, String pageListFile) {
        FileUtils fu = new FileUtils();
        wordList = fu.getWordList(wordListFile);
        pageList = fu.getPageList(pageListFile);
    }

    public void nullCheck(){
        if(this.pageList == null){
            setup(this.wordListFile, this.pageListFile);
        }
        if(this.pageList.size() == 0){
            setup(this.wordListFile, this.pageListFile);
        }
        if(this.wordList == null){
            setup(this.wordListFile, this.pageListFile);
        }
        if(this.wordList.size() == 0){
            setup(this.wordListFile, this.pageListFile);
        }
    }


}
