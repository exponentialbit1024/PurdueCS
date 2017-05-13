/**
 * Created by sidshah on 3/31/17.
 */
public class MyQueue extends Object{
    private Node head;
    private int count = 0;

    public MyQueue(){}

    public void add(Object o){
        this.count++;
        if(this.head == null){
            this.head = new Node(o);
        }else{
            Node tNode = this.head;
            while(tNode.getNext() != null){
                tNode = tNode.getNext();
            }
            tNode.setNext(new Node(o));
        }
    }

    public boolean isEmpty(){
        return count == 0;
    }

    public Node peek(){
        return this.head;
    }

    public Node remove(){
        if(this.count > 0){
            this.count--;
            Node tNode = this.head;
            if(tNode != null){
                this.head = this.head.getNext();
                return tNode;
            }
        }
        return null;
    }

    public int size(){
        return this.count;
    }

    public static void main(String[] args){
        MyQueue mq = new MyQueue();
        for(int i = 0 ; i < 10; i++)
            mq.add(new Integer(i));

        /* Remove 5 then recheck */
        for(int i = 0; i < 5; i++)
            mq.remove();

        System.out.println(mq.peek().getData());
    }
}
