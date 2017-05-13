/**
 * Created by sidshah on 4/28/17.
 */
public class Node<T extends Comparable> {
    private T value;
    private Node<T> next;

    public Node(T value, Node<T> next){
        this.value = value;
        this.next = next;
    }

    public Node(T value){
        this.value = value;
    }

    public T getValue(){
        return this.value;
    }

    public Node<T> getNext(){
        return this.next;
    }

    public void setValue(T value){
        this.value = value;
    }

    public void setNext(Node<T> next){
        this.next = next;
    }
}
