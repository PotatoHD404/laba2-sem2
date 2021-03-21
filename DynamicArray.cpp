//
// Created by korna on 20.03.2021.
//
#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class DynamicArray {
private:
    T *actual_array;
    int length;
public:
    //Creation of the object
    DynamicArray() : actual_array(new T[1]()), length(0) {}

    explicit DynamicArray(int count) {
        if (count < 0)
            throw out_of_range("count < 0");

        if (count > 0)
            actual_array = new T[count]();
        else
            actual_array = new T[1]();
        length = count;

    }

    DynamicArray(T *items, int count) {
        if (count < 0)
            throw out_of_range("count < 0");
        if (items == NULL)
            throw invalid_argument("items is NULL");
        if (count > 0) {
            actual_array = new T[count]();
            memcpy(actual_array, items, count * sizeof(T));
        } else {
            actual_array = new T[1]();
        }
        length = count;
    }

    DynamicArray(const DynamicArray<T> &dynamicArray) {
        length = dynamicArray.length;
        if (length > 0) {
            actual_array = new T[length]();
            memcpy(actual_array, dynamicArray.actual_array, length * sizeof(T));
        }
        else
            actual_array = new T[1]();
    }

    //Decomposition
    T &At(int index) {
        if (index < 0 || index >= length)
            throw out_of_range("index < 0 or index >= length");
        return actual_array[index];
    }

    void Set(int index, T value) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        At(index) = value;
    }

    int GetLength() { return length; }

    T &operator[](int index) { return At(index); }

    //Operations
    void Resize(int new_length) {
        if (new_length < 0) {
            throw range_error("new_length < 0");
        }
        T *new_array = new T[new_length]();
        memcpy(new_array, actual_array, sizeof(T) * new_length);
        length = new_length;
        delete[] actual_array;
        actual_array = new_array;
    }
    DynamicArray<T> &operator=(const DynamicArray<T> &list) {
        this->~DynamicArray();
        length = list.length;
        if (length > 0) {
            actual_array = new T[length]();
            memcpy(actual_array, list.actual_array, length * sizeof(T));
        }
        else
            actual_array = new T[1]();
        return *this;
    }

    //Termination
    ~DynamicArray() { delete[] actual_array; }

};
