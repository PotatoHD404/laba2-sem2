//
// Created by korna on 03.04.2021.
//

#ifndef LABA2_ICOLLECTION_H
#define LABA2_ICOLLECTION_H

template<class T>
class ICollection {
public:
    bool IsReadOnly;
    int Count;

    virtual ICollection(const ICollection<T> &iCollection) = 0;

    //Decomposition

    virtual T &At(int index) = 0;

    virtual int GetLength() = 0;

    virtual bool Contains (T item) = 0;

    virtual void CopyTo (T[] array, int arrayIndex) = 0;

    //Operations
    virtual void Clear () = 0;

    virtual void Append(T item) = 0;

    virtual void RemoveAt(int index) = 0;

    virtual ~ICollection() {};

};

#endif //LABA2_ICOLLECTION_H
