interface ResizableTray {

    void W(int width);

    void L(int length);
}

class Tray implements ResizableTray {

    protected int width;
    protected int length;
    protected int plateCount;

    public Tray(int width, int length, int plateCount) {
        this.width = width;
        this.length = length;
        this.plateCount = plateCount;
    }

    @Override
    public void W(int width) {
        this.width = width;
    }

    @Override
    public void L(int length) {
        this.length = length;
    }

    public void displayTray() {
        System.out.println("\nTray Details");
        System.out.println("Width = " + width);
        System.out.println("Length = " + length);
        System.out.println("Number of Plates = " + plateCount);
    }
}

interface ResizableBox extends ResizableTray {

    void D(int depth);
}

public class NewBox implements ResizableBox {

    private int width;
    private int length;
    private int depth;
    private int ballCount;

    public NewBox(int width,
                  int length,
                  int depth,
                  int ballCount) {

        this.width = width;
        this.length = length;
        this.depth = depth;
        this.ballCount = ballCount;
    }

    @Override
    public void W(int width) {
        this.width = width;
    }

    @Override
    public void L(int length) {
        this.length = length;
    }

    @Override
    public void D(int depth) {
        this.depth = depth;
    }

    public void displayBox() {
        System.out.println("\nBox Details");
        System.out.println("Width = " + width);
        System.out.println("Length = " + length);
        System.out.println("Depth = " + depth);
        System.out.println("Number of Balls = " + ballCount);
    }

    public static void main(String[] args) {

        Tray tray = new Tray(20, 30, 12);

        tray.displayTray();

        tray.W(25);
        tray.L(35);

        System.out.println("\nAfter Resizing Tray:");
        tray.displayTray();

        // Box Object
        NewBox box = new NewBox(10, 15, 20, 50);

        box.displayBox();

        box.W(12);
        box.L(18);
        box.D(25);

        System.out.println("\nAfter Resizing Box:");
        box.displayBox();
    }
}