import java.util.Scanner;

class MyStack {
    private int[] stack;
    private int top;
    private int size;

    public MyStack(int size) {
        this.size = size;
        stack = new int[size];
        top = -1;
    }


    public void push(int value) {
        if (top == size - 1) {
            System.out.println("Stack Overflow!");
            return;
        }
        stack[++top] = value;
        System.out.println(value + " pushed into stack.");
    }

    public void pop() {
        if (top == -1) {
            System.out.println("Stack Underflow!");
            return;
        }

        System.out.println("Popped Element: " + stack[top--]);
    }

    public void peek() {
        if (top == -1) {
            System.out.println("Stack is Empty!");
            return;
        }

        System.out.println("Top Element: " + stack[top]);
    }


    public void display() {
        if (top == -1) {
            System.out.println("Stack is Empty!");
            return;
        }

        System.out.println("\nStack Contents (Top to Bottom):");
        for (int i = top; i >= 0; i--) {
            System.out.println(stack[i]);
        }
    }

    public void display(int depth) {
        if (top == -1) {
            System.out.println("Stack is Empty!");
            return;
        }

        if (depth < 0 || depth > top) {
            System.out.println("Invalid Depth!");
            return;
        }

        System.out.println("Element at Depth " + depth +
                           " : " + stack[top - depth]);
    }
}

public class Stack{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter Stack Size: ");
        int size = sc.nextInt();

        MyStack stack = new MyStack(size);

        int choice;

        do {
            System.out.println("\n===== STACK MENU =====");
            System.out.println("1. Push");
            System.out.println("2. Pop");
            System.out.println("3. Peek");
            System.out.println("4. Display Entire Stack");
            System.out.println("5. Display Element at Given Depth");
            System.out.println("6. Exit");
            System.out.print("Enter Choice: ");

            choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter Element: ");
                    int value = sc.nextInt();
                    stack.push(value);
                    break;

                case 2:
                    stack.pop();
                    break;

                case 3:
                    stack.peek();
                    break;

                case 4:
                    stack.display();
                    break;

                case 5:
                    System.out.print("Enter Depth: ");
                    int depth = sc.nextInt();
                    stack.display(depth);
                    break;

                case 6:
                    System.out.println("Exiting...");
                    break;

                default:
                    System.out.println("Invalid Choice!");
            }

        } while (choice != 6);

        sc.close();
    }
}