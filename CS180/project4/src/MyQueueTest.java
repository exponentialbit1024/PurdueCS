import org.junit.Before;
import org.junit.Test;

import java.util.Queue;

import static org.junit.Assert.*;

/**
 * JUnit tests for MyQueue
 */
public class MyQueueTest {

    MyQueue mq;
    @Before
    public void setUp() throws Exception {
        mq = new MyQueue();
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void queueCheatCheck() throws Exception {
        assertFalse("Your Queue should not implement java.util.Queue", mq instanceof Queue);

    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void addDifferentObjectTypes() throws Exception {
        /* Add a String object and an Integer object */
        mq.add("Project 4 is Fun!");
        mq.add(new Integer(3));

        /* Assert the size is correct */
        assertEquals(2, mq.size());

        /* Assert the removed item is a String, then the size is 1 */
        assertEquals("Attempt to add String failed. Check that your Node data field accepts" +
                " generic Objects", "Project 4 is Fun!", mq.remove().getData());
        assertEquals(1, mq.size());

        /* Assert the removed item is an Integer, then the size is 0 */
        assertEquals("Attempt to add Integer failed. Check that your Node data field accepts" +
                        " generic Objects", 3, ((Integer)mq.remove().getData()).intValue());
        assertEquals(0, mq.size());
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void addTenItems() throws Exception {

        /* Add 10 Objects to the Queue */
        for(int i = 0 ; i < 10; i++)
            mq.add(new Integer(i));

        /* Check that Queue is size 10 */
        assertEquals("Queue size is not 10.", 10, mq.size());

    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void checkPeek() throws Exception {
        /* Add an item */
        mq.add(new Integer(5));

        /* First check that the peek method returns 5 as expected */
        assertEquals("The Head element should be 5.", new Integer(5), (Integer)mq.peek().getData());

        /* Now check the queue size is still 1 */
        assertEquals("Peek should not change the Queue size.", 1, mq.size());
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void remove() throws Exception {
        mq.add("CS180");
        mq.add("Project 4");

        /* Check that both items are enqueued */
        assertEquals("Check that both are added to Queue", 2, mq.size());

        /* Remove and confirm that the item removed is CS180 */
        assertEquals("Check the order of your Queue.", "CS180", (String)mq.remove().getData());

        /* Confirm the Head is now Project 4*/
        assertEquals("Check your remove method.", "Project 4", (String)mq.peek().getData());

        /* Confirm size is 1 */
        assertEquals("Check size is appropriately updated", 1, mq.size());


    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void removeTenItems() throws Exception {
        /* Add 10 Objects to the Queue */
        for(int i = 0 ; i < 10; i++)
            mq.add(new Integer(i));

        /* Remove 5 then recheck */
        for(int i = 0; i < 5; i++)
            mq.remove();

        /* Check that the number of the head Node is 5 */
        assertEquals("The current Head Node should have data value 5",
                ((Integer)mq.peek().getData()).intValue(), 5);

        /* Remove 5 more then check the Queue is empty */
        for(int i = 0; i < 5; i++)
            mq.remove();

        /* Check that Queue is empty */
        assertEquals("Queue should be empty.", 0, mq.size());
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void removePastQueueEnd()
    {
        /* Add 10 Objects to the Queue */
        for(int i = 0 ; i < 10; i++)
            mq.add(new Integer(i));

        /* Remove 10 Objects to the Queue */
        for(int i = 0 ; i < 10; i++)
            mq.remove();

        /* Try and remove another item, should return null */
        assertEquals("Removing when no items should return null.", null, mq.remove());

    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void isEmpty() throws Exception {
        /* Add 10 Objects to the Queue */
        for(int i = 0 ; i < 10; i++)
            mq.add(new Integer(i));

        /* Check that Queue is empty */
        assertEquals("Queue should be empty.", false, mq.isEmpty());

        /* Remove 5 then recheck */
        for(int i = 0; i < 5; i++)
            mq.remove();

        /* Check that Queue is empty */
        assertEquals("Queue should be empty.", false, mq.isEmpty());

        /* Remove 5 more then check the Queue is empty */
        for(int i = 0; i < 5; i++)
            mq.remove();

        /* Check that Queue is empty */
        assertEquals("Queue should be empty.", true, mq.isEmpty());
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void size() throws Exception {
        /* Check initial size is 0 */
        assertEquals("Check the initial size is 0", 0, mq.size());

        mq.add("Item 1");

        /* Check size is now 1 */
        assertEquals("Adding 1 item size check failed. Size should be 1.", 1, mq.size());

        /* Add 5 items */
        for(int i = 0; i < 5; i++)
            mq.add(new Integer(i));

        /* Check size is 6 */
        assertEquals("Adding bulk items failed. Should be 6.", 6, mq.size());

        /* Remove one item then recheck */
        mq.remove();
        assertEquals("Removing 1 item size check failed. Size should be 5.", 5, mq.size());

        /* Remove 3 items */
        for(int i = 0; i < 3; i++)
            mq.remove();

        /* Recheck size */
        assertEquals("Bulk removing size check failed. Size should be 2.", 2, mq.size());


    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void stressTest() throws Exception {
        /* Add 100 Objects to the Queue */
        for(int i = 0 ; i < 100; i++)
            mq.add(new Integer(i));

        /* Check size */
        assertEquals("Size should be 100", 100, mq.size());

        /* Remove 31 then recheck */
        for(int i = 0; i < 37; i++)
            mq.remove();

        /* Check size */
        assertEquals("Size should be 63", 63, mq.size());
        assertEquals("isEmpty() should return false", false, mq.isEmpty());

        /* Remove 300 then recheck */
        for(int i = 0; i < 300; i++)
            mq.remove();

        /* Check size */
        assertEquals("Size should be 0", 0, mq.size());
        assertEquals("isEmpty() should return true", true, mq.isEmpty());

        /* Add 10 Objects to the Queue */
        for(int i = 0 ; i < 10; i++)
            mq.add(new Integer(i));

        assertEquals("Size should be 10", 10, mq.size());
        assertEquals("isEmpty() should return false", false, mq.isEmpty());

    }
}