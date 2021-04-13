//
// Created by korna on 03.04.2021.
//
#include "IEnumerable.h"
#include "ICollection.h"

#ifndef LABA2_COLLECTION_H
#define LABA2_COLLECTION_H

template<class T>
/*abstract*/
class Enumerable : public IEnumerable<T>, public ICollection<T> {
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


    Enumerable<T> *Zip(T (*mapper)(T)) {
        Enumerable<Enumerable<T>> *res = this->Init(Enumerable<T>);
        for (int i = 0; i < this->GetLength(); i++)
            res->At(i) = mapper(this->At(i));
        return res;
    };

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
