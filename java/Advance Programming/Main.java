

public class Main {
    public static void main(String[] args) {
        Triangle t = new Triangle(10.0f, 20.0f);
        Circle c = new Circle(5f);
        Rectangle r = new Rectangle(12.0f, 13.0f);

        System.out.println("Area triangle   : "+t.getArea());
        System.out.println("Area circle     : "+c.getArea());
        System.out.println("Area rectangle  : "+r.getArea());
    }
}
