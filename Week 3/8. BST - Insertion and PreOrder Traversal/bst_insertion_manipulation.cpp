//C++ 
#include <iostream>

using namespace std; 

struct Node {
    int value;
    Node* left;
    Node* right;
    
    Node(int value) {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
};

Node* insert(Node* node, int value) {
     // If the tree is empty, return a new node
    if (node == nullptr) 
        return new Node(value);
    
    // If the key is already present in the tree, return the node
    if (node->value == value) 
        return node;
    
    // If the key to be inserted is greater than the node's value, insert it in the right subtree
    if (node->value < value) 
        node->right = insert(node->right, value);
    // If the key to be inserted is smaller than the node's value, insert it in the ;eft subtree
    else 
        node->left = insert(node->left, value);
        
    return node;
}

void preOrderTraversal(Node * root) {
    if (root !=nullptr) {
        cout << root->value << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

int main() 
{ 
    Node* node = nullptr;
    string command;
    while (cin >> command) {
        if (command == "insert") {
            int value;
            cin >> value;
            node = insert(node, value);
        } else break;
    }
    
    preOrderTraversal(node);
}
