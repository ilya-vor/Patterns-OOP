#include <iostream>

class Template {
public:
    void templateMethod() {
        printf("1\n");
        operation1();
        printf("3\n");
        operation2();
        printf("5\n");
    }
    void virtual operation1() = 0;
    void virtual operation2() = 0;
};

class A : public Template {
    void operation1() override {
        printf("2\n");
    }
    void operation2() override {
        printf("4\n");
    }
};

class B : public Template {
    void operation1() override {
        printf("BA\n");
    }
    void operation2() override {
        printf("BUBE\n");
    }
};

int main()
{
    A* a = new A();
    B* b = new B();
    a->templateMethod();
    printf("\n");
    b->templateMethod();
    std::cout << "Hello World!\n";
}

