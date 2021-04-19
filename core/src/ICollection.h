//
// Created by korna on 03.04.2021.
//

#ifndef LABA2_ICOLLECTION_H
#define LABA2_ICOLLECTION_H

template<class T>
class ICollection {
public:
    ICollection() {}

    //Decomposition

    virtual T &At(int index) = 0;

    virtual int GetLength() = 0;

    virtual bool Contains(T item) = 0;

    //Operations
    virtual void Clear() = 0;

    virtual void Append(T item) = 0;

    virtual void RemoveAt(int index) = 0;

    virtual ~ICollection() = default;
};

#endif //LABA2_ICOLLECTION_H