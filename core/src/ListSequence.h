//
// Created by korna on 20.03.2021.
//
#ifndef LABA2_LISTSEQUENCE_H
#define LABA2_LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"
#include <iostream>
#include <cstring>
#include "IEnumerator.h"

using namespace std;

template<class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> items;



public:
    //Creation of the object
    ListSequence() {
        items = LinkedList<T>();
    }

    explicit ListSequence(int count) {
        items = LinkedList<T>(count);
    }

    ListSequence(T *items, int count) {
        this->items = LinkedList<T>(items, count);
    }

    ListSequence(const ListSequence<T> &list) {
        items = LinkedList<T>(list.items);
    }

    explicit ListSequence(const LinkedList<T> &list) {
        items = LinkedList<T>(list);
    }

    explicit ListSequence(Sequence<T> &list) : ListSequence((*dynamic_cast<ListSequence<T> *>(&list))) {
    }

    explicit ListSequence(Sequence<T> *list) : ListSequence(*list) {
    }

    explicit ListSequence(const ListSequence<T> *list) : ListSequence(*list) {
    }

    explicit ListSequence(const unique_ptr<Sequence<int>> &list) : ListSequence(list.get()) {
    }

    explicit ListSequence(const unique_ptr<ListSequence<int>> &list) : ListSequence(*list) {
    }

    //Decomposition

    T &At(int index) {
        return items.At(index);
    }

    ListSequence<T> *Subsequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.GetLength())
            throw range_error("endIndex >= length");
        ListSequence<T> *res = new ListSequence<T>();
        res->items = items.GetSubList(startIndex, endIndex);
        return res;
    }

    int GetLength() {
        return items.GetLength();
    }

    //Operations
    void Clear() {
        while (items.GetLength()) items.PopFirst();
    }

    ListSequence<T> *Clone() const {
        return new ListSequence<T>(this->items);
    }

    ListSequence<T> *Init() const {
        return new ListSequence<T>();
    }

    ListSequence<T> *Init(int count) const {
        return new ListSequence<T>(count);
    }

    IEnumerator<T> *GetEnumerator() {
        return new typename IEnumerable<T>::Enumerator(this);
    }


    void Append(T item) {
        items.Append(item);
    }

    void Prepend(T item) {
        items.Prepend(item);
    }

    void InsertAt(T item, int index) {
        items.InsertAt(item, index);
    }

    void PopFirst() {
        items.PopFirst();
    }

    void PopLast() {
        items.PopLast();
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        items.RemoveAt(index);
    }

    ListSequence<T> *Concat(Sequence<T> &list) {
        ListSequence<T> *res = new ListSequence<T>();
        for (int i = 0; i < items.GetLength(); ++i) {
            res->Append(items.At(i));
        }
        for (int i = 0; i < list.GetLength(); ++i) {
            res->Append(list[i]);
        }
        return res;
    }

    ListSequence<T> *Concat(const Sequence<T> &list) {
        return Concat(dynamic_cast<ListSequence<T>>(list));
    }

    ListSequence<T> *Concat(const ListSequence<T> *list) {
        return Concat(*list);
    }

    ListSequence<T> &operator=(const ListSequence<T> &list) {
        items = LinkedList<T>(list.items);
        return *this;
    }

};

#endif //LABA2_LISTSEQUENCE_H