//
// Created by korna on 03.04.2021.
//
#include "IEnumerable.h"
#include "ICollection.h"
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;


#ifndef LABA2_COLLECTION_H
#define LABA2_COLLECTION_H

template<class T>
/*abstract*/
class Enumerable : public IEnumerable<T>, public ICollection<T> {
private:
    template<typename... Args, typename... Ts, template<typename> typename Current, typename ElType>
    static auto _zip(vector<tuple<Ts...>> &res, int min, Current<ElType> current, Args... args) {
        int count = current.GetLength();
        vector<tuple<ElType, Ts...>> res2;
        if (min > count)
            min = count;
        for (int i = 0; i < min; i++)
            res2.push_back(tuple_cat(res.at(i), make_tuple(current[i])));

        return Zip(res2, min, args...);
    }

    template<typename... Ts, template<typename> typename Current, typename ElType>
    static auto _zip(tuple<tuple<Ts...>> &res, int min, Current<ElType> current) {
        int count = current.GetLength();
        vector<tuple<ElType, Ts...>> res2;
        if (min > count)
            min = count;
        for (int i = 0; i < min; i++)
            res2.push_back(tuple_cat(res.at(i), make_tuple(current[i])));

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


    template<typename... Args, template<typename ElType> typename Current, typename ElType>
    static auto Zip(Current<ElType> current, Args... args) {
        const int count = current.GetLength();
        vector<tuple<ElType>> res;
        for (int i = 0; i < count; i++) {
            res.push_back(make_tuple(current[i]));
        }
        return _zip(res, count, args...);
    }


    virtual ~Enumerable() {};

};


#endif //LABA2_COLLECTION_H
