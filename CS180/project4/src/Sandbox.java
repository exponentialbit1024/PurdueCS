/**
 * Project 5 - Sandbox
 *
 * This program contains example usage of different JSoup library components
 * in order to get students started.
 *
 * @author Andrew Blejde
 */

/* Imports from the Jsoup library */
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;

/*
 * =========== Overview ===========
 * For this project we will be parsing web pages using a powerful parsing library
 * called JSoup. This file will give you the basic tools that you will need in order
 * to get started. First, a word about HTML pages.
 *
 * HTML pages have the following structure;
 *
 * <html>
 *     <head>
 *         <title> Hello CS180 </title>
 *     </head>
 *     <body>
 *         <!-- Some Content -->
 *         <a href = "https://purdue.edu">Purdue</a>
 *     </body>
 * </html>
 *
 * For this project, we will be interested in extracting the contents of the
 * <body> .. </body> tags, as well as the links represented as <a href="..">.
 */
public class Sandbox
{
    public Document getDocument(String url)
    {
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
        catch (IOException e)
        {
            /* Print the stack trace */
            e.printStackTrace();
        }

        /* Return the Document */
        return d;
    }
    /**
     * Method to access a given URL and print the web page title
     * @param url - website to access
     */
    public void printTitle(String url)
    {
        /* Get the Document for the given web page */
        Document d = getDocument(url);

        /* Null check */
        if(d == null)
        {
            System.out.println("Error retrieving document.");
            return;
        }

        /* Print the document title */
        System.out.println("Web page: " + url);
        System.out.println("Title: " + d.title());

        /* More information on the Document object can be found at;
         * https://jsoup.org/apidocs/org/jsoup/nodes/Document.html
         */
    }

    /**
     * Method to extract and enumerate all links on a given web page
     * @param url - web page to extract links from
     */
    public void printLinks(String url)
    {
        /* Get the Document for the given web page */
        Document d = getDocument(url);

        /* Null check */
        if(d == null)
        {
            System.out.println("Error retrieving document.");
            return;
        }

        /* A Document is composed of Elements. In our case, we have a HTML
         * Document that is composed of tag Elements (e.g. <body>, <a href ..>).
         * To get the links on a web page, we need to select just that specific
         * type of tag, which is designated in HTML as <a href = " " >
         *
         * From the documentation, we see that the .select() method returns an
         * Elements object, which is an ArrayList composed of multiple Element objects.
         *
         * https://jsoup.org/apidocs/org/jsoup/select/Elements.html#select-java.lang.String-
         */
        Elements links = d.select("a[href]");

        /* Elements in an ArrayList of Element objects, in our case we selected link Elements
         * and now have an ArrayList of all link Element object (e.g. one Element might be http://purdue.edu.
         * Now we can iterate over this list of Element objects.
         */
        for(Element link : links)
        {
            /* Links in HTML are structured as <a href = "link" >. We want to access the contents
             * of that 'href' piece for all of our link Element objects. Looking at the documentation
             *  for Element, we can do that like below;
             *
             *  https://jsoup.org/apidocs/org/jsoup/nodes/Element.html#attr-java.lang.String-java.lang.String-
             */
            System.out.println(link.attr("abs:href"));
        }

        /* In this project, you will need to do this to get and store the links on each page you visit.
         */
    }

    /**
     * Method to print the contents of a web pages body to the console.
     * @param url - web page to extract body text from
     */
    public void printBody(String url)
    {
        /* Get the Document for the given web page */
        Document d = getDocument(url);

        /* Null check */
        if(d == null)
        {
            System.out.println("Error retrieving document.");
            return;
        }

        /* A HTML document has one <body> tag, so we can store its contents using an Element
         * object just as we did for links above by using the Document classes .body() method.
         * the Document classes .body() method;
         */
        Element body = d.body();

        /* To extract the raw text from inside the <body> .. </body> tags, we can use the Element
         * classes .text() method.
         * For example, given HTML <p>Hello <b>there</b> now! </p>, p.text() returns "Hello there now!"
         *
         * Documentation; https://jsoup.org/apidocs/org/jsoup/nodes/Element.html#text--
         */
        System.out.println(body.text());

        /* For your web crawler, you will need fetch the contents of a web pages body like above, but also
         * come up with a way to count and store words in order to query it later. More information about this
         * can be found in the handout.
         */
    }
    /**
     * Main method to run methods within this Sandbox class
     * @param args
     */
    public static void main(String[] args)
    {
        Sandbox sb = new Sandbox();

        /* URL we will use for these examples */
        String url = "https://purdue.edu";

        Document jsoupDoc = sb.getDocument(url);
        System.out.println(jsoupDoc);
        /* Print a web page title */
        // sb.printTitle(url);

        /* Print all links on a web page */
        // sb.printLinks(url);

        /* Print the body of a web page */
//        sb.printBody(url);
    }
}
