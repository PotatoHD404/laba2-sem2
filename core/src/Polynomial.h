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
    Polynomial() {
        this->coefficients = ArraySequence<T>({T()});
    }

    Polynomial(T *items, int count) {
        this->coefficients = ArraySequence<T>(items, count);
    }

    template<int N>
    explicit Polynomial(T (&items)[N]) : Polynomial(items, N) {}

    Polynomial(initializer_list<T> items) {
        this->coefficients = ArraySequence<T>();
        for (T item : items)
            coefficients.Append(item);
    }

    Polynomial(Polynomial<T> const &x) {
        this->coefficients = ArraySequence<T>(x.coefficients);
    }

    Polynomial<T> Multiply(T x) {
        Polynomial<T> res = Polynomial<T>(*this);
        for (int i = 0; i < this->coefficients.GetLength(); ++i) {
            res.coefficients[i] = res.coefficients[i] * x;
        }
        return res;
    }

    Polynomial<T> Multiply(Polynomial<T> &x) {
        Polynomial<T> res = Polynomial<T>();
        for (int i = 0; i < this->coefficients.GetLength(); ++i) {
            Polynomial<T> tmp = res * x.coefficients[i];
            for (int j = 0; j < i; ++j) {
                tmp.coefficients.Prepend();
            }
            res = res + tmp;
        }
        return res;
    }

    Polynomial<T> Sum(Polynomial<T> &x) {
        Polynomial<T> res = Polynomial<T>(*this);

        for (int i = 0; i < this->coefficients.GetLength(); ++i) {
            if (res.coefficients.GetLength() <= i)
                res.Append(T());
            else {
                res.coefficients[i] = res.coefficients[i] * x;
            }
        }
        return res;
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

    Polynomial<T> operator+(const Polynomial<T> &x) const {
        return this->Sum(x);
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

    Polynomial<T> operator*(T &x) const {
        return Multiply(x);
    }

    Polynomial<T> operator*(Polynomial<T> &x) const {
        return Multiply(x);
    }

    friend ostream &operator<<(ostream &out, const Polynomial<T> &x) {
        for (int i = x.coefficients.GetLength() - 1; i > 0; --i) {
            if (x.coefficients[i] != 0) {
                out << x.coefficients[i] << "*x^" << i;
                if (x.coefficients[i] > 0)
                    out << " + ";
            }
        }
        return out;
    }


};

#endif //TEST_DB_POLYNOMIAL_H
