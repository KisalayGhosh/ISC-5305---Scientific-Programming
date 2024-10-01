#ifndef LOG_QUADRATIC_FUNCTION_H
#define LOG_QUADRATIC_FUNCTION_H

#include "function.h"
#include <cmath>

template <typename T>
class LogQuadraticFunction : public Function<T>
{
public:
    LogQuadraticFunction() : Function<T>("log(x) + x^2 - 3") {}

    T operator()(T x) const override {
        return std::log(x) + x*x - 3;
    }

    T fp(T x) const override {
        return 1 / x + 2 * x;
    }
};

#endif // LOG_QUADRATIC_FUNCTION_H
