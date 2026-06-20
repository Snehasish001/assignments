import java.io.*;
import java.util.*;

public class FibonacciFile {

    public static void main(String[] args) {

        try {


            FileWriter fw = new FileWriter("Fibo.txt");

            int a = 0, b = 1;

            for (int i = 1; i <= 10; i++) {
                fw.write(a + " ");
                int c = a + b;
                a = b;
                b = c;
            }

            fw.close();

            System.out.println("First 10 Fibonacci numbers written to Fibo.txt");


            Scanner sc = new Scanner(new FileReader("Fibo.txt"));

            ArrayList<Integer> fibo = new ArrayList<>();

            while (sc.hasNextInt()) {
                fibo.add(sc.nextInt());
            }

            sc.close();

            System.out.println("\nContents of Fibo.txt: "+fibo);

            FileWriter appendWriter = new FileWriter("Fibo.txt", true);

            int n1 = fibo.get(fibo.size() - 2);
            int n2 = fibo.get(fibo.size() - 1);

            int next = n1 + n2;
            while (next < 250) {
                appendWriter.write(next + " ");
                n1 = n2;
                n2 = next;
                next = n1 + n2;
            }

            appendWriter.close();

            System.out.println("\nNumbers appended successfully.");


            Scanner sc2 = new Scanner(new FileReader("Fibo.txt"));

            FileOutputStream fos = new FileOutputStream("Fibo.bin");

            while (sc2.hasNextInt()) {
                int num = sc2.nextInt();
                fos.write(num);
            }

            sc2.close();
            fos.close();

            System.out.println("Binary file Fibo.bin created.");
        }

        catch (IOException e) {
            System.out.println(e);
        }
    }
}