//
// Created by korna on 03.04.2021.
//
#include "IEnumerable.h"

#ifndef LABA2_COLLECTION_H
#define LABA2_COLLECTION_H

template<class T>
class Collection : public IEnumerable<T>, public ICollection<T> {
public:

    template<class ChildClass>
    ChildClass& Map(T (*mapper)(T), ChildClass collection) {
        ChildClass res = ChildClass(collection.GetLength());
        for (int i = 0; i < collection.GetLength(); i++)
            res[i] = mapper(collection[i]);
        return res;
    };

//    template <typename Iterator>
//    void advance_all (Iterator & iterator) {
//        ++iterator;
//    }
//    template <typename Iterator, typename ... Iterators>
//    void advance_all (Iterator & iterator, Iterators& ... iterators) {
//        ++iterator;
//        advance_all(iterators...);
//    }
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



    virtual ~Collection() {};

};

#endif //LABA2_COLLECTION_H
