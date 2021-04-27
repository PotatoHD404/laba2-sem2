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
                      "4. Sum polynomials",
                      "5. Calculate in point",
                      "6. Print polynomial"};
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
                if (res == 0) {
                    res = 1;
                    break;
                }
                scanf("\n");
                if (res == 1)
                    cin >> polyA;
                else
                    cin >> polyB;
                break;

            case 2: {
                cout << "Result:" << endl;
                cout << polyA * polyB << endl;
                break;
            }
            case 3: {
                res = Dialog(MSGS1);
                cout << "Enter a scalar:" << endl;
                scanf("\n");
                T scalar;
                try {
                    cin >> scalar;
                    cout << "Result:" << endl;
                    if (res == 1)
                        cout << polyA * scalar << endl;
                    else
                        cout << polyB * scalar << endl;
                }
                catch (exception) {
                    cout << "Wrong input" << endl;
                }

                break;
            }
            case 4: {
                cout << "Result:" << endl;
                cout << polyA + polyB << endl;
                break;
            }
            case 5: {
                res = Dialog(MSGS1);
                cout << "Enter a number:" << endl;

                T x;
                try {
                    cin >> x;
                    cout << "Result:" << endl;
                    if (res == 1)
                        cout << polyA.Calculate(x) << endl;
                    else
                        cout << polyB.Calculate(x) << endl;
                }
                catch (exception) {
                    cout << "Wrong input" << endl;
                }
                break;
            }

            case 6: {
                res = Dialog(MSGS1);
                if (res == 0) {
                    res = 1;
                    break;
                } else if (res == 1)
                    cout << "PolyA:" << endl << polyA << endl;
                else if (res == 2)
                    cout << "PolyB:" << endl << polyB << endl;
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

    return 0;
}