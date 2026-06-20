public class Dog implements Animals{
    @Override
    public void sound() {
        System.out.println("Dog Barks");
    }

    public static void main(String[] args) {
        Animals d = new Dog();
        d.sound();
    }
}
