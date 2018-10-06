#include "abstractsyntaxtree.h"

#include <string>

using namespace std;

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
  return eval(root);
}

double AbstractSyntaxTree::eval(Node* subRoot) const {
  // Base case: empty tree
  if (subRoot == NULL) return 0;
  // Basecase: Extract double if node is a leaf node
  if (subRoot->left == NULL && subRoot->right == NULL) return stod(subRoot->elem);

  // Evaluate the left and right subtrees
  double leftVal = eval(subRoot->left);
  double rightVal = eval(subRoot->right);
  // Determine whether to add, subtract, multiply, or divide
  if (subRoot->elem == "+") return leftVal + rightVal;
  else if (subRoot->elem == "-") return leftVal - rightVal;
  else if (subRoot->elem == "*") return leftVal * rightVal;
  /*if (subRoot->elem == "/")*/ else return leftVal / rightVal;
};
