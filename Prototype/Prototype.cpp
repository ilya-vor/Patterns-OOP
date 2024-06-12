#include <iostream>

class Animal {
public:
    virtual Animal* clone() = 0;
};

class Dog : public Animal {
public:
    Animal* clone() override {
        return new Dog(*this);
    }
};

class Cat : public Animal {
public:
    Animal* clone() override {
        return new Cat(*this);
    }
};

int main()
{
    Animal* cages[2];
    cages[0] = new Dog();
    cages[1] = new Cat();
    Animal* clonedAnimal = cages[1]->clone();
    if (dynamic_cast<Cat*>(clonedAnimal) != nullptr) printf("Cat will be created!!\n");
    std::cout << "Hello World!\n";
}
