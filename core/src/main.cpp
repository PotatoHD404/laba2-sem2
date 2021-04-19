//
// Created by korna on 19.03.2021.
//

#include <iostream>
#include "ArraySequence.h"
#include "ListSequence.h"
//#include "Enumerable.cpp"


using namespace std;


int main() {
//    ListSequence<int> a = ListSequence<int>();
//    ListSequence<float> b = ListSequence<float>();
//    a.Append(0);
//    a.Append(1);
//    a.Append(2);
//    b.Append(3.14);
//    b.Append(2.1);
//
//    auto lulw = Zip(a, b);
//    cout << get<0>(lulw).At(1) << endl;
//    ArraySequence<int> a = ArraySequence<int>();

    ArraySequence<int> a = ArraySequence<int>();
    ArraySequence<float> b = ArraySequence<float>();
    ArraySequence<float> c = ArraySequence<float>();
    ArraySequence<double> d = ArraySequence<double>();
    d.Append(0.1);
    a.Append(0);
    a.Append(1);
    a.Append(2);
    b.Append(3.14);
    b.Append(2.1);


    auto res = ArraySequence<int>::Zip(a, b);
//    auto[d, e] = ArraySequence<int>::UnZip<ArraySequence>(lulw);
//    cout << e.At(1) << endl;
    cout << b.At(0) << endl;
//    ArraySequence<int> a = ArraySequence<int>();
//    a.Append(0);
//    a.Append(1);
//    a.Append(2);
//
//    IEnumerator<int> *enumerator = a.GetEnumerator();
//    cout << enumerator->GetCurrent() << " " << enumerator->MoveNext() << " " << enumerator->GetCurrent() << endl;
//    enumerator->MoveNext();
//    cout << enumerator->MoveNext() << " " << enumerator->GetCurrent() << endl;
//    enumerator->Reset();
//    cout << enumerator->GetCurrent() << endl;

    return 0;
}