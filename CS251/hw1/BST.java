public class BST{

  private static int[] a = {1,2,3,4,5,6,7,8,9,10};
  private static int[] b = {11,12,13,14,15,16,17,18,19,20};

  public static int kthLargest(int start1, int end1, int start2, int end2, int k){
    int mida1 = (end1 - start1) / 2;
    int mida2 = (end2 - start2) / 2;
    if(mida1 + mida2 < k){
      if(a[mida1] > b[mida2]){
        return kthLargest(0, a.length, mida2 + 1, b.length, k - mida2 - 1);
      }
      else{
        return kthLargest(mida1 + 1, a.length, 0, b.length, k - mida1 - 1);
      }
    }
    else{
      if(a[mida1] > b[mida2]){
        return kthLargest(0, mida1, 0, b.length, k);
      }
      else{
        return kthLargest(0, a.length, 0, mida2, k);
      }
    }
  }

  public static void main(String[] args){
    System.out.println(kthLargest(0, a.length, 0, this.ar2.length, 13));
  }
}
