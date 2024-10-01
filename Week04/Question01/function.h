#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <cmath>
#include <string>

template <typename T>
class Function
{
public:
    std::string name;
    Function(const std::string& name_) : name(name_) {}
    virtual ~Function() {}
    
    // Pure virtual functions for f(x) and the derivative f'(x)
    virtual T operator()(T x) const = 0;
    virtual T fp(T x) const = 0;
    
    // Verify the solution against the expected root
    virtual T verify(T computed_root) const {
        return std::abs(operator()(computed_root));
    }
};

#endif // FUNCTION_H
