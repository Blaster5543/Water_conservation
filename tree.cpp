#include "tree.h"
#include <iostream>
#include <algorithm>
#include <string>

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

int BinaryTree::get_data() const {
    return 0;
}

Node_tree* BinaryTree::get_root() const {
   return root;
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