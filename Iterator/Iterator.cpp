#include <iostream>
#include <list>
using namespace std;

class Iterator {
public:
    virtual void  first() = 0;
    virtual bool  isEOL() = 0;
    virtual void  next() = 0;
    virtual int  get() = 0;
    virtual void  set(int value) = 0;
    virtual ~Iterator() {}
};

class Storage {
public:
    virtual Iterator* createIterator() { return nullptr; }
    virtual ~Storage() {};
};

class ArrayStorage : public Storage {
public:
    int* _values;
    int _size;
public:
    ArrayStorage(int size) : _size(size) {
        _values = new int[size];
        for (int i = 0; i < size; i++) {
            _values[i] = rand() % 10;
        }
    }
    int get(int index) { return _values[index]; }
    void set(int index, int value) { _values[index] = value; }
    int getSize() { return _size; }
    Iterator* createIterator() override;
    ~ArrayStorage() {
        delete[] _values;
    }
};

class ArrayIterator : public Iterator {
public:
    ArrayStorage* _array;
    int _currentIndex;
public:
    ArrayIterator(ArrayStorage* arr) : _array(arr) { _currentIndex = 0; }
    void first() override { _currentIndex = 0; }
    bool isEOL() override { return _array->getSize() == _currentIndex; }
    void next() override { _currentIndex = _currentIndex + 1; }
    int get() override { return _array->get(_currentIndex); }
    void set(int value) override { _array->set(_currentIndex, value); }
};

Iterator* ArrayStorage::createIterator() {
    return new ArrayIterator(this);
}

int main()
{
    ArrayStorage* arr = new ArrayStorage(3);
    for (int i = 0; i < arr->getSize(); i++) {
        cout << arr->get(i) << endl;
    }

    cout << "\n";

    Iterator* iter = arr->createIterator();
    for (iter->first(); !iter->isEOL(); iter->next()) {
        cout << iter->get() << endl;
    }

    list<int> ar(10);
    list<int>::iterator i;
    for (i = ar.begin(); i != ar.end(); i++) {
        *i = rand();
    }
    for (i = ar.begin(); i != ar.end(); i++) {
        cout << *i << endl;
    }

    std::cout << "Hello World!\n";
}
