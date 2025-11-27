#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Animal {
public:
    virtual void speak() const = 0;
    virtual void eat() const { cout << "Animal is eating...\n"; }
    virtual ~Animal() { cout << "Animal class closed.\n"; }
};

class Dog : public Animal {
public:
    void speak() const override { cout << "Dog says: Woof!\n"; }
    void eat() const override { cout << "Dog is eating bones.\n"; }
};

class Cat : public Animal {
public:
    void speak() const override { cout << "Cat says: Meow!\n"; }
    void eat() const override { cout << "Cat is eating fish.\n"; }
};

class Cow : public Animal {
public:
    void speak() const override { cout << "Cow says: Moo!\n"; }
    void eat() const override { cout << "Cow is eating grass.\n"; }
};

int main() {

    vector<unique_ptr<Animal>> zoo;

    zoo.push_back(make_unique<Dog>());
    zoo.push_back(make_unique<Cat>());
    zoo.push_back(make_unique<Cow>());

    cout << "Welcome to the Zoo!\n\n";

    for (const auto& animal : zoo) {
        animal->speak();
        animal->eat();
        cout << "------------------\n";
    }

    cout << "Zoo closing. Animals go to sleep...\n";
    return 0;
}