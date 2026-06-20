import java.io.*;
import java.util.ArrayList;
import java.util.Random;

public class Profile implements Serializable {

    private String name;
    private int age;
    private float avgMarks;

    public Profile() {
        name = "";
        age = 0;
        avgMarks = 0;
    }

    public Profile(String name, int age, float avgMarks) {
        this.name = name;
        this.age = age;

        this.avgMarks = Math.round(avgMarks * 100) / 100.0f;
    }

    public float getAvgMarks() {
        return avgMarks;
    }

    @Override
    public String toString() {
        return String.format(
                "Name : %-20s Age : %2d  Average Marks : %.2f",
                name, age, avgMarks
        );
    }

    public static void main(String[] args) {

        String[] names = {
                "Ram", "Laxman", "Krishna",
                "Radha", "Sita", "Arjun",
                "Nakul", "Bhim", "Ajoy"
        };

        String[] titles = {
                "Sarkar", "Roy", "Chatterjee",
                "Ghosh", "Barman", "Mondal",
                "Banerjee"
        };

        ArrayList<Profile> profiles = new ArrayList<>();
        Random r = new Random();

        int n = r.nextInt(5, 15);

        System.out.println("Number of Profiles = " + n);

        for (int i = 0; i < n; i++) {

            String fullName = names[r.nextInt(names.length)]+ " "+ titles[r.nextInt(titles.length)];
            int age = r.nextInt(18, 26);
            float marks = r.nextFloat() * 100;

            profiles.add(new Profile(fullName, age, marks));
        }

        try {

            ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("Profile.bin"));

            for (Profile p : profiles) {
                oos.writeObject(p);
            }

            oos.close();

            System.out.println("\nProfiles successfully stored in Profile.bin");

            ObjectInputStream ois = new ObjectInputStream( new FileInputStream("Profile.bin"));

            Profile highestScorer = null;

            System.out.println("\nAll Profiles");
            System.out.println("----------------------------------------------------------");

            try {
                while (true) {
                    Profile p = (Profile) ois.readObject();
                    System.out.println(p);
                    if (highestScorer == null || p.getAvgMarks() > highestScorer.getAvgMarks()) {
                        highestScorer = p;
                    }
                }

            } catch (EOFException e) {

            }

            ois.close();

            System.out.println("\nHighest Scorer");
            System.out.println("----------------------------------------------------------");
            System.out.println(highestScorer);

        } catch (IOException | ClassNotFoundException e) {

            System.out.println("Error : " + e.getMessage());
        }
    }
}