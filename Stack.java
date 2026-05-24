class StackException extends Exception{
    public StackException(String msg) {
        super(msg);
    }
}

public interface Stack {
    void push(int item) throws StackException;
    int  pop() throws StackException;
    boolean isEmpty();
    boolean isFull();
    int peek() throws StackException;
}