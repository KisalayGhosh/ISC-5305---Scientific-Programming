#include "PolynomialBinaryTree.hpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

// Function to compare two floating-point numbers for approximate equality
bool almostEqual(double a, double b, double tolerance = 1e-4) {
    return std::fabs(a - b) < tolerance;
}

// Numerical derivative approximation using finite differences
double numericalDerivative(const PolynomialBinaryTree& poly, double x, double h = 1e-5) {
    return (poly.evaluate(x + h) - poly.evaluate(x - h)) / (2 * h);
}

void testConstructFromZeros() {
    std::cout << "Running testConstructFromZeros...\n";
    PolynomialBinaryTree poly;
    std::vector<double> zeros = {-0.86, -0.34, 0.34, 0.86};
    poly.constructFromZeros(zeros);

    // Check if the polynomial evaluates to zero at each root
    for (double root : zeros) {
        double value = poly.evaluate(root);
        assert(almostEqual(value, 0.0));
    }
    std::cout << "testConstructFromZeros passed.\n";
}

void testEvaluate() {
    std::cout << "Running testEvaluate...\n";
    PolynomialBinaryTree poly;
    std::vector<double> zeros = {-0.86, -0.34, 0.34, 0.86};
    poly.constructFromZeros(zeros);

    // Check evaluation at a point we know the answer for
    double x = 0.5;
    double expectedValue = (x + 0.86) * (x + 0.34) * (x - 0.34) * (x - 0.86);
    double evaluatedValue = poly.evaluate(x);
    assert(almostEqual(evaluatedValue, expectedValue));

    std::cout << "testEvaluate passed.\n";
}

void testDifferentiation() {
    std::cout << "Running testDifferentiation...\n";
    PolynomialBinaryTree poly;
    std::vector<double> zeros = {-0.86, -0.34, 0.34, 0.86};
    poly.constructFromZeros(zeros);

    // Differentiate the polynomial
    PolynomialBinaryTree firstDerivative = poly.differentiate();
    
    // Choose a point to evaluate the derivative
    double x = 0.5;
    
    // Use numerical differentiation to get the expected value
    double expectedFirstDerivative = numericalDerivative(poly, x);
    double evaluatedFirstDerivative = firstDerivative.evaluate(x);

    assert(almostEqual(evaluatedFirstDerivative, expectedFirstDerivative));

    std::cout << "testDifferentiation passed.\n";
}

void testRepeatedRoots() {
    std::cout << "Running testRepeatedRoots...\n";
    PolynomialBinaryTree poly;
    std::vector<double> zeros = {-0.5, -0.5, 0.5, 0.5};  // Repeated roots
    poly.constructFromZeros(zeros);

    // Test evaluation at roots
    for (double root : zeros) {
        double value = poly.evaluate(root);
        assert(almostEqual(value, 0.0));
    }

    std::cout << "testRepeatedRoots passed.\n";
}

int main() {
    try {
        testConstructFromZeros();
        testEvaluate();
        testDifferentiation();
        testRepeatedRoots();

        std::cout << "All tests passed.\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
