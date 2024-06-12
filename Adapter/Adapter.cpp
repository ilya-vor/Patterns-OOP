#include <iostream>

class IX {
public:
    virtual int get(int index) = 0;
    virtual int getSize() = 0;
};

class X : public IX {
private:
    int* arr;
    int size;
public:
    X(int size) : size(size) { arr = new int[size]; }
    int get(int index) override { return arr[index]; }
    int getSize() override { return size; }
};

class IY {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual int get() = 0;
    virtual bool isEOL() = 0;
};

class Adapter : IY {
private:
    X* arr;
    int currIndex;
public:
    Adapter(X* x): arr(x){}
    void first() override { currIndex = 0; }
    void next() override { currIndex = currIndex + 1; }
    int get() override { return arr->get(currIndex); }
    bool isEOL() override { return currIndex == arr->getSize(); }
};

int main()
{
    X* x = new X(10);
    Adapter* adapter = new Adapter(x);

    std::cout << "Hello World!\n";
}
