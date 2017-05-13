import org.junit.Before;
import org.junit.Test;

import java.util.List;

import static org.junit.Assert.*;

public class WordTest {
    Word w;

    static String testWord = new String("hello");
    static int testUrlId = 1;

    @Before
    public void setUp() throws Exception {
        w = new Word(testWord, testUrlId);
    }

    @Test(timeout = 1000)
    public void testSerialVersionUID() {
        assertEquals("Failed to implement correct serialVersionUID. Should be -3696191086353573895L",
                -3696191086353573895L, w.serialVersionUID);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetWord() throws Exception {
        assertEquals("Failed to get the word initialized by the constructor.",
                testWord, w.getWord());
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetList() throws Exception {
        List<Integer> li = w.getList();
        assertNotEquals("The returned list should NOT be null.", null, li);
        assertEquals("The returned list size should be 1 after the object is constructed.", 1, li.size());
        assertEquals("The first entry in the returned list should be equal to the URLID given in the constructor " +
                "arguements.", testUrlId, li.get(0).intValue());
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testAddURLID() throws Exception {
        List<Integer> li = w.getList();
        assertNotEquals("Before calling .addURLID(), the .getList() should NOT return null.", null, li);
        assertEquals("Before calling .addURLID(), the .getList() should return the list with size 1.",
                1, li.size());
        assertEquals("Before calling .addURLID(), the first entry in the list returned by .getList() should be equal to" +
                " the URLID given in the constructor arguements.", testUrlId, li.get(0).intValue());

        w.addURLID(2);
        assertNotEquals("After calling .addURLID(2), the .getList() should NOT return null.", null, li);
        assertEquals("After calling .addURLID(2), the .getList() should return the list with size 2.",
                2, li.size());
        assertEquals("After calling .addURLID(2), the second entry in the list returned by .getList() should be equal " +
                "to 2", 2, li.get(1).intValue());
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testEquals() throws Exception {
        assertEquals("Two Word objects should be equal if the word strings given in their constructors are " +
                "the same.", new Word(testWord, 100), w);
        assertNotEquals("Two Word objects should NOT be equal if the word strings given in their constructors are " +
                "different.", new Word(testWord + "aaa", 100), w);
    }
}