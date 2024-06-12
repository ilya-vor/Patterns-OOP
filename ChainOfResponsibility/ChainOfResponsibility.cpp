#include <iostream>
using  namespace std;
class DefaultHandler {
public:
    virtual bool handle(int request) {
        printf("%d is Prime\n", request);
        return true;
    }
    virtual ~DefaultHandler(){ }
};
class DivisionChecker: public DefaultHandler {
public:
    int number;
    DefaultHandler* next = nullptr;
    DivisionChecker(int number, DefaultHandler* handler) : number(number), next(handler) {}
    bool handle(int request) override {
        if (request % number == 0 && request != number) return false;
        else return next->handle(request);
    }
    ~DivisionChecker() { if (next != nullptr) delete next; }
};
int main()
{
    DefaultHandler* handler = new DefaultHandler;
    for (int i = 2; i < 100; i++) {
        if (handler->handle(i)) {
            DefaultHandler* newhandler = new DivisionChecker(i,handler);
            handler = newhandler;
        }
    }
}