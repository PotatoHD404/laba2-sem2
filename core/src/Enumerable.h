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


public:
    Enumerable() {}

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



//    template<class ChildType>
//    auto Init(ChildType *tmp) { return ChildType(); };


//public:
//    template<typename Current>
//    auto Zip(Current current) {
//        auto ahahnt = this->Init(*this);
//        tuple<Current> curr(ahahnt);
//        for (int i = 0; i < this->GetLength(); i++)
//            get<0>(curr); //.Append(this->At(i))
//        return Zip(curr, this->GetLength(), current);
//    }


    virtual ~Enumerable() {};

};

template<typename... Args, typename Current>
auto Zip(Current current, Args... args) {
    tuple<Current> res((Current()));
    int count = current.GetLength();
    for (int i = 0; i < count; i++)
        get<0>(res).Append(current[i]);
    return Zip(res, count, args...);
}

template<typename... Args, typename Tuple, typename Current>
auto Zip(Tuple res, int min, Current current, Args... args) {
    int count = current.GetLength();
    tuple<Current> curr((Current()));
    auto res2 = tuple_cat(res, curr);
    if (min > count)
        min = count;
    for (int i = 0; i < min; i++)
        get<tuple_size<decltype(res)>::value>(res2).Append(current.At(i));

    return Zip(res2, min, args...);
}


template<size_t I = 0, typename... Ts>
constexpr void Foreach(tuple<Ts...> &tup, int min) {
    // If we have iterated through all elements
    if
    constexpr(I == sizeof...(Ts)) {
        // Last case, if nothing is left to
        // iterate, then exit the functiopn
        return;
    } else {
        int count = get<I>(tup).GetLength();
        while (count-- > min) get<I>(tup).RemoveAt(count);

        // Going for next element.
        Foreach<I + 1, Ts...>(tup, min);
    }
}

//template<int i = 0, typename... Ts>
//void Foreach(tuple<Ts...> tup, int min) {
//    // If we have iterated through all elements
//    cout << i << endl;
//    if (i == sizeof...(Ts)) {
//        // Last case, if nothing is left to
//        // iterate, then exit the functiopn
//        return;
//    } else {
//        // Print the tuple and go to next element
////        cout << get<i>(tup) << " ";
////        int count = get<i>(tup).GetLength();
////        cout << count << " " << min << endl;
////        while (count-- > min) get<i>(tup).RemoveAt(count);
////        cout << count << endl;
////        get<i>(tup) = el;
//
//        // Going for next element.
//        Foreach<i + 1, Ts...>(tup, min);
//    }
//}


template<typename Tuple, typename Current>
auto Zip(Tuple res, int min, Current current) {
    int count = current.GetLength();
    tuple<Current> curr((Current()));
//        int len =
    auto res2 = tuple_cat(res, curr);
    if (min > count)
        min = count;
    for (int i = 0; i < min; i++)
        get<tuple_size<decltype(res)>::value>(res2).Append(current.At(i));

    Foreach(res2, min);
//    for (int i = 0; i < tuple_size<decltype(res)>::value; ++i)
//        Resize(get<i>(res2), min);

    return res2;
}
//
// Created by korna on 15.04.2021.
//

//template<typename... Args, typename Tuple, typename Current>
//auto Zip(Tuple res, int min, Current current, Args... args);
//
//template<int i = 0, typename... Ts>
//void Foreach(tuple<Ts...> tup, int min);
//
//template<class T>
//void Resize(Enumerable<T> *enumerable, int len);
//
//template<typename Tuple, typename Current>
//auto Zip(Tuple res, int min, Current current);

#endif //LABA2_COLLECTION_H
