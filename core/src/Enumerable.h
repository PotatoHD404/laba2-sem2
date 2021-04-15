//
// Created by korna on 03.04.2021.
//
#include "IEnumerable.h"
#include "ICollection.h"
#include <tuple>
#include <iostream>

using namespace std;


#ifndef LABA2_COLLECTION_H
#define LABA2_COLLECTION_H

template<class T>
/*abstract*/
class Enumerable : public IEnumerable<T>, public ICollection<T> {
private:
    template<typename... Args, typename... Ts, typename Current>
    static auto Zip(tuple<Ts...> res, int min, Current current, Args... args) {
        int count = current.GetLength();
        tuple<Current> curr((Current()));
        auto res2 = tuple_cat(res, curr);
        if (min > count)
            min = count;
        for (int i = 0; i < min; i++)
            get<sizeof...(Ts)>(res2).Append(current.At(i));

        return Zip(res2, min, args...);
    }


    template<size_t i = 0, typename... Ts>
    static constexpr void Foreach(tuple<Ts...> &tup, int min) {
        // If we have iterated through all elements
        if
        constexpr(i == sizeof...(Ts)) {
            // Last case, if nothing is left to
            // iterate, then exit the function
            return;
        } else {
            int count = get<i>(tup).GetLength();
            while (count-- > min) get<i>(tup).RemoveAt(count);

            // Going for next element.
            Foreach<i + 1, Ts...>(tup, min);
        }
    }


    template<typename... Ts, typename Current>
    static auto Zip(tuple<Ts...> res, int min, Current current) {
        int count = current.GetLength();
        tuple<Current> curr((Current()));
        auto res2 = tuple_cat(res, curr);
        if (min > count)
            min = count;
        for (int i = 0; i < min; i++)
            get<sizeof...(Ts)>(res2).Append(current.At(i));

        Foreach(res2, min);

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


    template<typename... Args, typename Current>
    static auto Zip(Current current, Args... args) {
        tuple<Current> res((Current()));
        int count = current.GetLength();
        for (int i = 0; i < count; i++)
            get<0>(res).Append(current[i]);
        return Zip(res, count, args...);
    }


    virtual ~Enumerable() {};

};


#endif //LABA2_COLLECTION_H
