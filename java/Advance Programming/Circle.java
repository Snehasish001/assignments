import shapes.Shape;

public class Circle implements Shape{
    float r;
    static float PI = 3.14f;
    Circle(float r) {
        this.r = r;
    }

    public float getArea() {
        return PI * 2 * r; 
    }
}
