import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import org.junit.Before;
import org.junit.Test;

import java.io.File;
import java.util.ArrayList;

import static org.junit.Assert.*;

/**
 * The test cases for Parser
 */
public class ParserTest {

    Parser ps;

    @Before
    public void setUp() throws Exception {
        ps = new Parser();
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetDocumentNull() throws Exception {
        boolean getException = false;
        try {
            ps.getDocument(null);
        }
        catch (ParseException e) {
            getException = true;
        }
        assertTrue("Attempt to getDocument(null), but the expected ParseException is not caught. ",
                getException);
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetDocumentInvalidURL() throws Exception {
        boolean getException = false;
        try {
            ps.getDocument("abc");
        }
        catch (ParseException e) {
            getException = true;
        }
        assertTrue("Attempt to getDocument() with an invalid URL, but the expected ParseException is not caught. ",
                getException);
    }

    // We move this to be part of the demo,
    // since Vocareum doesn't support connecting to the external links
    // but you are welcome to test this locally.
//    @Test(timeout = 5000)
//    // @ScoringWeight(.01)
//    public void testGetDocument() throws Exception {
//        Document d = ps.getDocument("https://en.wikipedia.org/wiki/Purdue_University");
//        assertNotEquals("Attempt to get the document from https://en.wikipedia.org/wiki/Purdue_University, but " +
//                ".getDocument() returns a null.", null, d);
//    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetLinksNull() throws Exception {
        boolean getException = false;
        try {
            ps.getLinks(null);
        }
        catch (ParseException e) {
            getException = true;
        }
        assertTrue(".getLinks() should throw a ParseException, while we pass a null document in.", getException);
    }

    @Test(timeout = 5000)
    // @ScoringWeight(.01)
    public void testGetLinks() throws Exception {

        Document d = Jsoup.parse(new File("inputs/ParserTest1.html"), null);
        assertNotEquals("Cannot find the local input file (Should not happen).",
                null, d);
        Elements links = ps.getLinks(d);
        assertNotEquals("The returned links from .getLinks(d) should not be null.",
                null, links);

        // We test this by checking if several links are existed in the returned links.
        ArrayList<String> linkArray = new ArrayList<String>();
        for (Element link: links) {
            linkArray.add(link.attr("abs:href"));
        }
        assertTrue("https://www.cs.purdue.edu/people/faculty/index.html is expected to be founded in the returning links, but it is not.",
                linkArray.contains("https://www.cs.purdue.edu/people/faculty/index.html"));
        assertTrue("https://www.cs.purdue.edu/people/graduate-students/index.html is expected to be founded in the returning links, but it is not.",
                linkArray.contains("https://www.cs.purdue.edu/people/graduate-students/index.html"));
        assertTrue("https://www.cs.purdue.edu/future-students/index.html is expected to be founded in the returning links, but it is not.",
                linkArray.contains("https://www.cs.purdue.edu/future-students/index.html"));
        assertTrue("https://www.cs.purdue.edu/research/centers.html is expected to be founded in the returning links, but it is not.",
                linkArray.contains("https://www.cs.purdue.edu/research/centers.html"));
        assertTrue("https://www.cs.purdue.edu/research/funding.html is expected to be founded in the returning links, but it is not.",
                linkArray.contains("https://www.cs.purdue.edu/research/funding.html"));
    }

    @Test(timeout = 1000)
    // @ScoringWeight(.01)
    public void testGetBodyNull() throws Exception {
        boolean getException = false;
        try {
            ps.getBody(null);
        }
        catch (ParseException e) {
            getException = true;
        }
        assertTrue(".getBody() should throw a ParseException, while we pass a null document in.", getException);
    }

    @Test(timeout = 5000)
    // @ScoringWeight(.01)
    public void testGetBody() throws Exception {
        Document d = Jsoup.parse(new File("inputs/ParserTest1.html"), null);
        assertNotEquals("Cannot find the local input file (Should not happen).",
                null, d);

        // We test this by checking if some sentences are in the returned body.
        String body = ps.getBody(d);
        assertNotEquals(".getBody(d) should not return null, while we pass a valid document.", null, body);

        String s = "Purdue CS Facebook Purdue CS Twitter CS";
        assertTrue("Substring \"" + s + "\" should be found in the " +
                        "body of https://www.cs.purdue.edu/",
                body.contains(s));

        s = "Events Internships Graduation Survey Careers Resources Business Office Campus Map Facilities FTP";
        assertTrue("Substring \"" + s + "\" should be found in the " +
                        "body of https://www.cs.purdue.edu/",
                body.contains(s));

        s = "Alumni Distinguished Alumnus Past Distinguished Alumni Outstanding Alumni Past Outstanding Alumni Keep in Touch";
        assertTrue("Substring \"" + s + "\" should be found in the " +
                        "body of https://www.cs.purdue.edu/",
                body.contains(s));
    }
}
