#include <iostream>
#include <vector>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
    virtual Shape* getRealShape() = 0;
};

class Point : public Shape {
public:
    int x, y;
    Point(int x, int y): x(x),y(y){}
    void draw() override {
        printf("Point %d %d\n", x, y);
    }
    Shape* getRealShape() override {
        return this;
    }
};

class ProxyPoint: public Shape {
public:
    int x, y;
    Shape* s;
    ProxyPoint(int x, int y) : x(x), y(y) { s = nullptr; }
    void draw() override {
        if (s == nullptr) s = new Point(x, y);
        s->draw();
    }
    Shape* getRealShape() override {
        return s;
    }
};

int main()
{
    vector<Shape*> s(3);
    s[0] = new Point(1, 1);
    s[1] = new ProxyPoint(5, 5);
    s[2] = new Point(10, 10);

    
    for (int i = 0; i != s.size(); i++) {
        s[i]->draw();
        s[i] = s[i]->getRealShape(); // Прокси сделал свое дело, дальше он будет лишь мешать программе
    }

    for (int i = 0; i != s.size(); i++) {
        if (dynamic_cast<Point*>(s[i]) != nullptr) printf("%d Shape is a Point\n", i);
    }
   
}

