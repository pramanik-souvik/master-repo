interface Drawable {
    void draw();
}

class Shape {
    String color;

    Shape(String color) {
        this.color = color;
    }

    void showColor() {
        System.out.println("Shape color: " + color);
    }
}

class Circle extends Shape implements Drawable {
    double radius;

    Circle(String color, double radius) {
        super(color);
        this.radius = radius;
    }

    @Override
    public void draw() {
        System.out.println("Drawing a circle with radius " + radius);
    }

    void area() {
        System.out.println("Circle area: " + (3.1415 * radius * radius));
    }
}

public class InheritanceInterfaces {
    public static void main(String[] args) {
        Circle c = new Circle("Red", 5);
        c.showColor();
        c.draw();
        c.area();
    }
}
