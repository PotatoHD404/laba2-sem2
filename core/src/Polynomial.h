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

    Polynomial(T *items, size_t count) {
        this->coefficients = ArraySequence<T>(items, count);
    }

    explicit Polynomial(ArraySequence<T> x) {
        this->coefficients = ArraySequence<T>();
        for (int i = 0; i < x.GetLength(); ++i)
            coefficients.Prepend(x[i]);
    }

    template<size_t N>
    explicit Polynomial(T (&items)[N]) : Polynomial(items, N) {}

    Polynomial(initializer_list<T> items) {
        this->coefficients = ArraySequence<T>();
        for (T item : items)
            coefficients.Prepend(item);
    }

    size_t GetDimension() { return coefficients.GetLength(); }

    T &At(size_t index) {
        return this->coefficients[coefficients.GetLength() - 1 - index];
    }

    bool operator==(Polynomial<T> &x) { return x.coefficients == this->coefficients; }

    T &operator[](size_t index) { return At(index); }

    Polynomial(Polynomial<T> const &x) {
        this->coefficients = ArraySequence<T>(x.coefficients);
    }

    T Calculate(T x) {
        T res = coefficients[0];
        T tmp = x;
        for (size_t i = 1; i < coefficients.GetLength(); ++i) {
            res = res + coefficients[i] * tmp;
            tmp = tmp * x;
        }
        return res;
    }

    Polynomial<T> operator*(T x) {
        Polynomial<T> res = Polynomial<T>(*this);
        for (size_t i = 0; i < res.coefficients.GetLength(); ++i) {
            res.coefficients[i] = res.coefficients[i] * x;
        }
        return res;
    }

    Polynomial<T> operator*(Polynomial<T> &x) const {
        Polynomial<T> res = Polynomial<T>();
        Polynomial<T> y = Polynomial<T>(*this);
        for (size_t i = 0; i < x.coefficients.GetLength(); ++i) {
            Polynomial<T> tmp = y * x.coefficients[i];
            for (size_t j = 0; j < i; ++j) {
                tmp.coefficients.Prepend(T());
            }
            res = res + tmp;
        }
        return res;
    }


    Polynomial<T> operator+(Polynomial<T> x) const {
        Polynomial<T> res = Polynomial<T>(*this);

        for (size_t i = 0; i < x.coefficients.GetLength(); ++i) {
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
        for (size_t i = 0; i < this->coefficients.GetLength(); ++i) {
            res.coefficients[i] = -this->coefficients[i];
        }
        return res;
    }

    Polynomial<T> operator-(const Polynomial<T> &x) const {
        return this->Sum(-x);
    }

    friend istream &operator>>(istream &in, Polynomial &poly) {
        string tmp;
        getline(in, tmp);
        stringstream ss(tmp);
        T t;
        poly.coefficients = ArraySequence<T>();
        while (ss >> t) {
            poly.coefficients.Prepend(t);
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, Polynomial<T> x) {
        if (x.coefficients[x.coefficients.GetLength() - 1] < 0)
            out << "-";
        for (size_t i = x.coefficients.GetLength() - 1; i > 0; --i) {
            if (x.coefficients[i] != 0) {
                if (x.coefficients[i] < 0)
                    x.coefficients[i] = -x.coefficients[i];
                if (x.coefficients[i] != 1)
                    out << x.coefficients[i] << "*";
                out << "x";

                if (i > 1)
                    out << "^" << i;
                if (x.coefficients[i - 1] >= 0.0f)
                    out << " + ";
                else
                    out << " - ";
            }
        }
        if (x.coefficients[0] < 0)
            x.coefficients[0] = -x.coefficients[0];
        out << x.coefficients[0];
        return out;
    }
};

#endif //TEST_DB_POLYNOMIAL_H
