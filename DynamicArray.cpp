//
// Created by korna on 20.03.2021.
//

#include <cstring>

template<class T>
class DynamicArray {
private:
    T *actual_array;
    unsigned int length;
public:
    //Creation of the object
    DynamicArray() {
        actual_array = new T[1];
        length = 0;
    }

    explicit DynamicArray(int count) {
        actual_array = new T[count];
        length = count;
    }

    DynamicArray(T *items, int count) {
        actual_array = new T[count];
        memcpy(actual_array, items, count * sizeof(T));
        length = count;
    }

    DynamicArray(const DynamicArray<T> &dynamicArray) {
        length = dynamicArray.length;
        actual_array = new T[length];
        memcpy(actual_array, dynamicArray.actual_array, length * sizeof(T));
    }

    //Decomposition
    T &At(int index) {
        if (index < 0 || index >= length)
            throw out_of_range("");
        return actual_array[index];
    }

    void Set(int index, T value) {
        if (index < 0 || index >= length)
            throw range_error("");
        At(index) = value;
    }

    unsigned int GetLength() { return length; }

    T &operator[](int index) { return At(index); }

    //Operations
    void Resize(int new_length) {
        if (new_length < 0) {
            throw range_error("");
        }
        T *new_array = new T[new_length];
        memcpy(new_array, actual_array, sizeof(T) * new_length);
        length = new_length;
        delete[] actual_array;
        actual_array = new_array;
    }

    //Termination
    ~DynamicArray() { delete[] actual_array; }

};
