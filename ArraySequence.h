//
// Created by korna on 20.03.2021.
//
#include "Sequence.h"
#include "DynamicArray.h"
#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class ArraySequence : public Sequence<T> {

private:
    DynamicArray<T> items;

public:
    //Creation of the object
    ArraySequence() {
        items = DynamicArray<T>();
    }

    explicit ArraySequence(int count) {
        items = DynamicArray<T>(count);
    }

    ArraySequence(T *items, int count) {
        this->items = DynamicArray<T>(items, count);
    }

    ArraySequence(const ArraySequence<T> &list) {
        items = DynamicArray<T>(list.items);
    }

    explicit ArraySequence(Sequence<T> &list) : ArraySequence((*dynamic_cast<ArraySequence<T> *>(&list))) {
    }

    explicit ArraySequence(Sequence<T> *list) : ArraySequence(*list) {
    }

    explicit ArraySequence(const ArraySequence<T> *list) : ArraySequence(*list) {
    }

    explicit ArraySequence(const unique_ptr<Sequence<int>> &list) : ArraySequence(list.get()) {
    }

    explicit ArraySequence(const unique_ptr<ArraySequence<int>> &list) : ArraySequence(*list) {
    }

    //Decomposition

    T &At(int index) {
        return items.At(index);
    }

    ArraySequence<T> *GetSubsequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.GetLength())
            throw range_error("endIndex >= length");
        ArraySequence<T> *res = new ArraySequence<T>();
        for (int i = startIndex; i < endIndex + 1; ++i) {
            res->Append(items.At(i));
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
        if (items.GetLength() - 2 != index)
            items.Set(index, item);
        else
            items.Set(items.GetLength() - 1, item);

    }

    ArraySequence<T> *Concat(Sequence<T> &list) {
        ArraySequence<T> *res = new ArraySequence<T>();
        for (int i = 0; i < items.GetLength(); ++i) {
            res->Append(items[i]);
        }
        for (int i = 0; i < list.GetLength(); ++i) {
            res->Append(list[i]);
        }
        return res;
    }

    void PopFirst() {
        for (int i = 0; i < items.GetLength() - 1; ++i) {
            items.Set(i, items[i + 1]);
        }
        items.Resize(items.GetLength() - 1);
    }

    void PopLast() {
        items.Resize(items.GetLength() - 1);
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        for (int i = index; i < items.GetLength() - 1; ++i) {
            items.Set(i, items[i + 1]);
        }
        items.Resize(items.GetLength() - 1);
    }

    ArraySequence<T> *Concat(const Sequence<T> &list) {
        return Concat(dynamic_cast<ArraySequence<T>>(list));
    }

    ArraySequence<T> *Concat(const ArraySequence<T> *list) {
        return Concat(*list);
    }

    ArraySequence<T> &operator=(const ArraySequence<T> &list) {
        items = DynamicArray<T>(list.items);
        return *this;
    }
};