//
// Created by korna on 20.03.2021.
//
#ifndef LABA2_ARRAYSEQUENCE_H
#define LABA2_ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"
#include <iostream>
#include <cstring>
#include "IEnumerator.h"

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

    explicit ArraySequence(size_t count) {
        items = DynamicArray<T>(count);
    }

    explicit ArraySequence(int count) : ArraySequence((size_t) count) {}

    ArraySequence(T *items, size_t count) {
        this->items = DynamicArray<T>(items, count);
    }

    template<size_t N>
    explicit ArraySequence(T (&items)[N]) : ArraySequence(items, N) {}

    ArraySequence(initializer_list<T> items) : ArraySequence() {
        for (T item : items)
            this->Append(item);
    }

    ArraySequence(ArraySequence<T> const &list) {
        items = DynamicArray<T>(list.items);
    }

    explicit ArraySequence(Sequence<T> &list) : ArraySequence((*dynamic_cast<ArraySequence<T> *>(&list))) {
    }

    explicit ArraySequence(Sequence<T> *list) : ArraySequence(*list) {
    }

    explicit ArraySequence(const ArraySequence<T> *list) : ArraySequence(*list) {
    }

    explicit ArraySequence(const unique_ptr<Sequence<T>> &list) : ArraySequence(list.get()) {
    }

    explicit ArraySequence(const unique_ptr<ArraySequence<T>> &list) : ArraySequence(*list) {
    }

    //Decomposition

    T &At(size_t index) {
        return items.At(index);
    }

    ArraySequence<T> *GetSubsequence(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.GetLength())
            throw range_error("endIndex >= length");
        ArraySequence<T> *res = new ArraySequence<T>();
        for (size_t i = startIndex; i < endIndex + 1; ++i) {
            res->Append(items.At(i));
        }
        return res;
    }

    size_t GetLength() {
        return items.GetLength();
    }

    ArraySequence<T> *Subsequence(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.GetLength())
            throw range_error("endIndex >= length");
        ArraySequence<T> *res = new ArraySequence<T>();
        res->items = items.GetSubArray(startIndex, endIndex);
        return res;
    }

    bool operator==(ArraySequence<T> &list) {
        size_t len = list.GetLength();
        if (len != this->items.GetLength())
            return false;
        for (size_t i = 0; i < len; ++i)
            if (this->At(i) != list.At(i))
                return false;

        return true;
    }


    //Operations
    template<typename T1>
    ArraySequence<T1> *Init() const {
        return new ArraySequence<T1>();
    }

    template<typename T1>
    ArraySequence<T1> *Init(size_t count) const {
        return new ArraySequence<T1>(count);
    }

    void Append(T item) {
        items.Resize(items.GetLength() + 1);
        items.Set(items.GetLength() - 1, item);
    }

    void Prepend(T item) {
        items.Resize(items.GetLength() + 1);
        for (size_t i = items.GetLength() - 1; i > 0; --i) {
            items.Set(i, items.At(i - 1));
        }
        items.Set(0, item);
    }

    void InsertAt(T item, size_t index) {
        items.Resize(items.GetLength() + 1);

        for (size_t i = items.GetLength() - 1; i > index; --i) {
            items.Set(i, items[i - 1]);
        }
        if (items.GetLength() - 2 != index)
            items.Set(index, item);
        else
            items.Set(items.GetLength() - 1, item);
    }

    ArraySequence<T> *Concat(Sequence<T> &list) {
        ArraySequence<T> *res = new ArraySequence<T>();
        for (size_t i = 0; i < items.GetLength(); ++i) {
            res->Append(items[i]);
        }
        for (size_t i = 0; i < list.GetLength(); ++i) {
            res->Append(list[i]);
        }
        return res;
    }

    IEnumerator<T> *GetEnumerator() {
        return new typename IEnumerable<T>::Enumerator(this);
    }

    void PopFirst() {
        for (size_t i = 0; i < items.GetLength() - 1; ++i) {
            items.Set(i, items[i + 1]);
        }
        items.Resize(items.GetLength() - 1);
    }

    void PopLast() {
        items.Resize(items.GetLength() - 1);
    }

    void RemoveAt(size_t index) {
        if (index < 0 || index >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        for (size_t i = index; i < items.GetLength() - 1; ++i) {
            items.Set(i, items[i + 1]);
        }
        items.Resize(items.GetLength() - 1);
    }

    template<typename T1>
    ArraySequence<T1> Map(T1 (*mapper)(T)) {
        ArraySequence<T1> *res = dynamic_cast<ArraySequence<T1> *>(Enumerable<T>::template Map<T1, ArraySequence>(
                mapper));
        auto res1 = ArraySequence<T1>(res);
        delete res;
        return res1;
    }

    ArraySequence<T> Where(bool(*predicate)(T)) {
        ArraySequence<T> *res = dynamic_cast<ArraySequence<T> *>(Enumerable<T>::template Where<ArraySequence>(
                predicate));
        auto res1 = ArraySequence<T>(res);
        delete res;
        return res1;
    }

    void Clear() {
        items.Resize(0);
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

#endif //LABA2_ARRAYSEQUENCE_H