import java.io.*;
import java.util.ArrayList;
import java.util.Random;

public class Fibonacci implements Serializable {

    private ArrayList<Integer> fibo;

    Fibonacci() {
        fibo = new ArrayList<>();
    }

    ArrayList<Integer> getFiboList(int terms) {

        if (terms == 0) return fibo;

        fibo.add(0);

        if (terms == 1) return fibo;

        fibo.add(1);

        for (int i = 2; i < terms; i++) {
            fibo.add(fibo.get(i - 1) + fibo.get(i - 2));
        }

        return fibo;
    }

    public String toString() {
        return fibo.toString();
    }

    public static void main(String[] args)
            throws IOException, ClassNotFoundException {

        Random r = new Random();
        Fibonacci f = new Fibonacci();
        f.getFiboList(r.nextInt(1, 50));

        ObjectOutputStream out =
            new ObjectOutputStream(
                new FileOutputStream("fibo.dat"));

        out.writeObject(f);
        out.close();

        ObjectInputStream in =
            new ObjectInputStream(
                new FileInputStream("fibo.dat"));

        Fibonacci obj = (Fibonacci) in.readObject();
        in.close();

        System.out.println(obj);
    }
}