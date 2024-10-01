#ifndef CUBIC_FUNCTION_H
#define CUBIC_FUNCTION_H

#include "function.h"

template <typename T>
class CubicFunction : public Function<T>
{
public:
    CubicFunction() : Function<T>("x^3 - 6x^2 + 11x - 8") {}

    T operator()(T x) const override {
        return x*x*x - 6*x*x + 11*x - 8;
    }

    T fp(T x) const override {
        return 3*x*x - 12*x + 11;
    }
};

#endif // CUBIC_FUNCTION_H
