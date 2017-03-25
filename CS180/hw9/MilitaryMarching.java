public class MilitaryMarching {
    public static void main(String[] args) {
        Thread lt = new LeftThread();
        Thread rt = new RightThread();
        lt.start();
        rt.start();
        try {
          lt.join();
          rt.join();
        } catch(InterruptedException e) {
            e.printStackTrace();
        }
    }
}
