#include <iostream>

class Shape {
public:
    void virtual draw() = 0;
    virtual ~Shape() {}
};

class Point: public Shape {
public:
    int x, y;
    Point(int x, int y): x(x),y(y){}
    void draw() override { printf("Point %d %d\n", x, y); }
};

class SelectedShape : public Shape {
public:
    Shape* s;
    SelectedShape(Shape* s): s(s){}
    void draw() { 
        printf("<selected>\n");
        s->draw();
        printf("<selected>\n");
    }
};

int main()
{
    Shape* s = new Point(5, 5);
    s->draw();
    s = new SelectedShape(s);
    s->draw();
    std::cout << "Hello World!\n";
}

