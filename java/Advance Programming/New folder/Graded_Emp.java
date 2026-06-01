import java.util.Random;

public class Graded_Emp extends Emp {
    char grade;
    int dep_code;

    private char gradeRange(int total) {
        if (total > 90 && total < 100) return 'A';
        else if (total > 80) return 'B';
        else if (total > 70) return 'C';
        else if (total > 60) return 'D';
        else if (total > 50) return 'E';
        else return 'F';
    }
    
    private char calculateGrade(int[] marks) {
        int sum = 0;
        for (int i = 0; i < marks.length; i++) {
            sum += marks[i];
        }
        return gradeRange(sum / 5);
    }

    Graded_Emp(int id, int dep_code, int[] marks) {
        super(id, dep_code);
        if (dep_code > 5 && dep_code <= 10) {
            this.dep_code = dep_code;
            super.dep_code = -1;
        } else {
            this.dep_code = -1;
        }
        this.grade = this.calculateGrade(marks);
    }

    void display() {
        if (super.dep_code != -1) {
            System.out.println("Id       : "+super.id+"\nGrade    : "+this.grade+"\nDep_code : "+super.dep_code);
        } else {
            System.out.println("Id       : "+super.id+"\nGrade    : "+this.grade+"\nDep_code : "+this.dep_code);
        }
        System.out.println("\t");
    }

    static void validator(int id, int dep_code, int[] marks) throws Exception {
        if (id < 0) throw new Exception("id must be positive");
        if (dep_code > 10 || dep_code < 0) throw new Exception("dep_code must be in range 0-10");
        for (int i = 0; i < marks.length; i++) {
            if (marks[i] > 100 || marks[i] < 0) throw new Exception("marks must be in range 0-100");
        }
    }

    public static void main(String[] args) {
        Random r = new Random();
        int id, dep_code;
        int[] marks = new int[5];
        for (int i = 0; i < 30; i++) {
            id = r.nextInt(-2, 100);
            dep_code = r.nextInt(-1, 12);
            for (int j = 0; j < marks.length; j++) {
                marks[j] = r.nextInt(-10, 110);
            }
            try {
                validator(id, dep_code, marks);
                Graded_Emp emp = new Graded_Emp(id, dep_code, marks);
                emp.display();
            } catch(Exception e) {
                System.out.println(e+"\t");
            }
        }

    }
}
