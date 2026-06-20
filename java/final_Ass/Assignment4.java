import java.util.Scanner;

/* Custom Exception */
class InvalidDataException extends Exception {
    public InvalidDataException(String msg) {
        super(msg);
    }
}

/* Base Class */
class EMP {
    protected int id;
    protected int depCode;

    public EMP(int id, int depCode)
            throws InvalidDataException {

        if (id <= 0)
            throw new InvalidDataException(
                    "Employee ID must be positive");

        if (depCode < 0 || depCode > 5)
            throw new InvalidDataException(
                    "Department Code must be between 0 and 5");

        this.id = id;
        this.depCode = depCode;
    }

    public void display() {
        System.out.println("Employee ID : " + id);
        System.out.println("Department Code : " + depCode);
    }
}

/* Derived Class */
class GradedEmp extends EMP {

    private char grade;

    public GradedEmp(int id,
                     int depCode,
                     char grade)
            throws InvalidDataException {

        /* Change depCode 0 -> 10 */
        super(id, depCode == 0 ? 10 : depCode);

        grade = Character.toUpperCase(grade);

        if (grade < 'A' || grade > 'E')
            throw new InvalidDataException(
                    "Grade must be between A and E");

        this.grade = grade;
    }

    @Override
    public void display() {

        super.display();

        System.out.println("Grade : " + grade);
    }
}

public class Assignment4 {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        try {

            System.out.print("Enter Employee ID : ");
            int id = sc.nextInt();

            System.out.print(
                    "Enter Department Code (0-5) : ");
            int dep = sc.nextInt();

            System.out.print(
                    "Enter Grade (A-E) : ");
            char grade = sc.next().charAt(0);

            GradedEmp emp =
                    new GradedEmp(id, dep, grade);

            System.out.println("\nEmployee Details");
            System.out.println("----------------");

            emp.display();

        } catch (InvalidDataException e) {

            System.out.println(
                    "Exception : " + e.getMessage());

        } catch (Exception e) {

            System.out.println(
                    "Invalid Input");

        }

        sc.close();
    }
}