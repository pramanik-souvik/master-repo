#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    vector<int> v = {5, 2, 8, 1, 3};

    cout << "The given vector: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 1. Sum using lambda with reference capture
    int sum = 0;
    for_each(v.begin(), v.end(), [&](int x) { sum += x; });
    cout << "Sum: " << sum << "\n";

    // 2. Lambda as a square function
    auto square = [](int x) { return x * x; };
    cout << "Square of 5: " << square(5) << "\n";

    // 3. Sort with custom comparator (lambda)
    sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    cout << "Sorted descending: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // 4. Mixed capture (sum already calculated)
    auto greaterThanSum = [=](int x) { return x > sum; };
    cout << "Numbers greater than sum (" << sum << "): ";
    for (int x : v) if (greaterThanSum(x)) cout << x << " ";
    cout << "\n";

    // 5. Generic lambda (works for any type)
    auto multiply = [](auto a, auto b) { return a * b; };
    cout << "Multiply int: " << multiply(3, 4) << "\n";
    cout << "Multiply double: " << multiply(2.5, 1.2) << "\n";

    // 6. Recursive lambda (factorial)
    function<int(int)> fact = [&](int n) {
        return (n <= 1) ? 1 : n * fact(n - 1);
    };
    cout << "Factorial of 6: " << fact(6) << "\n";

    return 0;
}