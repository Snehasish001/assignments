import java.util.Scanner;
class StackException extends Exception{
    StackException(String message) {
        super(message);
    }
}

public class Stack{
    private int[] stk;
    private int top;

    Stack(int size) {
        this.stk = new int[size];
        this.top = -1;
    }

    private boolean isEmpty() {
        return this.top == -1;
    }

    private boolean isFull() {
        return this.top == this.stk.length - 1;
    }

    void display() {
        if (this.isEmpty()) {
            System.out.println("Stack is Empty.");
            return;
        }

        System.out.println();
        for (int i = this.top; i >= 0; i--) {
            System.out.println("| "+this.stk[i]+" |\n------");
        }
    }

    void display(int index) throws StackException {
        if (index >= 0 && index <= this.top) {
            System.out.println(index+"th element : "+this.stk[index]);
        } else {
            throw new StackException("IndexOutOfBound");
        }
    }

    void push(int element) throws StackException {
        if (this.isFull()) {
            throw new StackException("Overflow.");
        }
        this.top++;
        this.stk[this.top] = element;
    }
    
    int pop() throws StackException {
        if (this.isEmpty()) {
            throw new StackException("Underflow.");
        }
        int item = this.stk[this.top];
        this.stk[this.top] = 0;
        this.top--;
        return item;
    }

    int peek() throws StackException {
        if (this.isEmpty()) {
            throw new StackException("Underflow.");
        }
        return this.stk[this.top];
    }

    private void presort() {
        for(int i = 0; i < this.top; i++) {
            int min = i;

            for (int j = i + 1; j <= this.top; j++) {
                if (this.stk[min] > this.stk[j]) {
                    min = j;
                }
            }

            int temp = this.stk[min];
            this.stk[min] = this.stk[i];
            this.stk[i] = temp;
        }
    }

    void merge(Stack s) throws StackException{
        int total = (this.top + 1) + (s.top + 1);

        if (total > this.stk.length) {
            throw new StackException("Overflow.");
        }

        for (int i = 0; i <= s.top; i++) {
            this.push(s.stk[i]);
        }

        this.presort();
    }

    public static void main(String[] args) {
        boolean flag = true;
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the size : ");
        int n = sc.nextInt();
        Stack s1 = new Stack(n);

        while (flag) {
            int choice = 0;
            System.out.print("\nPress\n1. push\n2. pop\n3. peek\n4. display (whole)\n5. display (index)\n6. merge\n7. exit\n>>> ");
            choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter the element : ");
                    int item = sc.nextInt();
                    try {
                        s1.push(item);
                        s1.display();
                        System.out.println(item+" pushed successfully.");
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case 2:
                    try {
                        System.out.println("Popped : "+s1.pop());
                        s1.display();
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case 3:
                    try {
                        System.out.println("Top element : "+s1.peek());
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    break;
                case 4:
                    s1.display();
                    break;
                case 5:
                    System.out.print("Enter the index : ");
                    int index = sc.nextInt();
                    try {
                        s1.display(index);
                    } catch(Exception e) {
                        System.out.println(e);
                    }
                    break;
                case 6:
                    System.err.print("Enter the size : ");
                    int size = sc.nextInt();
                    Stack s2 = new Stack(size);
                    for (int i = 0; i < size; i++) {
                        System.out.print("Enter the "+(i + 1)+"th element : ");
                        try {
                            s2.push(sc.nextInt());
                        } catch (Exception e) {
                            System.out.println(e);
                        }
                    }
                    try {   
                        s1.merge(s2);
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    s1.display();
                    break;
                case 7: 
                    flag = false;
                    break;
                default:
                    System.out.println("Wrong choice");
                    break;
            }
        }

        sc.close();
    }
}
