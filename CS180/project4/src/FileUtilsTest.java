import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

/**
 * Test Cases for FileUtils
 *
 */

// ToDo: make this as the hidden tests.
public class FileUtilsTest {
    FileUtils fu;

    static String tmpFileName = "tmp.txt";

    @Before
    public void setUp() throws Exception {
        fu = new FileUtils();
    }

    @After
    public void clean() throws Exception {
        try {
            File file = new File(tmpFileName);
            file.delete();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSaveWordTableNull() throws Exception {
        boolean ret = fu.saveWordTable(null, tmpFileName);
        assertEquals(".saveWordTable() should return false, when a null list is passed", false, ret);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSaveWordTableNullFilePath() throws Exception {
        List<Word> table = new ArrayList<Word>();
        boolean ret = fu.saveWordTable(table, null);
        assertEquals(".saveWordTable() should return false, when a null file name is passed", false, ret);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSaveWordTableEmptyList() throws Exception {
        List<Word> table = new ArrayList<Word>();
        boolean saved = fu.saveWordTable(table, tmpFileName);
        assertEquals(".saveWordTable() should return true, while the table is successfully saved.", true, saved);

        List<Word> retTable = _getWordList(tmpFileName);
        assertEquals("The saved word table does not have the right content.", table, retTable);
        clean();
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSaveWordTable1() throws Exception {
        List<Word> table = new ArrayList<Word>();
        table.add(new Word("hello", 1));
        boolean saved = fu.saveWordTable(table, tmpFileName);
        assertEquals(".saveWordTable() should return true, while the table is successfully saved.", true, saved);

        List<Word> retTable = _getWordList(tmpFileName);
        assertEquals("Attempt to save a word table with 1 element, but the saved word table does not have the right " +
                "content.", table, retTable);
        clean();
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSaveWordTable3() throws Exception {
        List<Word> table = new ArrayList<Word>();
        table.add(new Word("word1", 1));
        table.add(new Word("word2", 2));
        table.add(new Word("word3", 3));

        boolean saved = fu.saveWordTable(table, tmpFileName);
        assertEquals(".saveWordTable() should return true, while the table is successfully saved.", true, saved);

        List<Word> retTable = _getWordList(tmpFileName);
        assertEquals("Attempt to save a word table with 3 elements, but the saved word table does not have the right " +
                "content.", table, retTable);
        clean();
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSavePageTableNull() throws Exception {
        boolean ret = fu.savePageTable(null, tmpFileName);
        assertEquals(".saveParsed() should return false, when a null list is passed", false, ret);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSavePageTableNullFilePath() throws Exception {
        List<Page> table = new ArrayList<Page>();
        boolean ret = fu.savePageTable(table, null);
        assertEquals(".saveParsed() should return false, when a null file name is passed", false, ret);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSavePageTableEmptyList() throws Exception {
        List<Page> table = new ArrayList<Page>();
        boolean saved = fu.savePageTable(table, tmpFileName);
        assertEquals(".saveParsed() should return true, while the table is successfully saved.", true, saved);

        List<Page> retTable = _getPageList(tmpFileName);
        assertEquals("The saved page table does not have the right content.", table, retTable);
        clean();
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSavePageTable1() throws Exception {
        List<Page> table = new ArrayList<Page>();
        table.add(new Page("https://purdue.edu", 1));
        boolean saved = fu.savePageTable(table, tmpFileName);
        assertEquals(".saveParsed() should return true, while the table is successfully saved.", true, saved);

        List<Word> retTable = _getWordList(tmpFileName);
        assertEquals("Attempt to save a page table with 1 elements, but the saved page table does not have the right " +
                "content.", table, retTable);
        clean();
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testSavePageTable3() throws Exception {
        List<Page> table = new ArrayList<Page>();
        table.add(new Page("https://purdue.edu", 1));
        table.add(new Page("https://www.cs.purdue.edu/", 2));
        table.add(new Page("https://www.cs.purdue.edu/academic-programs/index.html", 3));

        boolean saved = fu.savePageTable(table, tmpFileName);
        assertEquals(".saveParsed() should return true, while the table is successfully saved.", true, saved);

        List<Word> retTable = _getWordList(tmpFileName);
        assertEquals("Attempt to save a page table with 1 elements, but the saved page table does not have the right " +
                "content.", table, retTable);
        clean();
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetWordListNull() throws Exception {
        List<Word> testTable = fu.getWordList(null);
        assertEquals(".getWordList() should return null, while any invalid argument is specified.", null, testTable);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetWordList() throws Exception {
        String fpath = "inputs/testWordTable1.txt";
        List<Word> goldTable = _getWordList(fpath);
        List<Word> testTable = fu.getWordList(fpath);
        assertEquals(".getWordList() returns an incorrect list.", testTable, goldTable);

        fpath = "inputs/testWordTable2.txt";
        goldTable = _getWordList(fpath);
        testTable = fu.getWordList(fpath);
        assertEquals(".getWordList() returns an incorrect list.", testTable, goldTable);

        fpath = "inputs/testWordTable3.txt";
        goldTable = _getWordList(fpath);
        testTable = fu.getWordList(fpath);
        assertEquals(".getWordList() returns an incorrect list.", testTable, goldTable);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetPageListNull() throws Exception {
        List<Page> testTable = fu.getPageList(null);
        assertEquals(".getPageList() should return null, while any invalid argument is specified.", null, testTable);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetPageList() throws Exception {
        String fpath = "inputs/testPageTable1.txt";
        List<Page> goldTable = _getPageList(fpath);
        List<Page> testTable = fu.getPageList(fpath);
        assertEquals(".getPageList() returns an incorrect list.", testTable, goldTable);

        fpath = "inputs/testPageTable2.txt";
        goldTable = _getPageList(fpath);
        testTable = fu.getPageList(fpath);
        assertEquals(".getPageList() returns an incorrect list.", testTable, goldTable);

        fpath = "inputs/testPageTable3.txt";
        goldTable = _getPageList(fpath);
        testTable = fu.getPageList(fpath);
        assertEquals(".getPageList() returns an incorrect list.", testTable, goldTable);
    }


    // --------------------------------------------

    private boolean _saveWordTable(List<Word> wordTable, String filePath)
    {
        if (wordTable == null || filePath == null)
            return false;
        try
        {
            FileOutputStream fos = new FileOutputStream(filePath);

            ObjectOutputStream oos = new ObjectOutputStream(fos);

            oos.writeObject(wordTable);

            oos.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return false;
        }

        return true;
    }

    private boolean _savePageTable(List<Page> pageTable, String filePath)
    {
        if (pageTable == null || filePath == null)
            return false;
        FileOutputStream fos = null;
        ObjectOutputStream oos = null;
        try
        {
            fos = new FileOutputStream(filePath);

            oos = new ObjectOutputStream(fos);

            oos.writeObject(pageTable);

        }
        catch(Exception e)
        {
            e.printStackTrace();
            return false;
        }
        finally
        {
            try
            {
                fos.close();
                oos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return true;
    }

    private List<Page> _getPageList(String filePath)
    {
        FileInputStream fis = null;
        ObjectInputStream ois = null;
        try
        {
            fis = new FileInputStream(filePath);
            ois = new ObjectInputStream(fis);

            List<Page> pages = (ArrayList<Page>) ois.readObject();
            return pages;
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        finally
        {
            try
            {
                ois.close();
                fis.close();


            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return null;
    }

    private List<Word> _getWordList(String filePath)
    {
        FileInputStream fis = null;
        ObjectInputStream ois = null;
        try
        {
            fis = new FileInputStream(filePath);
            ois = new ObjectInputStream(fis);

            @SuppressWarnings("unchecked")
            List<Word> words = (ArrayList<Word>) ois.readObject();
            return words;
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        finally
        {
            try
            {
                ois.close();
                fis.close();


            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return null;
    }
}
