//
// Created by korna on 19.03.2021.
//

#include <iostream>
#include <sstream>
#include "ArraySequence.h"
#include "ListSequence.h"
//#include "Enumerable.cpp"


using namespace std;


const char *MSGS[] = {"0. Quit",
                      "1. Input polynomial",
                      "2. Multiply polynomial",
                      "3. Sum polynomial",
                      "4. Print string",
                      "5. Concat a and b",
                      "6. Find string b in string a",
                      "7. Run tests",
                      "8. Clear error log",
                      "9. Delete strings"};
const char *MSGS1[] = {"0. Quit", "1. Poly a", "2. Poly b"};
//const char *MSGS2[] = {"0. Quit", "1. With case", "2. Without case"};


template<int N>
int Dialog(const char *(&msgs)[N]) {
    string error;
    int choice = -1;
    do {
        cout << error;
        error = "You're wrong. Try again!\n";
        for (int i = 0; i < N; ++i) {
            cout << msgs[i] << endl;
        }
        cout << "Make your choice: \n";
        cin >> choice;
    } while (choice < 0 || choice >= N);
    return choice;
}

template<typename T>
T ReadFromString(const string &str) {
    stringstream ss(str);
    T t;
    ss >> t;
    if (ss.fail())
        throw std::runtime_error("Cannot read string");
    return t;
}

string ReadFromString(const string &str) {
    return str;
}
template<typename T>
void StartUI() {
    int res = 1;
    string tmp;
    while (res != 0) {
        res = Dialog(MSGS);
        switch (res) {
            case 0:
                break;
            case 1:
                res = Dialog(MSGS1);
                cin >> tmp;
                try {
                    T input = ReadFromString(tmp);
                }
                catch (exception){

                }
                break;
            default:
                printf("How did you end up here?\n");
                break;
        }
    }
}


int main() {
//    StartUI();


    return 0;
}