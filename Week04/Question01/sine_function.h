#ifndef SINE_FUNCTION_H
#define SINE_FUNCTION_H

#include "function.h"
#include <cmath>

template <typename T>
class SineFunction : public Function<T>
{
public:
    SineFunction() : Function<T>("sin(3x - 2)") {}

    T operator()(T x) const override {
        return std::sin(3 * x - 2);
    }

    T fp(T x) const override {
        return 3 * std::cos(3 * x - 2);
    }
};

#endif // SINE_FUNCTION_H
