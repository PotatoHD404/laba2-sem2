//
// Created by korna on 20.04.2021.
//

#ifndef TEST_DB_COMPLEX_H
#define TEST_DB_COMPLEX_H

#include <iostream>

using namespace std;

class Complex {
private:
    float real, imaginary;
public:
    Complex() : real(), imaginary() {}

    Complex(float real, float imaginary) {
        this->real = real;
        this->imaginary = imaginary;
    }

    Complex(const Complex &ob) {
        real = ob.real;
        imaginary = ob.imaginary;
    };

    Complex &operator=(const Complex &x) = default;

    Complex operator+(const Complex &x) const {
        float i, j;
        i = this->real + x.real;
        j = this->imaginary + x.imaginary;
        return Complex(i, j);
    }

    Complex operator-() const {
        float i, j;
        i = -this->real;
        j = -this->imaginary;
        return Complex(i, j);
    }

    Complex operator-(const Complex &x) const {
        float i, j;
        i = this->real - x.real;
        j = this->imaginary - x.imaginary;
        return Complex(i, j);
    }

    Complex operator*(Complex &x) const {
        float i, j;
        i = real * x.real - imaginary * x.imaginary;
        j = real * x.imaginary + x.real * imaginary;
        return Complex(i, j);
    }

    Complex operator/(Complex &x) const {
        float i, j, k;
        k = real * real + x.imaginary * x.imaginary;
        i = (real * x.real + imaginary * x.imaginary) / k;
        j = (x.real * imaginary - real * x.imaginary) / k;
        return Complex(i, j);
    }

    friend ostream &operator<<(ostream &out, const Complex &x) {
        if (x.imaginary < 0)
            out << x.real << "-i" << -x.imaginary;
        else
            out << x.real << "+i" << x.imaginary;
        return out;
    }

    bool operator==(Complex &x) const { return !(*this != x); }

    bool operator!=(Complex &x) const {
        if (this->real != x.real || this->imaginary != x.imaginary)
            return true;
        else
            return false;
    }

};

#endif //TEST_DB_COMPLEX_H
