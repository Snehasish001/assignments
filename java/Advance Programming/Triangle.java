import shapes.Shape;

public class Triangle implements Shape{
    float b, h;
    Triangle(float b, float h) {
        this.b = b;
        this.h = h;
    }

    public float getArea() {
        return 0.5f * this.b * this.h;
    }
}
