//
// Created by korna on 20.03.2021.
//
#include "Sequence.h"
#include "DynamicArray.h"
#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class ArraySequence : Sequence<T> {

private:
    DynamicArray<T> items;

public:
    //Creation of the object
    ArraySequence() {
        items = DynamicArray<T>();
    }

    ArraySequence(T *items, int count) {
        this->items = DynamicArray<T>(items, count);
    }

    ArraySequence(const ArraySequence<T> &list) {
        items = DynamicArray<T>(list.items);
    }

    //Decomposition

    T &At(int index) {
        return items.At(index);
    }

    Sequence<T> GetSubsequence(int startIndex, int endIndex) {
        ArraySequence<T> res;
        for (int i = startIndex; i < endIndex; ++i) {
            res.Append(items.At(i));
        }
        return res;
    }

    int GetLength() {
        return items.GetLength();
    }


    //Operations
    void Append(T item) {
        items.Resize(items.GetLength() + 1);
        items.Set(items.GetLength() - 1, item);
    }

    void Prepend(T item) {
        items.Resize(items.GetLength() + 1);
        for (int i = items.GetLength() - 1; i > 0; --i) {
            items.Set(i, items.At(i - 1));
        }
        items.Set(0, item);
    }

    void InsertAt(T item, int index) {
        items.Resize(items.GetLength() + 1);
        for (int i = items.GetLength() - 1; i > index; --i) {
            items.Set(i, items[i - 1]);
        }
        items.Set(index, item);
    }

    Sequence<T> *Concat(Sequence<T> &list) {
        ArraySequence<T> res;
        for (int i = 0; i < items.GetLength(); ++i) {
            res.Append(items[i]);
        }
        for (int i = 0; i < list->items.GetLength(); ++i) {
            res.Append(list.items[i]);
        }
        return res;
    }

    ArraySequence<T> &operator=(const ArraySequence<T> &list) {
        this->~ArraySequence();
        items = DynamicArray<T>(list.items);
        return *this;
    }
};