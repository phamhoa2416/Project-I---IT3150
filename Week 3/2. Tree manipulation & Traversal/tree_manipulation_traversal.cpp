#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* leftMostChild;
    Node* rightSibling;
    
    Node(int id) : value(id), leftMostChild(nullptr), rightSibling(nullptr) {}
};

Node* find_id(Node* root, int id) {
    if (root == nullptr) return nullptr;
    
    if (root->value == id) {
        return root;
    }
    
    Node* current = root->leftMostChild;
    while (current != nullptr) {
        Node* temp = find_id(current, id);
        if (temp != NULL)
            return temp;
        current = current->rightSibling;
    }
    return NULL;
}

void insert(Node* root, int u, int v) {
    if (find_id(root, u) != nullptr || find_id(root, v) == nullptr) 
        return;
        
    Node* insertNode = find_id(root, v);
    
    if (insertNode->leftMostChild == nullptr) {
        insertNode->leftMostChild = new Node(u);
    } else {
        Node* current = insertNode->leftMostChild;
        while (current->rightSibling != nullptr) 
            current = current->rightSibling;
        current->rightSibling = new Node(u);
    }
}

void inOrderTraversal(Node* root) {
    if (root == nullptr)
        return;
        
    Node* current = root->leftMostChild;
    inOrderTraversal(current);
    cout << root->value << " ";
    
    if (current == nullptr)
        return;
    current = current->rightSibling;
    
    while (current != nullptr) {
        inOrderTraversal(current);
        current = current->rightSibling;
    }
}

void preOrderTraversal(Node* root) {
    if (root == nullptr) 
        return;
        
    cout << root->value << " ";
    Node* current = root->leftMostChild;
    while (current != nullptr) {
        preOrderTraversal(current);
        current = current->rightSibling;
    }
}

void postOrderTraversal(Node* root) {
    if (root == nullptr) 
        return;
        
    Node* current = root->leftMostChild;
    while (current != nullptr) {
        postOrderTraversal(current);
        current = current->rightSibling;
    }
    
    cout << root->value << " ";
}

int main() {
    Node* head = nullptr;
    
    string command;
    while (cin >> command) {
        if (command == "MakeRoot") {
            int value;
            cin >> value;
            head = new Node(value);
        } else if (command == "Insert") {
            int u, v;
            cin >> u >> v;
            insert(head, u, v); 
        } else if (command == "PreOrder") {
            preOrderTraversal(head);
        } else if (command == "PostOrder") {
            postOrderTraversal(head);
        } else if (command == "InOrder") {
            inOrderTraversal(head);
        } else break;
    }
    
    return 0;
}
