import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by sidshah on 4/9/17.
 */
public class FileUtils extends Object {
    public FileUtils(){}

    public List<Page> getPageList(String filePath){
        if(filePath == null){
            return null;
        }
        if(filePath.length() == 0){
            return null;
        }
        try{
            File pageFile = new File(filePath);
            FileInputStream fis = new FileInputStream(pageFile);
            ObjectInputStream ois = new ObjectInputStream(fis);
            ArrayList<Page> returnPage = (ArrayList<Page>) ois.readObject();
            return returnPage;
        }catch (IOException e){
            return null;
        }catch (ClassNotFoundException e){
            return null;
        }
    }

    public boolean saveWordTable(List<Word> wordTable, String filePath){
        if(filePath == null){
            return false;
        }
        if(filePath.length() == 0){
            return false;
        }
        if(wordTable == null){
            return false;
        }
        try{
            FileOutputStream fw = new FileOutputStream(filePath);
            ObjectOutputStream obw = new ObjectOutputStream(fw);
            ArrayList<Word> wordArrayList = new ArrayList<>(wordTable);
            obw.writeObject(wordArrayList);
            obw.close();
            return true;
        }catch (IOException e){
            return false;
        }
    }

    public boolean savePageTable(List<Page> pageTable, String filePath){
        if(filePath == null){
            return false;
        }
        if(filePath.length() == 0){
            return false;
        }
        if(pageTable == null){
            return false;
        }

        try{
            FileOutputStream fw = new FileOutputStream(filePath);
            ObjectOutputStream obw = new ObjectOutputStream(fw);
            ArrayList<Page> pageArrayList = new ArrayList<>(pageTable);
            obw.writeObject(pageArrayList);
            obw.close();
            return true;
        }catch (IOException e){
            return false;
        }
    }

    public List<Word> getWordList(String filePath){
        if(filePath == null){
            return null;
        }
        if(filePath.length() == 0){
            return null;
        }
        try{
            FileInputStream fis = new FileInputStream(filePath);
            ObjectInputStream ois = new ObjectInputStream(fis);
            ArrayList<Word> returnPage = (ArrayList<Word>) ois.readObject();
            ois.close();
            fis.close();
            return returnPage;
        }catch (IOException e){
            return null;
        }catch (ClassNotFoundException e){
            return null;
        }
    }

}
