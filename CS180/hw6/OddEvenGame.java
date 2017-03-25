public class OddEvenGame{
  private int oddsum;
  private int evensum;
  private static int totalOddSum;
  private static int totalEvenSum;

  public void addEven(int[] array){
    for(int i = 0; i < array.length; i++){
      if(array[i] % 2 == 0){
        this.totalEvenSum += array[i];
      }
    }
  }

  public void addOdd(int[] array){
    for(int i = 0; i < array.length; i++){
      if(array[i] % 2 != 0){
        this.totalEvenSum += array[i];
      }
    }
  }

  public int getOddSum(){
    return this.oddsum;
  }

  public int getEvenSum(){
    return this.evensum;
  }

  public int getTotalOddSum(){
    return this.totalOddSum;
  }

  public int getTotalEvenSum(){
    return this.totalEvenSum;
  }
}
