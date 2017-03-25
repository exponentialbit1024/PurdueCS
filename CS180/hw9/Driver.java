public class Driver{
  public static void main(String[] args){
    Thread t = new A();
    t.start();
    Runnable r = new B();
    Thread t2 = new Thread(r);
    t2.start();
  }
}
