//
// Created by korna on 03.04.2021.
//
#include "IEnumerator.h"

#ifndef LABA2_IENUMERABLE_H
#define LABA2_IENUMERABLE_H

template<class T>
class IEnumerable {
public:
    virtual IEnumerator<T> &GetEnumerator() = 0;

    virtual ~IEnumerable() {};

};

#endif //LABA2_IENUMERABLE_H
