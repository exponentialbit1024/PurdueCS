public class RightThread extends Thread {

    public synchronized void run() {
      for(int i = 0; i < 10; i++) {
        System.out.println("Right");
        Thread.yield();
      }
    }
}
