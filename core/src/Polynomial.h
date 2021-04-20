//
// Created by korna on 20.04.2021.
//

#ifndef TEST_DB_POLYNOMIAL_H
#define TEST_DB_POLYNOMIAL_H

#include "ArraySequence.h"

template<typename T>
class Polynomial {
private:
    ArraySequence<T> coefficients;

public:
    Polynomial() : Polynomial(T()) {
    }

    explicit Polynomial(T x) {
        this->coefficients = ArraySequence<T>({x});
    }

    Polynomial(T *items, int count) {
        this->coefficients = ArraySequence<T>(items, count);
    }

    explicit Polynomial(ArraySequence<T> x) {
        this->coefficients = ArraySequence<T>(x);
    }

    template<int N>
    explicit Polynomial(T (&items)[N]) : Polynomial(items, N) {}

    Polynomial(initializer_list<T> items) {
        this->coefficients = ArraySequence<T>();
        for (T item : items)
            coefficients.Append(item);
    }

    T &At(int index) {
        return this->coefficients[coefficients.GetLength() - 1 - index];
    }

    bool operator==(Polynomial<T> &x) { return x.coefficients == this->coefficients; }

    T &operator[](unsigned int index) { return At(index); }

    Polynomial(Polynomial<T> const &x) {
        this->coefficients = ArraySequence<T>(x.coefficients);
    }

    T Calculate(T x) {
        T res = coefficients[0];
        T tmp = x;
        for (int i = 1; i < coefficients.GetLength(); ++i) {
            res = res + coefficients[i] * x;
            tmp = tmp * x;
        }
        return res;
    }

    Polynomial<T> operator*(T x) {
        Polynomial<T> res = Polynomial<T>(*this);
        for (int i = 0; i < res.coefficients.GetLength(); ++i) {
            res.coefficients[i] = res.coefficients[i] * x;
        }
        return res;
    }

    Polynomial<T> operator*(Polynomial<T> x) const {
        Polynomial<T> res = Polynomial<T>(*this);
        for (int i = 0; i < res.coefficients.GetLength(); ++i) {
            Polynomial<T> tmp = res * x.coefficients[i];
            for (int j = 0; j < i; ++j) {
                tmp.coefficients.Prepend(T());
            }
            res = res + tmp;
        }
        return res;
    }


    Polynomial<T> operator+(Polynomial<T> x) const {
        Polynomial<T> res = Polynomial<T>(*this);

        for (int i = 0; i < res.coefficients.GetLength(); ++i) {
            if (res.coefficients.GetLength() <= i)
                res.coefficients.Append(x.coefficients[i]);
            else {
                res.coefficients[i] = res.coefficients[i] + x.coefficients[i];
            }
        }
        return res;
    }

    Polynomial<T> operator-() const {
        Polynomial<T> res = Polynomial<T>(*this);
        for (int i = 0; i < this->coefficients.GetLength(); ++i) {
            res.coefficients[i] = -this->coefficients[i];
        }
        return res;
    }

    Polynomial<T> operator-(const Polynomial<T> &x) const {
        return this->Sum(-x);
    }



    friend ostream &operator<<(ostream &out, Polynomial<T> x) {
        for (int i = x.coefficients.GetLength() - 1; i > 0; --i) {
            if (x.coefficients[i] != 0) {
                out << x.coefficients[i] << "*x^" << i;
                if (x.coefficients[i] >= 0.0f)
                    out << " + ";
            }
        }
        return out;
    }


};

#endif //TEST_DB_POLYNOMIAL_H
