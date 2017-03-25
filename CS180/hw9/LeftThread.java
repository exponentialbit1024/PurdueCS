public class LeftThread extends Thread {

    public void run() {
      for(int i = 0; i < 10; i++) {
        System.out.println("Left");
        System.out.println("Left");
        Thread.yield();
        System.out.println("Left");
      }
    }
}
