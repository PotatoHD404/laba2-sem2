//
// Created by korna on 03.04.2021.
//
#include "IEnumerable.h"

#ifndef LABA2_COLLECTION_H
#define LABA2_COLLECTION_H

template<class T>
class Collection : public IEnumerable<T>, public ICollection<T> {
public:

    virtual void Map(T (*mapper)(T), Collection collection, Collection &res) {

    };

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
