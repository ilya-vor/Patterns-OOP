#include <iostream>
#include <vector>
#include <list>
using namespace std;

class StorageImpl {
public:
	virtual int get(int index) = 0;
	virtual void set(int index, int value) = 0;
	virtual void pushback(int value) = 0;
	virtual int getSize() = 0;
	virtual ~StorageImpl() {}
};

class VectorStorageImpl : public StorageImpl {
public:
	vector<int> values;
	int get(int index) override { return values[index]; }
	void set(int index, int value) override { values[index] = value; }
	void pushback(int value) override { values.push_back(value); }
	int getSize() override { return values.size(); }
};

class ListStorageImpl : public StorageImpl {
public:
	list<int> values;
	int currentIndex = 0;
	int get(int index) override {
		list<int>::iterator i;
		for (i = values.begin(); i != values.end(); i++) {
			if (index == 0) {
				return *i;
			}
			else {
				index--;
			}
		}
	}
	void set(int index, int value) override {
		list<int>::iterator i;
		for (i = values.begin(); i != values.end(); i++) {
			if (index == 0) {
				*i = value;
			}
			else {
				index--;
			}
		}
	}
	void pushback(int value) override { values.push_back(value); }
	int getSize() override { return values.size(); }
};

class Storage {
public:
	StorageImpl* impl;
	int get(int index) { return impl->get(index); }
	void set(int index, int value) { impl->set(index, value); }
	void pushback(int value) { impl->pushback(value); }
	void relocate() {
		StorageImpl* newStorage;
		if (dynamic_cast<ListStorageImpl*>(impl) != nullptr) newStorage = new VectorStorageImpl;
		else newStorage = new ListStorageImpl;	
		for (int i = 0; i < impl->getSize(); i++) {
			newStorage->pushback(impl->get(i));
		}
		delete impl;
		impl = newStorage;
	}
};

class OrderedStorage: public Storage{
public:
	void sort() {
		for (int i1 = 0; i1 < impl->getSize(); i1++) {
			for (int i2 = i1 + 1; i2 < impl->getSize(); i2++) {
				if (get(i1) > get(i2)) {
					int x1 = get(i1);
					int x2 = get(i2);
					set(i1, x2);
					set(i2, x1);
				}
			}
		}
	}
};

int main() {

	OrderedStorage* st = new OrderedStorage;
	st->impl = new ListStorageImpl;

	for (int i = 0; i < 5; i++) {
		st->pushback(rand() % 100);
	}

	st->relocate();

	st->sort();

	return 1;
}