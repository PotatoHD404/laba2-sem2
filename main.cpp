#include <iostream>

using namespace std;

template<typename T>
class DynamicArray {
private:
    T *actual_array;
    unsigned int length;

//    DynamicArray(DynamicArray<T> &dynamicArray const);

    T Get(int index) {
        return this[index];
    }

    void Set(int index, T value) {
        if (0 < index >= length)
            throw out_of_range("blah");
        this[index] = value;
    }

    void Resize(int newSize) {

    }

    DynamicArray() {
        actual_array = new T[1];
        length = 0;
    }

    explicit DynamicArray(int count) {
        actual_array = new T[count];
        length = count;
    }

    explicit DynamicArray(T *items, int count) {
        actual_array = new T[count];
        memcpy(actual_array, items, count * sizeof(T));
        length = count;
    }

    ~DynamicArray() { delete[] actual_array; }

    unsigned int GetSize() { return length; }

    T &operator[](unsigned int index) { return actual_array[index]; }

};


int main() {
    cout << "Hello, World!" << endl;

    return 0;
}
