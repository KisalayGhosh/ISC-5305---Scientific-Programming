#ifndef NON_ADAPTIVE_INTEGRATION_H
#define NON_ADAPTIVE_INTEGRATION_H

#include <functional>

double parallelNonAdaptiveIntegration(double a, double b, int n, int threads, const std::function<double(double)>& f, bool verbose);

#endif // NON_ADAPTIVE_INTEGRATION_H
