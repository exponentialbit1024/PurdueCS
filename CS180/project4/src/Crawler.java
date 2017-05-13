import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.util.*;
/**
 * Created by sidshah on 4/9/17.
 */
public class Crawler {
    public static int currentID;
    public static String domain;
    public static int limit;
    public static List<Page> parsed = new ArrayList<>();
    public static Parser parser;
    public MyQueue toParse;
    public static int totalURLs;
    public static List<String> visited = new ArrayList<>();
    public static List<Word> words = new ArrayList<>();

    public Crawler(String seed, String domain, int limit){
        this.domain = domain;
        this.limit = limit;
        currentID = 0;
        toParse = new MyQueue();
        parser = new Parser();
        totalURLs = 0;
        toParse.add(seed);
    }

    public void addPageToList(Page p){
        parsed.add(p);
    }

    public void addToQueue(String url){
        toParse.add(url);
        totalURLs++;
    }

    public void addWordToList(String word, int id){
        words.add(new Word(word,id));
    }

    public void crawl() throws ParseException {
        while(!toParse.isEmpty() && (currentID < limit)){
            System.out.println((currentID + 1) + "/" + limit + ", toParse size: " + toParse.size());
            String currentUrl = (String) toParse.remove().getData();
            Document jsoupDoc;
            try{
                jsoupDoc = parser.getDocument(currentUrl);
            }catch (ParseException e){
             continue;
            }
            boolean parseSuc = false;
            try{
                parseSuc = parse(jsoupDoc, currentID);
            }catch (ParseException e){
                continue;
            }
            if(parseSuc){
                currentID++;
            }
            addPageToList(new Page(currentUrl, currentID));
        }
    }

    public boolean isInDomain(String url){
        return url.contains(this.domain);
    }

    public boolean isValidURL(String url){
        String[] urlParts = url.split("//");
        if(urlParts[0].equals("http:") || urlParts[0].equals("https:")){
            return true;
        }else{
            return false;
        }
    }

    public boolean parse(Document doc, int id) throws ParseException{
        try{
            parseLinks(doc);
            parseText(doc, id);
            return true;
        }catch(ParseException e){
            return false;
        }catch (Exception e){
            return false;
        }
    }

    public void parseLinks(Document doc) throws ParseException {
        Elements links = parser.getLinks(doc);
        for(Element link : links){
            String absUrl = link.attr("abs:href");
            if(isInDomain(absUrl) && isValidURL(absUrl)){
                String linkStr = absUrl.split(" ")[0];
//                if(!toParse.contains(linkStr)){
                    addToQueue(linkStr);
//                }
            }
        }
    }

    public void parseText(Document doc, int id) throws ParseException {
        String bodyText = parser.getBody(doc);
        bodyText = bodyText.toLowerCase();
        String[] allWords = bodyText.split(" ");
        for(int i = 0; i < allWords.length; i++){
            addWordToList(allWords[i], id);
        }
    }

    public static void main(String[] args) throws ParseException {
        Crawler usageObj = new Crawler("http://www.purdue.edu","http://www.purdue.edu",10);
        usageObj.crawl();
    }
}
