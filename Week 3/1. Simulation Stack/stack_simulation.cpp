#include <iostream>

using namespace std;

class Node {
public:
    int value;
    Node* next;
    
    Node(int value) {
        this->value = value;
        this->next = nullptr;
    }
};

Node* append(Node* head, int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) 
        return newNode;
    
    Node* current = head;
    while (current->next != nullptr) 
        current = current->next;
        
    current->next = newNode;
    
    return head;
}

Node* pop(Node* head) {
    if (head == nullptr) return nullptr;
    
    if (head->next == nullptr) {
        delete head;
        return nullptr;
    }
    
    Node* current = head;
    while (current->next->next != nullptr) 
        current = current->next;
    
    current->next = nullptr;
    
    return head;
}

int main() 
{ 
    Node* head = nullptr;
    
    string command;
    while (cin >> command) {
        if (command == "PUSH") {
            int value;
            cin >> value;
            head = append(head, value);
        } else if (command == "POP") {
            if (head == nullptr) {
                cout << "NULL" << endl;
            } else if (head->next == nullptr) {
                cout << head->value << endl;
                head = nullptr; 
            } else {
                Node* current = head;
                while (current->next != nullptr) 
                    current = current->next;

                cout << current->value << endl;
                head = pop(head);
            } 
        } else break; 
    }
}
