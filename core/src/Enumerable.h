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
    };

    template<typename... Args>
    auto Zip(Args... args) {
        auto res = make_tuple(this->Init());
        int len = 0;
        for (int i = 0; i < this->GetLength(); i++)
            res->At(len).Append(this->At(i));
        return Zip(res, args...);
    };

    template<typename... Args>
    auto Zip(Enumerable<Enumerable<T>> *res, Enumerable<T> current, Args... args) {
        int count = current->GetLength();
        int len = res->GetLength();
        res->Append(this->Init());
        for (int i = 0; i < this->GetLength(); i++)
            res->At(len).Append(current->At(i));
        for (int i = 0; i < len; ++i)
            Resize(res->At(i), count);
        Zip(res, args...);
    };

    void Zip(Enumerable<Enumerable<T>> *res, Enumerable<T> current) {

        int count = current->GetLength();
        int len = res->GetLength();
        res->Append(this->Init());
        for (int i = 0; i < this->GetLength(); i++)
            res->At(len).Append(current->At(i));
        for (int i = 0; i < len; ++i)
            Resize(res->At(i), count);
    };

//    template<typename... Args>
//    Enumerable<T> *Zip(Args... args) {
//        Enumerable<Enumerable<T>> *res = this->InitEnumerable();
//        int len = res->GetLength();
//        res->Append(this->Init());
//        for (int i = 0; i < this->GetLength(); i++)
//            res->At(len).Append(this->At(i));
//        Zip(res, args...);
//        return res;
//    };
//
//    template<typename... Args>
//    void Zip(Enumerable<Enumerable<T>> *res, Enumerable<T> current, Args... args) {
//        int count = current->GetLength();
//        int len = res->GetLength();
//        res->Append(this->Init());
//        for (int i = 0; i < this->GetLength(); i++)
//            res->At(len).Append(current->At(i));
//        for (int i = 0; i < len; ++i)
//            Resize(res->At(i), count);
//        Zip(res, args...);
//    };
//
//    void Zip(Enumerable<Enumerable<T>> *res, Enumerable<T> current) {
//
//        int count = current->GetLength();
//        int len = res->GetLength();
//        res->Append(this->Init());
//        for (int i = 0; i < this->GetLength(); i++)
//            res->At(len).Append(current->At(i));
//        for (int i = 0; i < len; ++i)
//            Resize(res->At(i), count);
//    };



//    template <typename Function, typename Iterator, typename ... Iterators>
//    Function zip (Function func, Iterator begin,
//                  Iterator end,
//                  Iterators ... iterators)
//    {
//        for(;begin != end; ++begin, advance_all(iterators...))
//            func(*begin, *(iterators)... );
//        //could also make this a tuple
//        return func;
//    }

//    int main () {
//        std::vector<int> v1{1,2,3};
//        std::vector<int> v2{3,2,1};
//        std::vector<float> v3{1.2,2.4,9.0};
//        std::vector<float> v4{1.2,2.4,9.0};
//        zip (
//                [](int i,int j,float k,float l){
//                    std::cout << i << " " << j << " " << k << " " << l << std::endl;
//                },
//                v1.begin(),v1.end(),v2.begin(),v3.begin(),v4.begin());
//    }

//    template<typename IteratorA, typename IteratorB, typename Zipper, typename P>
//    void Zip(IteratorA a, IteratorA aEnd, IteratorB b, IteratorB bEnd, Zipper zipper, vector<P>& ret) {
//        if (a == aEnd || b == bEnd) return;
//        ret.push_back(zipper(*a, *b));
//        zip(++a, aEnd, ++b, bEnd, zipper, ret);
//    }
//    template<typename IteratorA, typename IteratorB, typename Zipper, typename P>
//    void UnZip(IteratorA a, IteratorA aEnd, IteratorB b, IteratorB bEnd, Zipper zipper, vector<P>& ret) {
//        if (a == aEnd || b == bEnd) return;
//        ret.push_back(zipper(*a, *b));
//        zip(++a, aEnd, ++b, bEnd, zipper, ret);
//    }
//    template<typename IteratorA, typename IteratorB, typename Zipper, typename P>
//    void Reduce(IteratorA a, IteratorA aEnd, IteratorB b, IteratorB bEnd, Zipper zipper, vector<P>& ret) {
//        if (a == aEnd || b == bEnd) return;
//        ret.push_back(zipper(*a, *b));
//        zip(++a, aEnd, ++b, bEnd, zipper, ret);
//    }
//    template<typename IteratorA, typename IteratorB, typename Zipper, typename P>
//    void Split(IteratorA a, IteratorA aEnd, IteratorB b, IteratorB bEnd, Zipper zipper, vector<P>& ret) {
//        if (a == aEnd || b == bEnd) return;
//        ret.push_back(zipper(*a, *b));
//        zip(++a, aEnd, ++b, bEnd, zipper, ret);
//    }
//    TODO: where, concat, subsequence, zip/unzip, reduce, split
//    void Where(IteratorA a, IteratorA aEnd, IteratorB b, IteratorB bEnd, Zipper zipper, vector<P>& ret) {
//        if (a == aEnd || b == bEnd) return;
//        ret.push_back(zipper(*a, *b));
//        zip(++a, aEnd, ++b, bEnd, zipper, ret);
//    }
//    void Concat(IteratorA a, IteratorA aEnd, IteratorB b, IteratorB bEnd, Zipper zipper, vector<P>& ret) {
//        if (a == aEnd || b == bEnd) return;
//        ret.push_back(zipper(*a, *b));
//        zip(++a, aEnd, ++b, bEnd, zipper, ret);
//    }
//    void Subsequence(IteratorA a, IteratorA aEnd, IteratorB b, IteratorB bEnd, Zipper zipper, vector<P>& ret) {
//        if (a == aEnd || b == bEnd) return;
//        ret.push_back(zipper(*a, *b));
//        zip(++a, aEnd, ++b, bEnd, zipper, ret);
//    }



    virtual ~Enumerable() {};

};

#endif //LABA2_COLLECTION_H
