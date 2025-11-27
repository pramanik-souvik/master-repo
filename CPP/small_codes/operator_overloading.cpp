#include <iostream>
using namespace std;

class Point {
public:
    int x, y;

    Point(int a = 0, int b = 0) : x(a), y(b) {}

    // Overload +
    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    // Overload -
    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    // Overload * (scalar multiplication)
    Point operator*(int scalar) const {
        return Point(x * scalar, y * scalar);
    }

    // Overload == and !=
    bool operator==(const Point& p) const {
        return (x == p.x && y == p.y);
    }
    bool operator!=(const Point& p) const {
        return !(*this == p);
    }

    // Friend function for output stream (cout << point)
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p1(1, 2), p2(3, 4);

    Point p3 = p1 + p2;
    Point p4 = p2 - p1;
    Point p5 = p1 * 3;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p3 (p1 + p2) = " << p3 << endl;
    cout << "p4 (p2 - p1) = " << p4 << endl;
    cout << "p5 (p1 * 3) = " << p5 << endl;

    cout << boolalpha; // print true/false instead of 1/0
    cout << "p1 == p2? " << (p1 == p2) << endl;
    cout << "p1 != p2? " << (p1 != p2) << endl;

    return 0;
}