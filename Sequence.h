//
// Created by korna on 20.03.2021.
//

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