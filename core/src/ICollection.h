//
// Created by korna on 03.04.2021.
//

#ifndef LABA2_ICOLLECTION_H
#define LABA2_ICOLLECTION_H

template<class T>
class ICollection {
protected:
//    bool ReadOnly;
public:
    ICollection() {}

    virtual ICollection<T> *Clone() const = 0;

    virtual ICollection<T> *Init() const = 0;

    virtual ICollection<T> *Init(int count) const = 0;

    //Decomposition

    virtual T &At(int index) = 0;

    virtual int GetLength()  = 0;

//    bool IsReadOnly() { return ReadOnly; }

    virtual bool Contains(T item) = 0;

    //Operations
    virtual void Clear() = 0;

    virtual void Append(T item) = 0;

    virtual void RemoveAt(int index) = 0;

    virtual ~ICollection() {};

};

#endif //LABA2_ICOLLECTION_H
