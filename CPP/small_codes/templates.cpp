#include <iostream>
#include <string>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << "Given Integer : " << endl;
    cout << 3 << ", " << 4 << endl << endl;

    cout << "Given Double : " << endl;
    cout << 2.5 << ", " << 3.5 << endl << endl;

    cout << "Given String : " << endl;
    cout << "Hello," << " & " << "World!" << endl << endl;

    cout << endl;
    cout << "Int add: " << add(3, 4) << endl;
    cout << "Double add: " << add(2.5, 3.5) << endl;
    cout << "String add: " << add(string("Hello, "), string("World!")) << endl;

    return 0;
}