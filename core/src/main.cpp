//
// Created by korna on 19.03.2021.
//

#include <iostream>
#include <sstream>
#include "Polynomial.h"
#include "Complex.h"
//#include "ListSequence.h"
//#include "Enumerable.cpp"


using namespace std;


const char *MSGS[] = {"0. Quit",
                      "1. Input polynomial",
                      "2. Multiply polynomials",
                      "3. Multiply polynomial on scalar",
                      "4. Sum polynomials"};
const char *MSGS1[] = {"0. Quit", "1. Poly a", "2. Poly b"};

const char *MSGS2[] = {"0. Quit", "1. Int", "2. Float", "3. Complex"};
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
void StartUI() {
    int res = 1;
    string tmp;
    Polynomial<T> polyA;
    Polynomial<T> polyB;
    while (res != 0) {
        res = Dialog(MSGS);
        switch (res) {
            case 0:
                break;
            case 1:
                res = Dialog(MSGS1);
                if (res == 0)
                    break;
                else if (res == 1) {
                    getline(cin, tmp);
                    try {
                        stringstream ss(tmp);
                        T t;
                        ArraySequence<T> arr = {};
                        while (ss >> t) {
                            arr.Append(t);
                        }
                        polyA = Polynomial(arr);
                    }
                    catch (exception) {
                        cout << "Wrong input" << endl;
                        break;
                    }
                } else if (res == 2) {
                    getline(cin, tmp);
                    try {
                        stringstream ss(tmp);
                        T t;
                        ArraySequence<T> arr = {};
                        while (ss >> t) {
                            arr.Append(t);
                        }
                        polyB = Polynomial(arr);
                    }
                    catch (exception) {
                        cout << "Wrong input" << endl;
                        break;
                    }
                }
            case 2: {
                cout << polyA * polyB << endl;
                break;
            }
            case 3: {
                T scalar;
                cin >> scalar;
                cout << polyA * scalar << endl;
                break;
            }
            case 4: {
                cout << polyA + polyB << endl;
                break;
            }
            default: {
                cout << "How did you end up here?\n";
                break;
            }
        }
    }
}


int main() {
    int res = 1;
    cout << "Enter data type" << endl;
    while (res != 0) {
        res = Dialog(MSGS2);
        switch (res) {
            case 0:
                break;
            case 1:
                StartUI<int>();
                break;
            case 2:
                StartUI<float>();
                break;
            case 3:
                StartUI<Complex>();
                break;
            default: {
                cout << "How did you end up here?\n";
                break;
            }
        }
    }

    return 0;
}