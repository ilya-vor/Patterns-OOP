#include <iostream>
#include <stack>
using namespace std;

class Point {
public:
    int x, y;
    Point(int x, int y): x(x), y(y){}
    void move(int dx, int dy) {
        x = x + dx;
        y = y + dy;
    }
    void draw() { printf("%d %d\n", x, y); }
};

class Command {
public:
    void virtual execute(Point* object) = 0;
    void virtual unexecute() = 0;
    virtual Command* clone() = 0;
    virtual ~Command() {}
};

class MoveCommand: public Command {
public:
    int dx, dy;
    Point* object;
    MoveCommand(int dx, int dy) : dx(dx), dy(dy) { object = nullptr; }
    void execute(Point* obj) override {
        obj->move(dx, dy);
        object = obj;
    }
    void unexecute() override {
        object->move(-dx, -dy);
    }
    Command* clone() override {
        return new MoveCommand(dx, dy);
    }
};

int main()
{
    Point* p = new Point(0, 0);

    stack<Command*> history;

    Command* moveToLeft = new MoveCommand(-5, 0);

    p->draw();
    moveToLeft->execute(p);
    history.push(moveToLeft);
    p->draw();

    Command* lastCommand = history.top();
    lastCommand->unexecute();
    history.pop();
    p->draw();

    delete lastCommand;


    std::cout << "Hello World!\n";
}
