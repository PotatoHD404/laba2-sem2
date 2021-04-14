//
// Created by korna on 19.03.2021.
//

#include <iostream>
#include "ListSequence.h"

using namespace std;


int main() {
    ListSequence<int> *a = new ListSequence<int>();
    ListSequence<float> *b = new ListSequence<float>();
    a->Append(0);
    b->Append(3.14);

    auto lulw = a->Zip(b);

    return 0;
}
