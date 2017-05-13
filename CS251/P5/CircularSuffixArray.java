public class CircularSuffixArray {

    private static final int CUTOFF = 8;

    private int[] index;

    // circular suffix array of s
     public CircularSuffixArray(String s) {
        index = new int[s.length()];
        for (int i = 0; i < s.length(); i++)
            index[i] = i;
        sort(s, 0, s.length() - 1, 0);
    }

     public int length() { // length of s
         return index.length;
     }

     public int index(int i) { // returns index of ith sorted suffix
         return index[i];
     }

    private int charAt(String s, int suffix, int offset) {
        if (suffix + offset >= 2 * s.length()) return (char) -1;
        return s.charAt((suffix + offset) % s.length());
    }

    // 3-way String Quicksort circular suffixes of string s from lo to hi
    // starting at index offset. Code adapted from
    // http://algs4.cs.princeton.edu/51radix/Quick3string.java.html
    private void sort(String s, int lo, int hi, int offset) {
        if (hi - lo <= CUTOFF) {
            insertion(s, lo, hi, offset);
            return;
        }
        int lt = lo, gt = hi, piv = charAt(s, index[lo], offset), eq = lo + 1;
        while (eq <= gt) {
            int t = charAt(s, index[eq], offset);
            if      (t < piv) exch(lt++, eq++);
            else if (t > piv) exch(eq, gt--);
            else              eq++;
        }
        sort(s, lo, lt - 1, offset);
        if (piv >= 0)
            sort(s, lt, gt, offset + 1);
        sort(s, gt + 1, hi, offset);
    }

    private void exch(int i, int j) {
        int tmp = index[i];
        index[i] = index[j];
        index[j] = tmp;
    }

    // Insertion sort starting at index offset. Code adapted from
    // http://algs4.cs.princeton.edu/51radix/Quick3string.java.html
    private void insertion(String s, int lo, int hi, int offset) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(s, j, j - 1, offset); j--)
                exch(j, j - 1);
    }

    // Is suffix i less than suffix j, starting at offset
    private boolean less(String s, int i, int j, int offset) {
        int oi = index[i], oj = index[j];
        for (; offset < index.length; offset++) {
            int ival = charAt(s, oi, offset), jval = charAt(s, oj, offset);
            if (ival < jval)
                return true;
            else if (ival > jval)
                return false;
        }
        return false;
    }

    public static void main(String[] args) {

    }

}
