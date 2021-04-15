//
// Created by korna on 03.04.2021.
//
#include "IEnumerable.h"
#include "ICollection.h"
#include <vector>
#include <tuple>
#include <iostream>
//#include <variant>

using namespace std;


#ifndef LABA2_COLLECTION_H
#define LABA2_COLLECTION_H

template<class T>
/*abstract*/
class Enumerable : public IEnumerable<T>, public ICollection<T> {
private:
    template<typename... Args, template<class> class Current, class ElType>
    static auto CreateVector(Current<ElType> _) {
        vector<tuple<Args..., ElType>> res;
        return res;
    }

    template<typename... Args, typename... Ts, typename Current>
    static auto Zip(vector<tuple<Ts...>> &res, int min, Current current, Args... args) {
        int count = current.GetLength();
        auto res2 = CreateVector<Ts...>(current);;
        if (min > count)
            min = count;
        for (int i = 0; i < min; i++)
            res2.push_back(tuple_cat(res.at(i), make_tuple(current[i])));

        return Zip(res2, min, args...);
    }


    template<typename... Args, typename... Ts, typename Current>
    static auto Zip(vector<tuple<Ts...>> &res, int min, Current current) {
        int count = current.GetLength();
        auto res2 = CreateVector<Ts...>(current);
        if (min > count)
            min = count;
        for (int i = 0; i < min; i++)
            res2.push_back(tuple_cat(res.at(i), make_tuple(current[i])));
        res2.resize(min);
        return res2;
    }


public:
    Enumerable() {}

    auto Split(int point) {
        auto res = make_tuple(this->Subsequence(0, point), this->Subsequence(point, this->GetLength()));
        return res;
    }

    bool Contains(T item) {
        for (int i = 0; i < this->GetLength(); ++i)
            if (this->At(i) == item)
                return true;
        return false;
    }

    virtual Enumerable<T> *Subsequence(int begin, int end) = 0;

    Enumerable<T> *Where(bool(*predicate)(T)) {
        Enumerable<T> *res = this->Init();
        for (int i = 0; i < this->GetLength(); i++)
            if (predicate(this->At(i)))
                res->Append(this->At(i));
        return res;
    }

    T Reduce(T(*f)(T, T), T const c) {
        T res = c;
        for (int i = 0; i < this->GetLength(); ++i) {
            res = f(this->At(i), res);
        }
        return res;
    }

    Enumerable<T> *Map(T (*mapper)(T)) {
        Enumerable<T> *res = this->Init(this->GetLength());
        for (int i = 0; i < this->GetLength(); i++)
            res->At(i) = mapper(this->At(i));
        return res;
    }


    template<typename... Args, class Current>
    static auto Zip(Current current, Args... args) {
        const int count = current.GetLength();
        auto res = CreateVector<>(current);
        for (int i = 0; i < count; i++)
            res.push_back(make_tuple(current[i]));

        return Zip(res, count, args...);
    }
    template<template<typename> typename ChildClass, int num, typename... Args, class Current>
    static auto UnZip(vector<tuple<Current>> &input, Args... args) {
        int length = input.size();
        auto res = ChildClass<Current>(length);
        for (int i = 0; i < length; i++)
            res.Append(get<num>(input.at(i)));


        return make_tuple(res, args...);

    }

    template<template<typename> typename ChildClass, int num, class Current,typename... Ts,typename... Args,  typename... Ts1>
    static auto UnZip(vector<tuple<Ts1...>> &input, Args... args) {
        int length = input.size();
        auto res = ChildClass<Current>();
        for (int i = 0; i < length; i++)
            res.Append(get<num>(input.at(i)));

        if
        constexpr (sizeof...(Ts) == 0)
            return make_tuple(args..., res);
        else
            return UnZip<ChildClass, num + 1,Ts...>(input, args..., res);
    }

    template<template<typename> typename ChildClass, typename... Args, class Current, typename... Ts>
    static auto UnZip(vector<tuple<Current, Ts...>> input, Args... args) {
        int length = input.size();
        auto res = ChildClass<Current>();
        for (int i = 0; i < length; i++)
            res.Append(get<0>(input.at(i)));

        if
        constexpr (sizeof...(Ts) == 0)
            return make_tuple(res, args...);
        else
            return UnZip<ChildClass, 1,Ts...>(input, args..., res);
    }




    virtual ~Enumerable() {};

};


#endif //LABA2_COLLECTION_H
