class Date{
    int d, m, y;
    Date() {
        this.d = 0;
        this.m = 0;
        this.y = 0;
    }
    Date(int d, int m, int y) {
        if (d > 0 && d < 32 && m > 0 && m < 13 && y > 0) {
            this.d = d;
            this.m = m;
            this.y = y;
        }
    }
    String display() {
        String ans = "%d/%d/%d";
        return String.format(ans, y,m,d);
    }
}

class Person {
    final Date today = new Date(11, 5, 2026);
    private String name;
    private Date dob;
    Person() {
        this.name = "";
    }
    Person(String name, Date dob) {
        this.name = name;
        this.dob = dob;
    }

    Date age(Date dob) {
        int d = today.d - dob.d;
        int m = today.m - dob.m;
        int y = today.y - dob.y;
        int days = d + m * 30 + y * 365;
        Date ans = new Date();
        ans.y = days / 365;
        days = days % 365;
        ans.m = days / 30;
        days = days % 30;
        ans.d = days;
        return ans;
    }

    String category() {
        int age = this.age(this.dob).y; 
        if (age < 18) {
            return "Under Age";
        } else if (age > 18 && age < 30) {
            return "Young Adult";
        } else if (age > 30 && age < 45) {
            return "Matured Adult";
        } else if (age > 45 && age < 60) {
            return "Middle Aged";
        } else {
            return "Buddha";
        }
    }

    void display() {
        System.out.println("Name          : "+ this.name);
        System.out.println("Date of Birth : "+dob.display());
        System.out.println("Age           : "+this.age(dob).display());
        System.out.println("Category      : "+this.category());
    }

    public static void main(String[] args) {
        Person p = new Person("Rakesh", new Date(15, 8, 1947));
        p.display();
    }
}