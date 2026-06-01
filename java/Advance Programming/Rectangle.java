import shapes.Shape;
public class Rectangle implements Shape{
    float l, b;
    Rectangle(float l, float b) {
        this.l = l;
        this.b = b;
    }

    public float getArea() {
        return this.l * this.b;
    }
}
