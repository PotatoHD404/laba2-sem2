//
// Created by korna on 20.03.2021.
//

#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class LinkedList {
private:
    struct node {
        T data;
        node *next;
    };
    node *head, *tail;
    unsigned int length;

    node *CreateNode(T data) {
        node *res = new T[1];
        res->data = data;
        res->next = NULL;
    }

    node *GetNode(int index) {
        if (index < 0 || index >= length || head == NULL)
            throw out_of_range("");
        node *res = head;
        for (int i = index - 1; i >= 0; --i) {
            res = res->next;
        }
        return res;
    }

public:
    //Creation of the object
    LinkedList() {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    LinkedList(T *items, int count) {
        head = CreateNode(items[0]);
        node *prev = head;
        for (int i = 1; i < count; ++i) {
            prev->next = CreateNode(items[i]);
            prev = prev->next;
        }
        tail = prev;
        length = count;
    }

    LinkedList(const LinkedList<T> &list) {
        node *tmp = list.head;
        head = CreateNode(tmp->data);
        node *prev = head;
        while (tmp->next != NULL) {
            prev->next = CreateNode(tmp->data);
            prev = prev->next;
            tmp = tmp->next;
        }
        tail = prev;
        length = GetLength(list);
    }

    //Decomposition
    T GetFirst() {
        if (head == NULL)
            throw out_of_range("");
        return head;
    }

    T GetLast() {
        if (tail == NULL)
            throw out_of_range("");
        return tail;
    }

    T At(int index) {
        if (index == 0)
            return GetFirst();
        if (index == length - 1)
            return GetLast();
        return GetNode(index)->data;
    }

    LinkedList<T> *GetSubList(int startIndex, int endIndex) {
        LinkedList<T> *res;
        res(new LinkedList<T>);
        node *tmp = GetNode(startIndex);
        for (int i = startIndex; i < endIndex + 1; ++i) {
            res->Append(tmp->data);
            tmp = tmp->next;
        }
        return res;
    }

    int GetLength() {
        return length;
    }

    T operator[](unsigned int index) { return At(index); }

    //Operations
    void Append(T item) {
        node *tmp = CreateNode(item);
        if (head == NULL)
            head = tmp;
        else
            tail->next = tmp;
        tail = tmp;
        ++length;
    }

    void Prepend(T item) {
        node *tmp = CreateNode(item);
        if (head == NULL) {
            head = tmp;
            tail = tmp;
        } else {
            tmp->next = head;
            head = tmp;
        }
        ++length;
    }

    void InsertAt(T item, int index) {
        node *tmp = CreateNode(item);
        node *prev = GetNode(index);
        node *next = prev->next;
        prev->next = tmp;
        tmp->next = next;
    }

    LinkedList<T> *Concat(LinkedList<T> *list) {
        LinkedList<T> *res = new LinkedList<T>[1];
        *res = LinkedList();
        for (int i = 0; i < list->GetLength(); ++i) {
            res->Append(list->At(i));
        }
        for (int i = 0; i < length; ++i) {
            res->Append(this[i]);
        }
        return res;
    }

    //Termination
    ~LinkedList() {
        node *tmp = head;
        for (int i = 1; i < length; ++i) {
            node *next = tmp->next;
            delete *tmp;
            tmp = next;
        }
    }
};

