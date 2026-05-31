import java.util.Random;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        Random random = new Random();
        InnerStack stack = new InnerStack(10);
        Scanner scanner = new Scanner(System.in);


        int choice = 0;
        boolean f = true;
        do {
            System.out.print("Press\n1. push\n2. pop\n3. peek\n4. display\n5. exit\n>>> ");
            choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    try {
                        stack.push(random.nextInt(10,99));
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    stack.display();
                    break;

                case 2:
                    try {
                        System.out.println(stack.pop());
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    stack.display();
                    break;

                case 3:
                    try {
                        System.out.println(stack.peek());
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    stack.display();
                    break;

                case 4:
                    stack.display();
                    break;

                case 5:
                    f = false;
                    break;
            
                default:
                    System.out.println("Wrong input.");
                    break;
            }
        } while (f);

        scanner.close();
    }
}
