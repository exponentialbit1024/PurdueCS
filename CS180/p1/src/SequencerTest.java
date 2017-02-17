import junit.framework.TestCase;
import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.Timeout;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

/**
 * Created by joseph on 4/19/16.
 */
public class SequencerTest extends TestCase {

    ///////////////////////////////////////////////////////////////////////////
    // The following variables can be changed for the user and online test-cases
    ///////////////////////////////////////////////////////////////////////////
    private static final String BAD_DNA = "atcgb";
    private static final String GOOD_DNA_ONE_LINE = "atcgatcg";

    private static final String GOOD_DNA_MULTILINE = multiline("tatatatataccc","tacccggg",""); // must end with blank
    private static final String GOOD_DNA_MULTILINE_RESULT = "tatatatatacccggg"; // expected output of above

    private static final String NO_START_CODON = "catcatcatcatcatcat";
    private static final String NO_END_CODON = "atgcccccc"; // string that starts with the start codon (atg)
    private static final String WRONG_PLACE_END = "atgctag"; // no multiple of 3 characters between


    private static final String GOOD_GENE = "tatatataatgaccggcagtctatatgactctgatgccgcaggctgcctctgaga" +
            "ttttggcgatatatcggtattcatgaggtccacatatccatgcttacctcacaggtatacggtcctgagtgacgaaagtaggaaa";
    private static final int GOOD_GENE_START_POSITION = 8;
    private static final int GOOD_GENE_END_POSITION = 50;
    private static final String GOOD_GENE_EYES = "brown";
    private static final String GOOD_GENE_HAIR = "red";
    private static final String GOOD_GENE_TONGUE = "no";
    private static final String GENE_TEXT = "atgaccggcagtctatatgactctgatgccgcaggctgcctc";


    ///////////////////////////////////////////////////////////////////////////
    // End changeable variables
    ///////////////////////////////////////////////////////////////////////////


    private final InputStream originalSysin = System.in;
    private final PrintStream originalSysout = System.out;
    private ByteArrayOutputStream recordingSysout;

    @Rule
    public Timeout globalTimeout = Timeout.seconds(2);

    @Before
    public void setUp() {
        System.setIn(originalSysin);
        System.setOut(originalSysout);
    }

    @After
    public void tearDown() {
        stopRecording(); // just in case we left something recording, clear out stdout
    }


    @Test(timeout=1000l)
    public void testNoInput() {
        setSystemIn("");
        recordOutput();
        Sequencer.main(new String[]{});

        assertEquals(multiline(
                "Input lowercase DNA fragments one line at a time. End with a blank line.",
                "Input DNA: ",
                "DNA does not contain a gene start codon"
                ),
                getRecording());

    }

    @Test(timeout=1000l)
    public void testBadDNA() {
        setSystemIn(BAD_DNA);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyBegins(
                "Make sure your program outputs \"DNA is invalid\" when the DNA is invalid",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "DNA is invalid"
                ),
                getRecording());
    }


    @Test(timeout = 1000l)
    public void testGoodDNA() {
        setSystemIn(GOOD_DNA_ONE_LINE);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyBegins(
                "Make sure your program outputs all lines up to the \"Input DNA:\" line correctly",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "Input DNA: " + GOOD_DNA_ONE_LINE
                ),
                getRecording());
    }


    @Test(timeout = 1000l)
    public void testReadMultiline() {
        setSystemIn(GOOD_DNA_MULTILINE);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyBegins(
                "Make sure your program joins multiple input lines correctly",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "Input DNA: " + GOOD_DNA_MULTILINE_RESULT
                ),
                getRecording());
    }

    @Test(timeout = 1000l)
    public void testFullOverlap() {
        setSystemIn(GOOD_DNA_ONE_LINE, GOOD_DNA_ONE_LINE);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyBegins(
                "Make sure your program joins fully overlapping DNA fragments",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "Input DNA: " + GOOD_DNA_ONE_LINE
                ),
                getRecording());
    }


    @Test(timeout = 1000l)
    public void testNoStartCodon() {
        setSystemIn(NO_START_CODON);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyEquals(
                "Make sure your program stops when it gets DNA with no start codon",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "Input DNA: " + NO_START_CODON,
                        "DNA does not contain a gene start codon"
                ),
                getRecording());
    }

    @Test(timeout = 1000l)
    public void testNoEndCodon() {
        setSystemIn(NO_END_CODON);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyEquals(
                "Make sure your program stops when it gets DNA with no stop codon",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "Input DNA: " + NO_END_CODON,
                        "DNA does not contain a gene end codon"
                ),
                getRecording());
    }


    @Test(timeout = 1000l)
    public void testImproperLocationEndCodon() {
        setSystemIn(WRONG_PLACE_END);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyEquals(
                "Make sure your program stops when it gets DNA with no start codon",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "Input DNA: " + WRONG_PLACE_END,
                        "DNA does not contain a gene end codon"
                ),
                getRecording());
    }

    @Test
    public void testShortGene() {
        final String SHORT_GENE = "atgtag";
        setSystemIn(SHORT_GENE);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyEquals(
                "Make sure your program stops when it gets a gene that is too short",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "Input DNA: " + SHORT_GENE,
                        "Start codon position: 0",
                        "End codon position: 3",
                        "Gene: atg",
                        "The gene is not long enough to continue."
                ),
                getRecording());
    }

    @Test(timeout = 1000l)
    public void testGoodGene() {
        setSystemIn(GOOD_GENE);
        recordOutput();
        Sequencer.main(new String[]{});

        assertFuzzyEquals(
                "Make sure your program stops when it gets DNA with no start codon",
                multiline(
                        "Input lowercase DNA fragments one line at a time. End with a blank line.",
                        "Input DNA: " + GOOD_GENE,
                        "Start codon position: " + GOOD_GENE_START_POSITION,
                        "End codon position: " + GOOD_GENE_END_POSITION,
                        "Gene: " + GENE_TEXT,
                        "",
                        "Analysis Results",
                        "",
                        "Eye color: " + GOOD_GENE_EYES,
                        "Hair color: " + GOOD_GENE_HAIR,
                        "Can roll tongue? " + GOOD_GENE_TONGUE
                ),
                getRecording());
    }



    //////////////////////////////////////////////////////////////////////////////////////////
    // Utility Functions
    //////////////////////////////////////////////////////////////////////////////////////////


    /**
     * Behaves like WebCat's setSystemIn, terminates all lines with a
     * system dependent newline character and replaces System.in
     *
     * @param inputLines
     */
    private void setSystemIn(String... inputLines) {
        byte[] bytes = multiline(inputLines).getBytes();
        ByteArrayInputStream newInput = new ByteArrayInputStream(bytes);
        System.setIn(newInput);
    }

    /**
     * Behaves like WebCat's setSystemIn, terminates all lines with a
     * system dependent newline character and replaces System.in
     *
     * @param inputLines The lines of input, one string per line.
     * @return A string with all lines concatenated and ended with the system newline character.
     */
    private static String multiline(String... inputLines) {
        StringBuilder sb = new StringBuilder();

        for(String line : inputLines) {
            sb.append(line);
            sb.append(System.lineSeparator());
        }

        return sb.toString();
    }

    /**
     * Starts recording the stdout of the application.
     */
    private void recordOutput() {
        recordingSysout = new ByteArrayOutputStream();
        System.setOut(new PrintStream(recordingSysout));
    }

    public void stopRecording() {
        System.setOut(originalSysout);

        if(recordingSysout != null) {
            getRecording();
        }

        recordingSysout = null;
    }

    /**
     * Gets the recording of sysout.
     * @return All the lines put in stdout since calling recordOutput
     */
    private String getRecording() {
        String output = recordingSysout.toString();
        recordingSysout.reset();

        originalSysout.print(output);
        return output;
    }

    /**
     * Does a "fuzzy" equals on two strings. This is comparable to running diff
     * with the -wiB flags. Ignores whitespace differences, case and blank lines.
     *
     * @param description The human readable description if the strings don't compare.
     * @param expected The expected value of the program output
     * @param actual The actual value of the program output
     */
    private void assertFuzzyEquals(String description, String expected, String actual) {
        if(normalize(expected).equals(normalize(actual))) {
            return;
        }

        assertEquals(description, expected, actual);
    }

    /**
     * Does a "fuzzy" startsWith on two strings. This is comparable to running diff
     * with the -wiB flags. Ignores whitespace differences, case and blank lines.
     *
     * @param description The human readable description if the strings don't compare.
     * @param expectedStart The string actual is expected to start with
     * @param actual The actual value of the program output
     */
    private void assertFuzzyBegins(String description, String expectedStart, String actual) {
        if(normalize(actual).startsWith(normalize(expectedStart))) {
            return;
        }

        assertEquals(description, expectedStart, actual);
    }


    private static String normalize(String str) {
        str = str.toLowerCase();
        str = str.replaceAll("\\s+","");
        return str;
    }
}
