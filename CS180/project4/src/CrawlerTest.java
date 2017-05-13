import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

/**
 * Test Cases for Crawler
 *
 */

public class CrawlerTest {
    Crawler cl;

    @Before
    public void setUp() throws Exception {

    }

    @Test(timeout = 5000)
    // @ScoringWeight(.01)
    public void TestStaticQueue() throws Exception {
        cl = new Crawler("http://google.com", "www.cs.purdue.edu", 0);
        Crawler c2 = new Crawler("http://facebook.com", "www.cs.purdue.edu", 0);

        String retUrl = (String) c2.toParse.remove().getData();
        assertEquals("Your Queue should not be static in Crawler class.", "http://facebook.com", retUrl);

    }
    @Test(timeout = 5000)
    // @ScoringWeight(.01)
    public void TestAddWordToList() throws Exception {
        cl = new Crawler("https://www.cs.purdue.edu/homes/bxd/", "www.cs.purdue.edu", 0);
        cl.words.clear();
        cl.addWordToList("hello", 1);
        assertEquals(".addWordToList() should update the list .words", 1, cl.words.size());
        assertEquals(".addWordToList() should update the list .words", new Word("hello", 1), cl.words.get(0));
        cl.addWordToList("hello2", 2);
        assertEquals(".addWordToList() should update the list .words", 2, cl.words.size());
        assertEquals(".addWordToList() should update the list .words", new Word("hello2", 2), cl.words.get(1));
    }

    @Test(timeout = 5000)
    // @ScoringWeight(.01)
    public void TestAddToQueue() throws Exception {
        String testUrl1 = "https://www.cs.purdue.edu/homes/bxd/";
        String testUrl2 = "https://www.google.com";
        String testUrl3 = "https://www.facebook.com";
        String testUrl4 = "https://www.apple.com";
        cl = new Crawler("https://www.cs.purdue.edu/homes/bxd/", "www.cs.purdue.edu", 0);

        cl.addToQueue(testUrl2);
        assertEquals(".addToQueue() should increment the totalURLs", 1, cl.totalURLs );
        cl.addToQueue(testUrl3);
        assertEquals(".addToQueue() should increment the totalURLs", 2, cl.totalURLs );
        cl.addToQueue(testUrl4);
        assertEquals(".addToQueue() should increment the totalURLs", 3, cl.totalURLs );

        String retUrl = (String) cl.toParse.remove().getData();
        assertEquals("Incorrect URL retrieved.", testUrl1, retUrl);
        retUrl = (String) cl.toParse.remove().getData();
        assertEquals("Incorrect URL retrieved.", testUrl2, retUrl);

        retUrl = (String) cl.toParse.remove().getData();
        assertEquals("Incorrect URL retrieved.", testUrl3, retUrl);
        retUrl = (String) cl.toParse.remove().getData();
        assertEquals("Incorrect URL retrieved.", testUrl4, retUrl);
    }


    @Test(timeout = 5000)
    // @ScoringWeight(.01)
    public void TestIsInDomain() throws Exception {
        cl = new Crawler("https://www.cs.purdue.edu/homes/bxd/", "www.cs.purdue.edu", 0);
        assertEquals(".isInDomain() should return true if the url contains the domain.", true,
                cl.isInDomain("https://www.cs.purdue.edu/index.html"));
        assertEquals(".isInDomain() should return true if the url contains the domain.", true,
                cl.isInDomain("https://www.cs.purdue.edu/abcdehello.html"));
        assertEquals(".isInDomain() should return false if the url doesn't contain the domain.",
                false, cl.isInDomain("https://www.physics.purdue.edu/abcdef"));
        assertEquals(".isInDomain() should return false if the url doesn't contain the domain.",
                false, cl.isInDomain("https://www.google.com"));
    }

    @Test(timeout = 5000)
    // @ScoringWeight(.01)
    public void TestIsValidURL() throws Exception {
        cl = new Crawler("https://www.cs.purdue.edu/homes/bxd/", "www.cs.purdue.edu", 0);
        assertEquals(".isValidURL() should return true if the url is valid.",
                true, cl.isValidURL("https://www.cs.purdue.edu/index.html"));
        assertEquals(".isValidURL() should return true if the url is valid.",
                true, cl.isValidURL("http://www.google.com/abcdehello.html"));
        assertEquals(".isValidURL() should return false if the url is invalid.",
                false, cl.isValidURL("www.physics.purdue.edu/abcdef"));
        assertEquals(".isValidURL() should return false if the url is invalid.",
                false, cl.isValidURL("httpc://www.google.com"));
    }


    @Test(timeout = 600000)
    // @ScoringWeight(.01)
    public void TestCrawler() throws Exception {
        cl = new Crawler("https://www.cs.purdue.edu/homes/bxd/", "www.cs.purdue.edu", 50);
        cl.crawl();

        assertEquals("Crawler.parsed doesn't contain some link addresses",
                true, Crawler.parsed.contains(new Page("http://www.cs.purdue.edu/homes/cs177", 1)));
        assertEquals("Crawler.parsed doesn't contain some link addresses",
                true, Crawler.parsed.contains(new Page("http://www.cs.purdue.edu/homes/cs180", 2)));
        assertEquals("Crawler.parsed doesn't contain some link addresses",
                true, Crawler.parsed.contains(new Page("https://www.cs.purdue.edu/people/faculty/bxd", 3)));

        assertEquals("Crawler.words doesn't contain some words that should be included",
                true, Crawler.words.contains(new Word("purdue", 1)));
        assertEquals("Crawler.words doesn't contain some words that should be included",
                true, Crawler.words.contains(new Word("department", 2)));
        assertEquals("Crawler.words doesn't contain some words that should be included",
                true, Crawler.words.contains(new Word("programmers", 3)));
    }
}
