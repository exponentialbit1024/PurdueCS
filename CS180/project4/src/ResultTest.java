import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class ResultTest {
    Result res;
    static private String testUrl = "http://www.purdue.edu";
    static private int testUrlID = 1769; //Arbitrary
    static private int testScore = 1;

    @Before
    public void setUp() throws Exception {
        res = new Result(testUrl, testUrlID);
        testScore = 1;
    }

    @Test(timeout = 1000)
    public void testSerialVersionUID() {
        assertEquals("Failed to implement correct serialVersionUID. Should be -938761094876384658L",
                -938761094876384658L, res.serialVersionUID);
    }

    @Test(timeout = 1000)
    public void testGetters() throws Exception {
        assertEquals("Failed to get the URL initialized by the constructor", testUrl, res.getURL());
        assertEquals("Failed to get the URLID initialized by the constructor", testUrlID, res.getURLID());
        assertEquals("Failed to get the current score", testScore, res.getScore());
    }

    @Test(timeout = 1000)
    public void testIncrementScore() throws Exception {
        testScore++;
        res.incrementScore();
        assertEquals("Failed to increment score", testScore, res.getScore());
    }

    @Test(timeout = 1000)
    public void testUpdateScore() {
        testScore += 783; //Arbitrary
        res.updateScore(783);
        assertEquals("Failed to update score", testScore, res.getScore());
    }
}