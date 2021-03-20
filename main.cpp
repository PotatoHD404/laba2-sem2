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
    //Decomposition
    virtual T GetFirst() { return At(0); }

    virtual T GetLast() { return At(GetLength() - 1); }

    virtual T At(int index) = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    virtual int GetLength() = 0;

    //Operations
    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(T item, int index) = 0;

    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;
};

template<class T>
class ArraySequence : Sequence<T> {

private:
    DynamicArray<T> *items;

public:
    //Creation of the object
    ArraySequence() {
        items(new DynamicArray<T>());
    }

    ArraySequence(T *items, int count) {
        items(new DynamicArray<T>(items, count));
    }

    explicit ArraySequence(const DynamicArray<T> &list) {
        items(new DynamicArray<T>(list));
    }

    //Decomposition

    T At(int index) {
        return items->At(index);
    }

    Sequence<T> *GetSubsequence(int startIndex, int endIndex) {
        ArraySequence<T> *res;
        res(new ArraySequence<T>);
        for (int i = startIndex; i < endIndex; ++i) {
            res->Append(items->At(i));
        }
        return res;
    }

    int GetLength() {
        return items->GetLength();
    }


    //Operations
    void Append(T item) {
        items->Resize(items->GetLength() + 1);
        items->Set(items->GetLength() - 1, item);
    }

    void Prepend(T item) {
        items->Resize(items->GetLength() + 1);
        for (int i = items->GetLength() - 1; i > 0; --i) {
            items->Set(i, items->At(i - 1));
        }
        items->Set(0, item);
    }

    void InsertAt(T item, int index) {
        items->Resize(items->GetLength() + 1);
        for (int i = items->GetLength() - 1; i > index; --i) {
            items->Set(i, items->At(i - 1));
        }
        items->Set(index, item);
    }

    Sequence<T> *Concat(Sequence<T> *list) {
        ArraySequence<T> *res;
        res(new ArraySequence<T>);
        for (int i = 0; i < items->GetLength(); ++i) {
            res->Append(items->At(i));
        }
        for (int i = 0; i < list->items->GetLength(); ++i) {
            res->Append(list->items->At(i));
        }
        return res;
    }

    //Termination
    ~ArraySequence() {
        delete *items;
        delete[] items;
    }
};

template<class T>
class LinkedListSequence : Sequence<T> {
private:
    LinkedList<T> *items;

public:
    //Creation of the object
    LinkedListSequence() {
        items(new LinkedList<T>());
    }

    LinkedListSequence(T *items, int count) {
        items(new LinkedList<T>(items, count));
    }

    explicit LinkedListSequence(const LinkedList<T> &list) {
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


int main() {
    cout << "Hello, World!" << endl;

    return 0;
}
