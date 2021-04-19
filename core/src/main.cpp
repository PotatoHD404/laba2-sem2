//
// Created by korna on 19.03.2021.
//

#include <iostream>
#include "ArraySequence.h"
#include "ListSequence.h"
//#include "Enumerable.cpp"


using namespace std;


int main() {
    ListSequence<int> arr = {11, 12, 3, 4, -5};
    auto[a, b] = arr.Split(0);
    for (int i = 0; i < b->GetLength(); ++i) {
        cout << b->At(i) << endl;
    }
    delete a;
    delete b;


    return 0;
}