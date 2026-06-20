import java.util.Scanner;

class StackException extends Exception {
    public StackException(String msg) {
        super(msg);
    }
}

class Stack {
    protected int[] stk;
    protected int top;
    protected int size;

    public Stack(int size) {
        this.size = size;
        stk = new int[size];
        top = -1;
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public boolean isFull() {
        return top == size - 1;
    }

    public void push(int item) throws StackException {
        if (isFull())
            throw new StackException("Stack Overflow");

        stk[++top] = item;
    }

    public int pop() throws StackException {
        if (isEmpty())
            throw new StackException("Stack Underflow");

        return stk[top--];
    }

    public int peek() throws StackException {
        if (isEmpty())
            throw new StackException("Stack Empty");

        return stk[top];
    }

    public void display() {
        if (isEmpty()) {
            System.out.println("Stack Empty");
            return;
        }

        System.out.println("Top -> Bottom");

        for (int i = top; i >= 0; i--)
            System.out.println(stk[i]);
    }
}

class SpecialStack extends Stack {

    public SpecialStack(int size) {
        super(size);
    }

    @Override
    public void push(int item) throws StackException {

        if (isFull())
            throw new StackException("Stack Overflow");

        if (!isEmpty() && item >= stk[top])
            throw new StackException(
                    "Cannot place larger disk on smaller disk");

        stk[++top] = item;
    }
}

public class Tower {

    static SpecialStack t1;
    static SpecialStack t2;
    static SpecialStack t3;
    static int moves = 0;


    static Stack merge(Stack s1, Stack s2) throws StackException {

        Stack temp = new Stack(s1.size + s2.size);
        Stack result = new Stack(s1.size + s2.size);

        while (!s1.isEmpty() && !s2.isEmpty()) {

            if (s1.peek() > s2.peek())
                temp.push(s1.pop());
            else
                temp.push(s2.pop());
        }

        while (!s1.isEmpty())
            temp.push(s1.pop());

        while (!s2.isEmpty())
            temp.push(s2.pop());

        while (!temp.isEmpty())
            result.push(temp.pop());

        return result;
    }



    static int valueAt(SpecialStack s, int index) {
        if (index <= s.top)
            return s.stk[index];

        return 0;
    }

    static void displayTowers() {

        int start =
                Math.max(t1.top,
                        Math.max(t2.top, t3.top));

        System.out.println();

        for (int i = start; i >= 0; i--) {

            System.out.printf(
                    "| %2d |   | %2d |   | %2d |\n",
                    valueAt(t1, i),
                    valueAt(t2, i),
                    valueAt(t3, i));

            System.out.println("--------------------------");
        }

        System.out.println("   A        B        C");
        System.out.println();
    }


    static void hanoi(int disk,
                      SpecialStack source,
                      SpecialStack auxiliary,
                      SpecialStack destination,
                      char s,
                      char a,
                      char d)
            throws StackException {

        if (disk == 1) {

            int item = source.pop();
            destination.push(item);

            moves++;

            System.out.println(
                    "Move Disk " + item +
                    " from " + s +
                    " to " + d);

            displayTowers();
            return;
        }

        hanoi(disk - 1,
                source,
                destination,
                auxiliary,
                s, d, a);

        int item = source.pop();
        destination.push(item);

        moves++;

        System.out.println(
                "Move Disk " + item +
                " from " + s +
                " to " + d);

        displayTowers();

        hanoi(disk - 1,
                auxiliary,
                source,
                destination,
                a, s, d);
    }


    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int choice;

        do {

            System.out.println("\n===== ASSIGNMENT 3 =====");
            System.out.println("1. Merge Two Sorted Stacks");
            System.out.println("2. Tower Of Hanoi");
            System.out.println("3. Exit");
            System.out.print("Enter Choice : ");

            choice = sc.nextInt();

            switch (choice) {

                case 1:

                    try {

                        System.out.print("Size of Stack 1 : ");
                        int n1 = sc.nextInt();

                        Stack s1 = new Stack(n1);

                        System.out.println(
                                "Enter elements in ascending order:");

                        for (int i = 0; i < n1; i++)
                            s1.push(sc.nextInt());

                        System.out.print("Size of Stack 2 : ");
                        int n2 = sc.nextInt();

                        Stack s2 = new Stack(n2);

                        System.out.println(
                                "Enter elements in ascending order:");

                        for (int i = 0; i < n2; i++)
                            s2.push(sc.nextInt());

                        Stack merged = merge(s1, s2);

                        System.out.println(
                                "\nMerged Stack:");

                        merged.display();

                    } catch (StackException e) {
                        System.out.println(e.getMessage());
                    }

                    break;

                case 2:

                    try {

                        System.out.print(
                                "Enter number of disks : ");

                        int disk = sc.nextInt();

                        t1 = new SpecialStack(disk);
                        t2 = new SpecialStack(disk);
                        t3 = new SpecialStack(disk);

                        for (int i = disk; i >= 1; i--)
                            t1.push(i);

                        moves = 0;

                        System.out.println(
                                "\nInitial Towers:");

                        displayTowers();

                        hanoi(disk,
                                t1,
                                t2,
                                t3,
                                'A',
                                'B',
                                'C');

                        System.out.println(
                                "Total Moves = " + moves);

                        System.out.println(
                                "Calculated Moves = "
                                + ((int)Math.pow(2, disk) - 1));

                    } catch (StackException e) {
                        System.out.println(e.getMessage());
                    }

                    break;

                case 3:
                    System.out.println("Program Ended.");
                    break;

                default:
                    System.out.println("Invalid Choice");

            }

        } while (choice != 3);

        sc.close();
    }
}