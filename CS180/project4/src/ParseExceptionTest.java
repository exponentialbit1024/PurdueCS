import org.jsoup.nodes.Document;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class ParseExceptionTest {
    Parser parser;

    @Before
    public void setUp() throws Exception {
        parser = new Parser();
    }

    @Test(timeout = 1000)
    public void testGetDocumentNullStringThrowsParseException() {

        try {
            parser.getDocument(null);
        } catch (Exception e) {
            assertTrue("Exception should be of type ParseException.", e instanceof ParseException);
        }
    }
    @Test(timeout = 1000)
    public void testGetDocumentNullStringExceptionMessage() {

        try {
            parser.getDocument(null);
        } catch (Exception e) {
            assertEquals("Check that the message you are throwing is correct.", "getDocument() failed. String url is null.", e.getMessage());
        }
    }
    @Test(timeout = 1000)
    public void testGetDocumentEmptyStringThrowsParseException() {

        try {
            parser.getDocument("");
        } catch (Exception e) {
            assertEquals("Check that the message you are throwing is correct.", "getDocument() failed. String url is empty.", e.getMessage());
        }
    }
    @Test(timeout = 1000)
    public void testGetDocumentParseExceptionThrown() {

        try {
            parser.getDocument("http://");
        } catch (Exception e) {
            assertTrue("Exception should be of type ParseException.", e instanceof ParseException);
        }
    }
    @Test(timeout = 1000)
    public void testGetDocumentParseExceptionMessage() {

        try {
            parser.getDocument("http://");
        } catch (Exception e) {
            assertEquals("Check that the message you are throwing is correct.", "getDocument() failed. Connection failed.", e.getMessage());
        }
    }
    @Test(timeout = 1000)
    public void testGetLinksParseExceptionThrown() {

        try {
            parser.getLinks(null);
        } catch (ParseException e) {
            assertTrue("Exception should be of type ParseException.", e instanceof ParseException);

        }
    }
    @Test(timeout = 1000)
    public void testGetLinksParseExceptionMessage() {

        try {
            parser.getLinks(null);
        } catch (Exception e) {
            assertEquals("Check that the message you are throwing is correct.",
                    "getLinks() failed. Document parameter is null.", e.getMessage());
        }
    }
    @Test(timeout = 1000)
    public void testGetBodyParseExceptionThrown() {

        try {
            parser.getBody(null);
        } catch (ParseException e) {
            assertTrue("Exception should be of type ParseException.", e instanceof ParseException);

        }
    }
    @Test(timeout = 1000)
    public void testGetBodyParseExceptionMessage() {

        try {
            parser.getBody(null);
        } catch (Exception e) {
            assertEquals("Check that the message you are throwing is correct.",
                    "getBody() failed. Document parameter is null.", e.getMessage());
        }
    }

}