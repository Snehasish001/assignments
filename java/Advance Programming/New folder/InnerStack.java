
public class InnerStack implements Stack{
    int[] stk;
    int top;

    public InnerStack(int size) {
        this.stk = new int[size];
        this.top = -1;
    }

    @Override
    public void push(int item) throws StackException{
        if (this.isFull())  throw new StackException("Overflow");
        this.top++;
        this.stk[this.top] = item;
    }

    @Override
    public int  pop() throws StackException{
        if (this.isEmpty()) throw new StackException("Underflow");
        int item = this.stk[this.top];
        this.stk[this.top] = 0;
        this.top--;
        return item;
    }

    @Override
    public boolean isEmpty() {
        return this.top < 0;
    }

    @Override
    public boolean isFull() {
        return (this.top + 1) == this.stk.length;
    }

    @Override
    public int peek() throws StackException{
        if (this.isEmpty()) throw new StackException("Underflow");
        return this.stk[this.top];
    }

    void display() {
        if (this.top == -1) System.out.println("Stack is Empty.");
        for (int i = this.top; i >= 0; i--) {
            System.out.println("| "+this.stk[i]+" |\n------");
        }
    }
}