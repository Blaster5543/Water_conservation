#include "tree.h"
#include <iostream>
#include <algorithm>
#include <string>
#define COUNT 10

//BinaryTree constructor and add_node method from ZyBooks

BinaryTree::BinaryTree() 
{
   root = add_node(root, "0", "2", 0);
}

Node_tree* BinaryTree::add_node(Node_tree* parent, std::string num_code, std::string y_n_chain, int pos) const {

   //Checks if the parent is nullptr, creates a new_node to return as the parent of that node.
   if (parent == nullptr) {
      Node_tree* new_node = new Node_tree();
      new_node->num_code = num_code;
      return new_node;
   } else {
   //Checks the binary string on whether to go left or right for the nodes.
      if (y_n_chain[pos] == 'Y') {
         parent->left = add_node(parent->left, num_code, y_n_chain, pos + 1);
      } else {
         parent->right = add_node(parent->right, num_code, y_n_chain, pos + 1);
      }
      return parent;
   }
}

std::string BinaryTree::get_data(Node_tree* node, std::string y_n_chain, int pos) const {
    if (node != nullptr) {
        if (pos == y_n_chain.length()) {
            return node->num_code;
        } else if (node->left == nullptr && node->right == nullptr) {
            return node->num_code;
        } else {
            if (y_n_chain[pos] == 'Y') { //Checks if the next character is 0 or 1
                return get_data(node->left, y_n_chain, pos + 1);
            } else {
                return get_data(node->right, y_n_chain, pos + 1);
            }
        }
    } else {
        return " ";
    }
}

Node_tree* BinaryTree::get_root() const {
   return root;
}

//Will delete later
void BinaryTree::print2DUtil(Node_tree* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << root->num_code << "\n";
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void BinaryTree::print2D(Node_tree* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

void BinaryTree::delete_tree(Node_tree* node) {
   //Returns if there is no node.
   if (node == NULL) {
      return;
   }
   //Traverses through each of the nodes and deletes the node.
   delete_tree(node->left);
   delete_tree(node->right);
   delete node;
}