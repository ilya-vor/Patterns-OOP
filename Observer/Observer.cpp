#include <iostream>
#include <vector>
using namespace std;

class Observer {
public:
    virtual void objectChanged() = 0;
};

class SpecificObserver : public Observer {
public:
    string name;
    SpecificObserver(string name): name(name) {}
    void objectChanged() override {
        cout << name << " has informed about changes\n";
    }
};

class Object {
private:
    vector <Observer*> observers;
public:
    void addObserver(Observer* o) { observers.push_back(o); }
    void notifyAll() {
        for (const auto& o : observers) {
            o->objectChanged(); 
        }
    }
    void change() {
        notifyAll();
    }
};



int main()
{
    Observer* obs = new SpecificObserver("Ilya");
    Object* obj = new Object();
    obj->addObserver(obs);
    obj->change();
    std::cout << "Hello World!\n";
}
