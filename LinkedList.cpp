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
    int length;

    node *CreateNode(T data) {
        node *res = new node();
        res->data = data;
        res->next = NULL;
    }

    node *CreateNode() {
        node *res = new node();
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
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    explicit LinkedList(int count) : LinkedList() {
        if (count < 0)
            throw out_of_range("count < 0");
        if (count > 0) {
            head = CreateNode();
            node *prev = head;
            for (int i = 1; i < count; ++i) {
                prev->next = CreateNode();
                prev = prev->next;
            }
            tail = prev;
            length = count;
        }
    }

    LinkedList(T *items, int count) : LinkedList() {
        if (count < 0)
            throw out_of_range("count < 0");
        if (items == NULL)
            throw invalid_argument("items is NULL");
        if (count > 0) {
            head = CreateNode(items[0]);
            node *prev = head;
            for (int i = 1; i < count; ++i) {
                prev->next = CreateNode(items[i]);
                prev = prev->next;
            }
            tail = prev;
            length = count;
        }
    }

    LinkedList(const LinkedList<T> &list) : LinkedList() {
        if (list.length > 0) {
            node *tmp = list.head;
            head = CreateNode(tmp->data);
            node *prev = head;
            tmp = tmp->next;
            while (tmp != NULL) {
                prev->next = CreateNode(tmp->data);
                prev = prev->next;
                tmp = tmp->next;
            }
            tail = prev;
            length = list.length;
        }
    }

    //Decomposition
    T &GetFirst() {
        if (!head)
            throw out_of_range("");
        return head->data;
    }

    T &GetLast() {
        if (!tail)
            throw out_of_range("");
        return tail->data;
    }

    T &At(int index) {
        if (index < 0 || index >= length)
            throw out_of_range("index < 0 or index >= length");
        if (index == 0)
            return GetFirst();
        if (index == length - 1)
            return GetLast();
        return GetNode(index)->data;
    }

    void Set(int index, T value) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        At(index) = value;
    }

    LinkedList<T> GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= length)
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= length)
            throw range_error("endIndex >= length");
        LinkedList<T> res;
        node *tmp = GetNode(startIndex);
        for (int i = startIndex; i < endIndex + 1; ++i) {
            res.Append(tmp->data);
            tmp = tmp->next;
        }
        return res;
    }

    int GetLength() {
        return length;
    }

    T &operator[](unsigned int index) { return At(index); }

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

    void PopLast() {
        if (length < 1)
            throw range_error("index < 0 or index >= length");
        if (length == 1) {
            this->PopFirst();
            return;
        }
        node *prev = GetNode(length - 2);
        tail = prev;
        delete prev->next;
        --length;
    }

    void PopFirst() {
        if (length < 1)
            throw range_error("index < 0 or index >= length");
        node *prev = head;
        head = prev->next;
        delete prev;
        --length;
        if (length == 0) {
            tail = NULL;
            head = NULL;
        }
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        if (index == length - 1) {
            this->Append(index);
            return;
        } else if (index == 0) {
            this->Prepend(index);
            return;
        }


        node *tmp = CreateNode(item);
        node *prev = GetNode(index - 1);
        node *next = prev->next;
        prev->next = tmp;
        tmp->next = next;
        ++length;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        if (index == length - 1) {
            this->PopLast();
            return;
        } else if (index == 0) {
            this->PopFirst();
            return;
        }


        node *prev = GetNode(index);
        node *next = (prev->next)->next;
        delete prev->next;
        prev->next = next;
        --length;
    }

    LinkedList<T> Concat(LinkedList<T> &list) {
        LinkedList<T> res;
        for (int i = 0; i < length; ++i) {
            res.Append(this->At(i));
        }
        for (int i = 0; i < list.length; ++i) {
            res.Append(list[i]);
        }
        return res;
    }

    LinkedList<T> &operator=(const LinkedList<T> &list) {
        this->~LinkedList();
        if (list.length > 0) {
            node *tmp = list.head;
            head = CreateNode(tmp->data);
            node *prev = head;
            tmp = tmp->next;
            while (tmp != NULL) {
                prev->next = CreateNode(tmp->data);
                prev = prev->next;
                tmp = tmp->next;
            }
            tail = prev;
            length = list.length;
        } else {
            head = nullptr;
            tail = nullptr;
            length = 0;
        }
        return *this;
    }

    //Termination
    ~LinkedList() {
        while (length)
            PopFirst();
    }
};




