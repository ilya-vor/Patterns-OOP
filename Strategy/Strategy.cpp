#include <iostream>
using namespace std;

class MultStrategy {
public:
    virtual double get_product(double* arr, int size) = 0;
    virtual ~MultStrategy() {}
};

class ForwardMultStrategy : public MultStrategy {
public:
    double get_product(double* arr, int size) override {
        double product = 1;
        for (int i = 0; i < size; i++) {
            product = product * arr[i];
        }
        return product;
    }
};

class BackwardMultStrategy : public MultStrategy {
public:
    double get_product(double* arr, int size) override {
        double product = 1;
        for (int i = size - 1; i != -1; i--) {
            product = product * arr[i];
        }
        return product;
    }
};

class Storage {
public:
    double* arr;
    int size;
    MultStrategy* strategy;
    Storage(int size) : size(size), arr(new double[size]){
        for (int i = 0; i < size; i++) {
            arr[i] = (rand() / RAND_MAX) + 0.5;
        }
    }
    double get_product() {
        return strategy->get_product(arr, size);
    }
};

int main()
{
    Storage* storage = new Storage(10);

    MultStrategy* back = new BackwardMultStrategy();
    storage->strategy = back;
    cout << storage->get_product() << endl;
    delete back;

    MultStrategy* forw = new ForwardMultStrategy();
    storage->strategy = forw;
    cout << storage->get_product() << endl;
    delete forw;


    std::cout << "Hello World!\n";
}
