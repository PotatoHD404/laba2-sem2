//
// Created by korna on 11.04.2021.
//
#ifndef TEST_DB_TESTCLASS_H
#define TEST_DB_TESTCLASS_H

#include "Enumerable.h"



template<class T>
class TestClass : public Collection<T> {
public:
    TestClass &Map(T (*mapper)(T), TestClass collection) override {

        Collection<T>::Map(mapper, collection, collection);
    }

    virtual ~TestClass() {};

};

#endif //TEST_DB_TESTCLASS_H