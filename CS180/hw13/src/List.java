/**
 * Created by sidshah on 4/28/17.
 */
public class List<T extends Comparable> {
    private Node<T> start;
    private int numElements;

    public List(){
        this.start = null;
        this.numElements = 0;
    }

    public int getNumElements(){
        return this.numElements;
    }

    @Override
    public String toString(){
        Node<T> pointer = start;
        String builder = "";
        for(int i = 0; i < getNumElements() - 1;i++){
            builder += pointer.getValue() + "->";
            pointer = pointer.getNext();
        }
        builder += pointer.getNext().getValue();
        return builder;
    }

    public boolean addAfter(int index, T value){
        Node<T> pointer = new Node<T>(start.getValue());
        for(int i = 0; i < index; i++){
            if(pointer == null){
                return false;
            }
            pointer = pointer.getNext();
        }
        pointer.setNext(new Node<T>(value));
        this.numElements++;
        return true;
    }

    public void addFront(T value){
        Node<T> newStart = new Node<T>(value);
        newStart.setNext(this.start);
        this.start = newStart;
    }

    public boolean addEnd(T value){
        Node<T> pointer = start;
        for(int i = 0; i < getNumElements(); i++){
            pointer = pointer.getNext();
        }
        pointer.setNext(new Node<T>(value));
        this.numElements++;
        return true;
    }

    public boolean deleteNode(T value){
        Node<T> pointer = start;
        if(pointer.getValue() == value){
            this.start = pointer.getNext();
            pointer.setNext(null);
            this.numElements--;
            return true;
        }
        Node<T> prevPointer = pointer;
        pointer = pointer.getNext();
        for(int i = 1; i < getNumElements(); i++){
            if(pointer.getValue() == value){
                prevPointer.setNext(pointer.getNext());
                this.numElements--;
                return true;
            }
        }
        return false;
    }

    public int insertInPlace(T value){

    }

    public static void main(String[] args){
        List<Integer> testList = new List<>();
    }
}
