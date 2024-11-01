#include "PolynomialBinaryTree.hpp"
#include <fstream>
#include <iostream>
#include <vector>

// Function to evaluate and save polynomial and its derivatives at specific points to a file
void savePolynomialEvaluation(const PolynomialBinaryTree& poly, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Unable to open file for saving polynomial evaluations.");

    // Write the header
    file << "x P(x) P'(x) P''(x) P'''(x) P''''(x) P'''''(x)\n";

    // Create differentiated polynomials
    PolynomialBinaryTree firstDerivative = poly.differentiate();
    PolynomialBinaryTree secondDerivative = firstDerivative.differentiate();
    PolynomialBinaryTree thirdDerivative = secondDerivative.differentiate();
    PolynomialBinaryTree fourthDerivative = thirdDerivative.differentiate();
    PolynomialBinaryTree fifthDerivative = fourthDerivative.differentiate();

    // Evaluate the polynomial and its derivatives at points
    for (double x = 0.0; x <= 1.0; x += 0.01) {
        double polyValue = poly.evaluate(x);
        double firstValue = firstDerivative.evaluate(x);
        double secondValue = secondDerivative.evaluate(x);
        double thirdValue = thirdDerivative.evaluate(x);
        double fourthValue = fourthDerivative.evaluate(x);
        double fifthValue = fifthDerivative.evaluate(x);

        file << x << " " << polyValue << " " << firstValue << " " << secondValue << " "
             << thirdValue << " " << fourthValue << " " << fifthValue << "\n";
    }

    file.close();
    std::cout << "Data written successfully to " << filename << std::endl;
}

int main() {
    PolynomialBinaryTree poly;
    std::vector<double> zeros = {-0.86, -0.34, 0.34, 0.86};
    poly.constructFromZeros(zeros);

    savePolynomialEvaluation(poly, "polynomial_evaluation.txt");
    return 0;
}
