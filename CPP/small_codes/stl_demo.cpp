#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    // ----- Vector demo -----
    vector<int> v = {5, 1, 4, 2, 2, 5, 3};
    cout << "Original vector: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    sort(v.begin(), v.end()); // sort ascending
    v.erase(unique(v.begin(), v.end()), v.end()); // remove duplicates

    cout << "Sorted unique vector: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    if (binary_search(v.begin(), v.end(), 3))
        cout << "Found 3 in vector!\n\n";

    // ----- Map demo -----
    map<string, int> freq;
    vector<string> fruits = {"apple", "banana", "apple", "orange", "banana", "apple"};
    for (const auto& f : fruits) freq[f]++;

    cout << "Fruit frequencies:\n";
    for (auto& p : freq)
        cout << p.first << " -> " << p.second << "\n";
    cout << "\n";

    // ----- Set demo -----
    set<int> s = {3, 2, 1, 2, 4, 5};
    cout << "Set elements (unique & sorted): ";
    for (int x : s) cout << x << " ";
    cout << "\n";

    // Custom comparator (descending order)
    set<int, greater<int>> s2 = {3, 2, 1, 4, 5};
    cout << "Set in descending order: ";
    for (int x : s2) cout << x << " ";
    cout << "\n\n";

    // ----- Unordered Map demo -----
    unordered_map<string, int> umap;
    umap["car"] = 3;
    umap["bike"] = 7;
    umap["bus"] = 2;

    cout << "Unordered Map (fast lookup):\n";
    for (auto& p : umap)
        cout << p.first << " -> " << p.second << "\n";

    string key = "bike";
    if (umap.find(key) != umap.end())
        cout << "Found " << key << " with value " << umap[key] << "\n";

    return 0;
}