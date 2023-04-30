#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <string>

struct Node_tree {
   std::string num_code;
   Node_tree* left;
   Node_tree* right;
};

class BinaryTree
{
public:
    /**
    * Constructs a tree with one node and no children.
    */
    BinaryTree();

    /**
    * Inserts a new node to the tree.
    * @param parent the root node
    * @param element the character data to be inserted
    * @param encrypted the binary string the character is associated with
    * @param pos the start of the position of the binary string
    */
    Node_tree* add_node(Node_tree* parent, std::string num_code, std::string y_n_chain, int pos) const;

    /**
    * 
    */
    std::string get_data(Node_tree* node, std::string y_n_chain, int pos) const;  

    /**
    * Gets the root of the tree.
    */
    Node_tree* get_root() const;

    void print2D(Node_tree* root);
    void print2DUtil(Node_tree* node, int space);

    /**
    * Deletes the entire tree.
    * @param node the root node to delete from.
    */
    void delete_tree(Node_tree* node);

private:
    Node_tree* root = nullptr;
};
#endif