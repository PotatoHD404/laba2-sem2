//
// Created by korna on 03.04.2021.
//


#ifndef LABA2_IENUMERABLE_H
#define LABA2_IENUMERABLE_H

#include "IEnumerator.h"
#include "ICollection.h"

template<class T>
/*interface*/
class IEnumerable {
protected:
    class Enumerator : public IEnumerator<T> {
    private:
        ICollection<T> *items;
        int pos;
    public:
        explicit Enumerator(ICollection<T> *arr) {
            items = arr;
            pos = 0;
        }

        T &GetCurrent() {
            return items->At(pos);
        }

        bool MoveNext() {
            if (++pos < items->GetLength())
                return true;
            pos--;
            return false;
        }

        void Reset() {
            pos = 0;
        }

    };

public:
    IEnumerable() {};

    virtual IEnumerator<T> *GetEnumerator() = 0;

    virtual ~IEnumerable() {};

};

#endif //LABA2_IENUMERABLE_H
