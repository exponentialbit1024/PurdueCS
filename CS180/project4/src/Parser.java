import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;

/**
 * Created by sidshah on 3/31/17.
 */
public class Parser {
    public Document getDocument(String url) throws ParseException
    {
        if(url == null){
            throw new ParseException("getDocument() failed. String url is null.");
        }
        if(url.length() == 0){
            throw new ParseException("getDocument() failed. String url is empty.");
        }
        /* Prepare a Jsoup Document object to hold the page */
        Document d = null;

        /* Attempt a connection, throws IOException so be
         * prepared to handle that.
         */
        try
        {
            /* Connect to URL and get the web page */
            d = Jsoup.connect(url).timeout(3000).get();

        }
        catch (IOException e){
            throw new ParseException("getDocument() failed. Connection failed.");
        }catch (Exception e){
            throw new ParseException("getDocument() failed. Connection failed.");
        }

        /* Return the Document */
        if(d == null){
            throw new ParseException("Null Body");
        }

        return d;
    }

    public String getBody(Document d) throws ParseException {
        if(d == null){
            throw new ParseException("getBody() failed. Document parameter is null.");
        }
        /* Get the Document for the given web page */

        /* Null check */
        if (d == null) {
            System.out.println("Error retrieving document.");
            return "";
        }

        /* A HTML document has one <body> tag, so we can store its contents using an Element
         * object just as we did for links above by using the Document classes .body() method.
         * the Document classes .body() method;
         */
        Element body = d.body();
        String bodyText = body.text();
        return bodyText;
//        return bodyText.toLowerCase();
    }

    public Elements getLinks(Document d) throws ParseException{

        if(d == null) {
            throw new ParseException("getLinks() failed. Document parameter is null.");
        }

        Elements links = d.select("a[href]");

        return links;
    }

    public static void main(String[] args) throws ParseException{
        Parser usageObj = new Parser();
        String url = "https://purdue.edu";
        Document jsoupDoc = usageObj.getDocument(url);
//        System.out.println(jsoupDoc);
        Elements allLinks = usageObj.getLinks(jsoupDoc);
        for(Element link : allLinks){
            System.out.println(link);
        }
    }
}
