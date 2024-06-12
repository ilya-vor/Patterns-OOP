#include <iostream>

class Memento {
private:
    friend class Point;
    int _x, _y;
    void setState(int x, int y) {
        _x = x;
        _y = y;
    }
    void getState(int& x, int& y) {
        x = _x;
        y = _y;
    }
public:
    Memento() : _x(0), _y(0) {}
    ~Memento() {}
};

class Point {
private:
    int _x, _y;
public:
    Point(int x, int y):_x(x),_y(y){}
    void move(int dx, int dy) {
        _x = _x + dx;
        _y = _y + dy;
    }
    void print() { printf("%d %d\n", _x, _y); }
    Memento* createMemento() {
        Memento* m = new Memento();
        m->setState(_x, _y);
        return m;
    }
    void loadMemento(Memento* m) {
        m->getState(_x, _y);
    }
    ~Point(){}
};



int main()
{
    Point* p = new Point(0,0);
    Memento* m = p->createMemento();
    p->move(5, -5);
    p->print();
    p->loadMemento(m);
    p->print();
}
