public class Merge{
  private static int merge(int[] a, int[] aux, int lo, int mid, int hi){
    int inversions = 0;
    for (int k = lo; k <= hi; k++){
      aux[k] = a[k];
    }
    int i = lo, j = mid+1;
    for (int k = lo; k <= hi; k++){
      if(i > mid){
        a[k] = aux[j++];
      }
      else if(j > hi){
        a[k] = aux[i++];
      }
      else if (aux[j] < aux[i]){
        a[k] = aux[j++];
        inversions += (mid - i + 1);
      }
      else{
        a[k] = aux[i++];
      }
    }
    return inversions;
  }
}
