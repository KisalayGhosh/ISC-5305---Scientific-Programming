#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

// Enum to specify the type of a node in the expression tree (Constant, Variable, Operator)
enum class NodeType { Constant, Variable, Operator };

class Node {
private:
    NodeType type;                  // Type of the node: Constant, Variable, or Operator
    double constantValue;            // Value if the node is a constant
    char variable;                   // Variable symbol if the node represents a variable (e.g., 'x')
    char op;                         // Operator symbol if the node represents an operation (e.g., '+', '*')
    std::shared_ptr<Node> left;      // Left child node for binary operations
    std::shared_ptr<Node> right;     // Right child node for binary operations

public:
    // Constructor for constant nodes
    Node(double value) : type(NodeType::Constant), constantValue(value) {}

    // Constructor for variable nodes
    Node(char var) : type(NodeType::Variable), variable(var) {}

    // Constructor for operator nodes with left and right child nodes
    Node(char oper, std::shared_ptr<Node> l, std::shared_ptr<Node> r)
        : type(NodeType::Operator), op(oper), left(l), right(r) {}

    // Getter methods to access node properties
    NodeType getType() const { return type; }
    double getConstantValue() const { return constantValue; }
    char getVariable() const { return variable; }
    char getOperator() const { return op; }
    std::shared_ptr<Node> getLeft() const { return left; }
    std::shared_ptr<Node> getRight() const { return right; }
};

#endif
