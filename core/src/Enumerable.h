//
// Created by korna on 03.04.2021.
//
#ifndef LABA2_ENUMERABLE_H
#define LABA2_ENUMERABLE_H

#include "IEnumerable.h"
#include "ICollection.h"
#include <vector>
#include <tuple>
#include <iostream>
//#include <variant>

using namespace std;

template<class T>
/*abstract*/
class Enumerable : public IEnumerable<T>, public ICollection<T> {
private:

    template<typename Base, typename T1>
    inline constexpr static bool instanceof(const T1 *) {
        return is_base_of<Base, T1>::value;
    }

    template<typename ElType, template<typename> class Child>
    static constexpr bool IsBadType(Child<ElType> *x) {
        return !instanceof<ICollection<ElType>>(x);
    }

    template<typename... Args, typename... Ts, template<typename> class Current, typename ElType>
    static auto Zip(vector<tuple<Ts...>> &res, int min, Current<ElType> current, Args... args) {
        if constexpr (static_cast<ICollection<ElType> *>(&current) == nullptr)
            throw std::runtime_error("Wrong type");
        else {
            int count = current.GetLength();
            vector<tuple<Ts..., ElType>> res2;
            if (min > count)
                min = count;
            for (int i = 0; i < min; i++)
                res2.push_back(tuple_cat(res.at(i), make_tuple(current[i])));
            if constexpr (sizeof...(Args) == 0) {
                res2.resize(min);
                return res2;
            } else
                return Zip(res2, min, args...);
        }
    }

    template<template<typename> typename ChildClass, int num, class Current, typename... Ts, typename... Args, typename... Ts1>
    static auto UnZip(vector<tuple<Ts1...>> &input, Args... args) {
        int length = input.size();
        auto res = ChildClass<Current>();
        for (int i = 0; i < length; i++)
            res.Append(get<num>(input.at(i)));

        if constexpr (sizeof...(Ts) == 0)
            return make_tuple(args..., res);
        else
            return UnZip<ChildClass, num + 1, Ts...>(input, args..., res);
    }

protected:

    template<typename T1, template<typename> class ChildClass>
    Enumerable<T1> *Map(T1 (*mapper)(T)) {
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        int length = this->GetLength();
        Enumerable<T1> *res = new ChildClass<T1>(length);
        for (int i = 0; i < length; i++)
            res->At(i) = mapper(this->At(i));
        return res;
    }

    template<template<typename> class ChildClass>
    Enumerable<T> *Where(bool(*predicate)(T)) {
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Enumerable<T> *res = new ChildClass<T>();
        for (int i = 0; i < this->GetLength(); i++)
            if (predicate(this->At(i)))
                res->Append(this->At(i));
        return res;
    }

public:
    Enumerable() {}

    auto Split(int point) {
        auto res = make_tuple(this->Subsequence(0, point), this->Subsequence(point + 1, this->GetLength() - 1));
        return res;
    }

    bool Contains(T item) {
        for (int i = 0; i < this->GetLength(); ++i)
            if (this->At(i) == item)
                return true;
        return false;
    }

    virtual Enumerable<T> *Subsequence(int begin, int end) = 0;

    T Reduce(T(*f)(T, T), T const c) {
        if (f == nullptr)
            throw std::invalid_argument("mapper is NULL");
        T res = c;
        for (int i = 0; i < this->GetLength(); ++i) {
            res = f(this->At(i), res);
        }
        return res;
    }


    template<typename... Args, template<typename> class Current, typename ElType>
    static auto Zip(Current<ElType> current, Args... args) {
        if constexpr(IsBadType(&current))
            throw std::runtime_error("Wrong type");
        else {
            const int count = current.GetLength();
            vector<tuple<ElType>> res;
            for (int i = 0; i < count; i++)
                res.push_back(make_tuple(current[i]));

            return Zip(res, count, args...);
        }

    }

    template<template<typename> typename ChildClass, typename... Args, typename Current, typename... Ts>
    static auto UnZip(vector<tuple<Current, Ts...>> input, Args... args) {
        int length = input.size();
        if (length == 0)
            throw std::runtime_error("Wrong size of input vector");
        auto res = ChildClass<Current>();
        for (int i = 0; i < length; i++)
            res.Append(get<0>(input.at(i)));

        if constexpr (sizeof...(Ts) == 0)
            return make_tuple(res, args...);
        else
            return UnZip<ChildClass, 1, Ts...>(input, args..., res);
    }


    virtual ~Enumerable() {};
};


#endif //LABA2_ENUMERABLE_H