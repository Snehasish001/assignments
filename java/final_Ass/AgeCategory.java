import java.time.LocalDate;
import java.time.Period;
import java.util.Scanner;

class Person {
    private String name;
    private LocalDate dob;
    private int age;


    Person(String name, LocalDate dob) {
        this.name = name;
        this.dob = dob;
        this.age = calculateAge();
    }

    private int calculateAge() {
        LocalDate today = LocalDate.now();
        return Period.between(dob, today).getYears();
    }

    public String getAgeCategory() {
        if (age < 18)
            return "Under Age";
        else if (age >= 18 && age < 30)
            return "Young Adult";
        else if (age >= 30 && age < 45)
            return "Matured Adult";
        else if (age >= 45 && age < 60)
            return "Middle Aged";
        else
            return "Senior Citizen";
    }

    public String toString() {
        return "\nName : "+name+"\nDOB : "+dob+"\nAge : "+age+"\nCategory : "+getAgeCategory();
    }
}

public class AgeCategory {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter Name: ");
        String name = sc.nextLine();

        System.out.print("Enter Birth Year (yyyy): ");
        int year = sc.nextInt();

        System.out.print("Enter Birth Month (mm): ");
        int month = sc.nextInt();

        System.out.print("Enter Birth Day (dd): ");
        int day = sc.nextInt();

        LocalDate dob = LocalDate.of(year, month, day);

        Person p = new Person(name, dob);
        System.out.println(p);

        sc.close();
    }
}