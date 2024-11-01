#ifndef POLYNOMIAL_BINARY_TREE_HPP
#define POLYNOMIAL_BINARY_TREE_HPP

#include "Node.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <unordered_map>

class PolynomialBinaryTree {
private:
    std::shared_ptr<Node> root;  // Root of the expression tree representing the polynomial

public:
    // Constructors
    PolynomialBinaryTree() : root(nullptr) {}
    PolynomialBinaryTree(std::shared_ptr<Node> node) : root(node) {}

    // Setter and Getter for the root node
    void setRoot(std::shared_ptr<Node> node) { root = node; }
    std::shared_ptr<Node> getRoot() const { return root; }

    // Adds two polynomials by creating a new root node with '+' operator
    PolynomialBinaryTree add(const PolynomialBinaryTree& other) const {
        return PolynomialBinaryTree(std::make_shared<Node>('+', root, other.getRoot()));
    }

    // Multiplies two polynomials by creating a new root node with '*' operator
    PolynomialBinaryTree multiply(const PolynomialBinaryTree& other) const {
        return PolynomialBinaryTree(std::make_shared<Node>('*', root, other.getRoot()));
    }

    // Differentiates the polynomial recursively
    PolynomialBinaryTree differentiateRecursive(std::shared_ptr<Node> node) const {
        if (!node) throw std::runtime_error("Null node encountered during differentiation.");

        if (node->getType() == NodeType::Constant) {
            // The derivative of a constant is zero
            return PolynomialBinaryTree(std::make_shared<Node>(0.0));
        } 
        else if (node->getType() == NodeType::Variable) {
            // The derivative of a variable (e.g., x) is 1
            return PolynomialBinaryTree(std::make_shared<Node>(1.0));
        } 
        else if (node->getType() == NodeType::Operator) {
            if (node->getOperator() == '+') {
                // Sum rule: (f + g)' = f' + g'
                PolynomialBinaryTree leftDiff = differentiateRecursive(node->getLeft());
                PolynomialBinaryTree rightDiff = differentiateRecursive(node->getRight());
                return leftDiff.add(rightDiff);
            } 
            else if (node->getOperator() == '-') {
                // Difference rule: (f - g)' = f' - g'
                PolynomialBinaryTree leftDiff = differentiateRecursive(node->getLeft());
                PolynomialBinaryTree rightDiff = differentiateRecursive(node->getRight());
                return PolynomialBinaryTree(std::make_shared<Node>('-', leftDiff.getRoot(), rightDiff.getRoot()));
            }
            else if (node->getOperator() == '*') {
                // Product rule: (f * g)' = f' * g + f * g'
                auto left = node->getLeft();
                auto right = node->getRight();
                PolynomialBinaryTree leftDiff = differentiateRecursive(left);
                PolynomialBinaryTree rightDiff = differentiateRecursive(right);

                // Term1 = f' * g and Term2 = f * g'
                PolynomialBinaryTree term1(std::make_shared<Node>('*', leftDiff.getRoot(), right));
                PolynomialBinaryTree term2(std::make_shared<Node>('*', left, rightDiff.getRoot()));
                return term1.add(term2);
            }
        }
        throw std::runtime_error("Unsupported operator encountered during differentiation.");
    }

    // Initiates differentiation from the root
    PolynomialBinaryTree differentiate() const {
        return differentiateRecursive(root);
    }

    // Recursive evaluation of the polynomial at a specific x value
    double evaluateAt(std::shared_ptr<Node> node, double x) const {
        if (!node) throw std::runtime_error("Null node encountered during evaluation.");

        if (node->getType() == NodeType::Constant) {
            return node->getConstantValue();
        } else if (node->getType() == NodeType::Variable) {
            return x;
        } else if (node->getType() == NodeType::Operator) {
            double leftValue = evaluateAt(node->getLeft(), x);
            double rightValue = evaluateAt(node->getRight(), x);
            switch (node->getOperator()) {
                case '+': return leftValue + rightValue;
                case '-': return leftValue - rightValue;
                case '*': return leftValue * rightValue;
                case '/': 
                    if (rightValue == 0) throw std::runtime_error("Division by zero.");
                    return leftValue / rightValue;
                default: throw std::runtime_error("Unsupported operator in evaluation.");
            }
        }
        throw std::runtime_error("Invalid node type encountered during evaluation.");
    }

    // Wrapper function to evaluate the polynomial at x from the root node
    double evaluate(double x) const {
        return evaluateAt(root, x);
    }

    // Constructs the polynomial expression tree from given roots
    void constructFromZeros(const std::vector<double>& zeros) {
        if (zeros.empty()) throw std::runtime_error("Empty list of zeros provided.");

        std::unordered_map<double, int> zeroMultiplicity;
        for (double zero : zeros) zeroMultiplicity[zero]++;

        bool firstTerm = true;
        for (const auto& [zero, multiplicity] : zeroMultiplicity) {
            auto term = std::make_shared<Node>('-', std::make_shared<Node>('x'), std::make_shared<Node>(zero));
            std::shared_ptr<Node> factor = term;
            for (int i = 1; i < multiplicity; ++i) {
                factor = std::make_shared<Node>('*', factor, term);
            }

            if (firstTerm) {
                root = factor;
                firstTerm = false;
            } else {
                root = std::make_shared<Node>('*', root, factor);
            }
        }
    }
};

#endif
