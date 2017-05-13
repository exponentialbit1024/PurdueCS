import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Driver class to manage the execution of different components.
 *
 */
public class Driver {
	/**
	 * Method to start a new crawler with a given number of threads.
	 */

	public void crawl()
	{
		long start = System.currentTimeMillis();

		Crawler c = new Crawler("https://cs.purdue.edu", "cs.purdue.edu", 250);
		try {
			c.crawl();
		} catch (ParseException e) {
			e.printStackTrace();
		}

		long end = System.currentTimeMillis();
    	System.out.println("Stats: ");
    	System.out.println("Number of parsed pages: " + Crawler.parsed.size());
    	System.out.println("Number of words: " + Crawler.words.size());
    	
    	System.out.println("Total time: " + (end - start) + "ms.");
	}

	/**
	 * Save the word and page table from Crawler to memory
	 * by calling the required FileUtils methods. 
	 */

	public void save()
	{
		// Save Info 
    	FileUtils f = new FileUtils();
    			
		// Save the Word Table 
		f.saveWordTable(Crawler.words, "words.txt");
		
		// Save Parsed List 
		f.savePageTable(Crawler.parsed, "parsed.txt");
	}

	/**
	 * Execute a query by invoking the necessary
	 * components of the Search class
	 * @param query - search terms to be processed
	 */

	public void search(String query)
	{
		// Prepare Search 
		Search s = new Search("words.txt", "parsed.txt");
		
		long start = System.currentTimeMillis();
		List<Result> result = s.executeQuery(query);
		long end = System.currentTimeMillis();
		
		System.out.println("Query: " + query);
		System.out.println(result.size() + " results found in " + (end - start) + "ms:\n");
		for(int i = 0; i < 10 && i < result.size(); i++)
		{
			Result r = result.get(i);
			System.out.println((i + 1) + ") " + r.getURL() + ", score: " + r.getScore());
		}
	}

	public static void main(String[] args)
    {    	
    	Driver d = new Driver();
//    	d.crawl();
//    	d.save();

    	Scanner sc = new Scanner(System.in);
    	while(true)
		{
			System.out.println("Enter query:");
			String query = sc.nextLine();

			d.search(query);

			System.out.println("\nContinue? (Yes / No)");

			while(true) {
				String decision = sc.nextLine();

				if (decision.equalsIgnoreCase("yes"))
					break;
				else if (decision.equalsIgnoreCase(("no")))
					System.exit(0);
				else
					System.out.println("Invalid response, try again:");
			}
		}

    }
}
