//
// Created by korna on 03.04.2021.
//
#include "IEnumerable.h"
#include "ICollection.h"
#include <tuple>

#ifndef LABA2_COLLECTION_H
#define LABA2_COLLECTION_H

template<class T>
/*abstract*/
class Enumerable : public IEnumerable<T>, public ICollection<T> {
private:
    void Resize(Enumerable<T> *enumerable, int len) {
        int count = enumerable->GetLength();
        while (count-- > len) enumerable->RemoveAt(count);
        while (count++ < len) enumerable->Append(T());
    }

public:
    auto Split(int point) {
        auto res = make_tuple(this->Subsequence(0, point), this->Subsequence(point, this->GetLength()));
        return res;
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

    template<typename... Args>
    auto Zip(Args... args) {
        auto res = make_tuple(this->Init());
        int len = 0;
        for (int i = 0; i < this->GetLength(); i++)
            get<len>(res).Append(this->At(i));
        return Zip(res, this->GetLength(), args...);
    }

    template<typename... Args, typename Tuple>
    auto Zip(Tuple res, int min, Enumerable<T> current, Args... args) {
        int count = current->GetLength();
        int len = res->GetLength();
        auto res2 = tuple_cat(res, make_tuple(this->Init()));
        res->Append(this->Init());
        for (int i = 0; i < this->GetLength(); i++)
            get<len>(res2).Append(current->At(i));
        if (min > count)
            min = count;
        return Zip(res2, min, args...);
    }

    template<typename Tuple>
    auto Zip(Tuple res, int min, Enumerable<T> current) {
        int count = current->GetLength();
        int len = res->GetLength();
        auto res2 = tuple_cat(res, make_tuple(this->Init()));
        for (int i = 0; i < this->GetLength(); i++)
            get<len>(res2).Append(current->At(i));
        if (min > count)
            min = count;
        for (int i = 0; i < len; ++i)
            Resize(get<len>(res2), min);

        return res2;
    }

    auto Zip(Enumerable<T> current) {
        auto res = make_tuple(this->Init());
        int len = 0;
        for (int i = 0; i < this->GetLength(); i++)
            get<len>(res).Append(this->At(i));
        return Zip(res, this->GetLength(), current);
    }


    virtual ~Enumerable() {};

}

#endif //LABA2_COLLECTION_H
