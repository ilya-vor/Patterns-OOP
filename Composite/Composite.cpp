#include <iostream>
#include <vector>
using namespace std;

class Shape {
public:
    void virtual move(int dx, int dy) = 0;
    void virtual draw() = 0;
};

class Point : public Shape {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    void move(int dx, int dy) override {
        x = x + dx;
        y = y + dy;
    }
    void draw() override {
        printf("Point %d %d\n", x, y);
    }
};

class Circle : public Shape {
public:
    int x, y, r;
    Circle(int x, int y, int r) : x(x), y(y), r(r){}
    void move(int dx, int dy) override {
        x = x + dx;
        y = y + dy;
    }
    void draw() override {
        printf("Circle %d %d %d\n", x, y, r);
    }
};

class Group : public Shape {
public:
    Group() {}
    vector <Shape*> shapes;
    void move(int dx, int dy) override {
        for (const auto& s : shapes) {
            s->move(dx, dy);
        }
    }
    void draw() override {
        for (const auto& s : shapes) {
            s->draw();
        }
    }
    void addShape(Shape* s) {
        shapes.push_back(s);
    }
};

int main()
{
    Group* g = new Group();
    g->addShape(new Point(1, 1));
    g->addShape(new Circle(3,5,7));
    g->draw();
    g->move(10, 10);
    g->draw();
    std::cout << "Hello World!\n";
}

