//
// Created by korna on 20.03.2021.
//

template<class T>
class Sequence {
public:

    //Decomposition
    T &GetFirst() { return At(0); }

    T &GetLast() { return At(GetLength() - 1); }

    void Set(int index, T value) {
        At(index) = value;
    }

    virtual T &At(int index) = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    virtual int GetLength() = 0;

    T &operator[](unsigned int index) { return At(index); }

    //Operations
    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(T item, int index) = 0;

    virtual void PopFirst() = 0;

    virtual void PopLast() = 0;

    virtual void RemoveAt(int index) = 0;

    virtual Sequence<T> *Concat(Sequence<T> &list) = 0;

    virtual ~Sequence() {};

};