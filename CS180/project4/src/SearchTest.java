import org.junit.Before;
import org.junit.Test;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

import static org.junit.Assert.assertTrue;

public class SearchTest {
    Search sr;
    private static final String testWordTable = "inputs/testWordTable4.txt";
    private static final String testPageTable = "inputs/testPageTable4.txt";
    private boolean correctEvaluation;
    private FileInputStream fis;
    private ObjectInputStream ois;
    private List<Result> res1;
    private List<Result> res2;
    private List<Result> res3;
    private List<Result> res4;


    @Before
    public void setUp() throws Exception {
        correctEvaluation = false;

        //Initialize Search object
        sr = new Search(testWordTable, testPageTable);

        //Populate result lists
        try
        {
            fis = new FileInputStream("inputs/searchTestResult1.txt");
            ois = new ObjectInputStream(fis);

            res1 = (List<Result>) ois.readObject();
            Collections.sort(res1);
            fis.close();
            ois.close();

            fis = new FileInputStream("inputs/searchTestResult2.txt");
            ois = new ObjectInputStream(fis);

            res2 = (List<Result>) ois.readObject();
            Collections.sort(res2);
            fis.close();
            ois.close();

            fis = new FileInputStream("inputs/searchTestResult3.txt");
            ois = new ObjectInputStream(fis);

            res3 = (List<Result>) ois.readObject();
            Collections.sort(res3);
            fis.close();
            ois.close();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        res4 = new ArrayList<>();
    }

    @Test(timeout = 1000)
    public void testSingleTermQuery() {
        List<Result> testList;

        //Single term query
        testList = sr.executeQuery("Purdue");
        boolean comparisonResult = resListCompareSorted(testList, res1);
        assertTrue("Failed to correctly execute query \"Purdue\"", correctEvaluation);
        assertTrue("Failed to correctly sort results of query \"Purdue\"", comparisonResult);
    }

    @Test(timeout = 1000)
    public void testMultiTermQuery() {
        List<Result> testList;

        //Multiple term query
        testList = sr.executeQuery("Computer Science Students");
        boolean comparisonResult = resListCompareSorted(testList, res2);
        assertTrue("Failed to correctly execute query \"Computer Science Students\"", correctEvaluation);
        assertTrue("Failed to correctly sort results of query \"Computer Science Students\"", comparisonResult);
    }

    @Test(timeout = 1000)
    public void testNumericalTermQuery() {
        List<Result> testList;

        //Numerical term query
        testList = sr.executeQuery("3");
        boolean comparisonResult = resListCompareSorted(testList, res3);
        assertTrue("Failed to correctly execute query \"3\"", correctEvaluation);
        assertTrue("Failed to correctly sort results of query \"3\"", comparisonResult);
    }

    @Test(timeout = 1000)
    public void testNonExistentTermQuery() {
        List<Result> testList;

        //Non-existent term query
        testList = sr.executeQuery("FakeWord");
        boolean comparisonResult = resListCompareSorted(testList, res4);
        assertTrue("Failed to correctly execute query \"FakeWord\"", correctEvaluation);
        assertTrue("Failed to correctly sort results of query \"FakeWord\"", comparisonResult);
    }

    private boolean resListCompareSorted(List<Result> resList1, List<Result> resList2)
    {
        //null checking
        if(resList1==null && resList2==null) {
            correctEvaluation = true;
            return true;
        }
        if((resList1 == null && resList2 != null) || (resList1 != null && resList2 == null)) {
            correctEvaluation = false;
            return false;
        }

        if(resList1.size()!=resList2.size()) {
            correctEvaluation = false;
            return false;
        }

        for(Result itemList1: resList1)
        {
            if(!resList2.contains(itemList1)) {
                correctEvaluation = false;
                return false;
            }
        }

        correctEvaluation = true;

        for (int i = 0; i < resList1.size(); i++) {
            if (!resList1.get(i).equals(resList2.get(i)))
                return false;
        }

        return true;
    }
}