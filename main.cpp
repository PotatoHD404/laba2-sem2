#include <iostream>

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
        return GetNode(index)->data;
    }

    LinkedList<T> *GetSubList(int startIndex, int endIndex) {
        LinkedList<T> *res = new LinkedList<T>[1];
        *res = LinkedList();
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

};


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
    T At(int index) {
        if (index < 0 || index >= length)
            throw out_of_range("");
        return actual_array[index];
    }

    void Set(int index, T value) {
        if (index < 0 || index >= length)
            throw range_error("");
        this[index] = value;
    }

    unsigned int GetLength() { return length; }

    T &operator[](unsigned int index) { return At(index); }

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

template<class T>
class Sequence {
public:
    Sequence();

    Sequence(T *items, int count);

    Sequence(const LinkedList<T> &list);

    T GetFirst();

    T GetLast();

    T Get(int index);

    Sequence<T> *GetSubsequence(int startIndex, int endIndex);

    int GetLength();

    void Append(T item);

    void Prepend(T item);

    void InsertAt(T item, int index);

    Sequence<T> *Concat(Sequence<T> *list);
};

template<class T>
class ArraySequence : Sequence<T> {

};

template<class T>
class LinkedListSequence : Sequence<T> {

};


int main() {
    cout << "Hello, World!" << endl;

    return 0;
}
