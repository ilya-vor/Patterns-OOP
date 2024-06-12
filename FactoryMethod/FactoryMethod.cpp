#include <iostream>
#include <vector>
using namespace std;

class Shape {
public:
    void virtual save(FILE* stream) = 0;
    void virtual load(FILE* stream) = 0;
    void virtual print() = 0;
};

class Point : public Shape {
public:
    int x, y;
    void save(FILE* stream) override {
        fprintf(stream, "P\n");
        fprintf(stream, "%d %d\n", x, y);
    }
    void load(FILE* stream) override {
        fscanf(stream, "%d %d\n", &x, &y);
    }
    void print() {
        printf("\n P %d %d\n", x, y);
    }
 };

class Circle : public Shape {
public:
    int x, y, r;
    void save(FILE* stream) override {
        fprintf(stream, "C\n");
        fprintf(stream, "%d %d %d\n", x, y, r);
    }
    void load(FILE* stream) override {
        fscanf(stream, "%d %d %d\n", &x, &y, &r);
    }
    void print() {
        printf("\n C %d %d %d\n", x, y, r);
    }
};

class Storage {
public:
    vector <Shape*> shapes;
    string filename;
    Storage(string filename) : filename(filename) {};
    virtual Shape* createShape(char charcode) {
        return nullptr;
    }
    void print() {
        for (const auto &s : shapes) {
            s->print();
        }
    }
    void loadShapes() {
        FILE* stream;
        int count;
        char charcode;
        Shape* shape;
        if ((stream = fopen(filename.c_str(), "r")) != nullptr) {
            fscanf(stream, "%d\n", &count);
            for (int i = 0; i < count; i++) {
                fscanf(stream, "%c\n", &charcode);
                shape = createShape(charcode);
                if (shape != nullptr) {
                    shape->load(stream);
                    shapes.push_back(shape);
                }
            }
            fclose(stream);
        }
    }
    void saveShapes() {
        FILE* stream;
        if ((stream = fopen(filename.c_str(), "w")) != nullptr) {
            fprintf(stream, "%d\n", (int)shapes.size());
            for (const auto& s : shapes) {
                s->save(stream);
            }
            fclose(stream);
        }
    }
};

class StorageForCirclesAndPoints : public Storage {
public:
    StorageForCirclesAndPoints(string filename) : Storage(filename) {};
    Shape* createShape(char charcode) override {
        if (charcode == 'P') return new Point();
        if (charcode == 'C') return new Circle();
        return nullptr;
    }
};


int main()
{
    string filename = "O:\\data.txt";
    /*
    Storage* s = new Storage(filename);
    s->shapes.push_back(new Point());
    s->shapes.push_back(new Circle());
    s->shapes.push_back(new Point());
    s->saveShapes();
    delete s;
    */
    Storage* s1 = new StorageForCirclesAndPoints(filename);
    s1->loadShapes();
    s1->print();
    delete s1;

    std::cout << "Hello World!\n";
}

