//
// Created by korna on 03.04.2021.
//

#ifndef LABA2_IENUMERATOR_H
#define LABA2_IENUMERATOR_H

template<class T>
/*interface*/ class IEnumerator {
public:
    virtual T &GetCurrent() = 0;

    virtual bool MoveNext() = 0;

    virtual void Reset() = 0;

};

#endif //LABA2_IENUMERATOR_H