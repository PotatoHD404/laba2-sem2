//
// Created by korna on 20.03.2021.
//
#include "Sequence.cpp"
#include <iostream>
#include <cstring>

using namespace std;
template<class T>
class LinkedListSequence : Sequence<T> {
private:
    LinkedList <T> *items;

public:
    //Creation of the object
    LinkedListSequence() {
        items(new LinkedList<T>());
    }

    LinkedListSequence(T *items, int count) {
        items(new LinkedList<T>(items, count));
    }

    explicit LinkedListSequence(const LinkedList <T> &list) {
        items(new LinkedList<T>(list));
    }

    //Decomposition

    T Get(int index) {
        return items->At(index);
    }

    Sequence<T> *GetSubsequence(int startIndex, int endIndex) {
        LinkedListSequence<T> *res;
        res(new LinkedListSequence<T>());
        return res;
    }

    int GetLength() {
        return items->GetLength();
    }

    //Operations
    void Append(T item) {
        items->Append(item);
    }

    void Prepend(T item) {
        items->Prepend(item);
    }

    void InsertAt(T item, int index) {
        items->InsertAt(item, index);
    }

    Sequence<T> *Concat(Sequence<T> *list) {
        LinkedListSequence<T> *res;
        res(new LinkedListSequence<T>());
        for (int i = 0; i < items->GetLength(); ++i) {
            res->Append(items->At(i));
        }
        for (int i = 0; i < list->items->GetLength(); ++i) {
            res->Append(list->items->At(i));
        }
        return res;
    }

    //Termination
    ~LinkedListSequence() {
        delete *items;
        delete[] items;
    }
};
