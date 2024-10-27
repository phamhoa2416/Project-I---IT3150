#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
    
    Node(int value) : value(value), next(nullptr) {}
};

bool elementExist(Node* head, int value) {
    for (Node* current = head; current != nullptr; current = current->next) {
        if (current->value == value) 
            return true;
    }
    return false;
}

Node* addlast(Node* head, int k) {
    if (!head) return new Node(k);
    
    if (!elementExist(head, k)) {
        Node* current = head;
        while (current->next != nullptr) 
            current = current->next;
        current->next = new Node(k);
    }
    return head;
}

Node* addfirst(Node* head, int k) {
    if (!elementExist(head, k)) {
        Node* newNode = new Node(k);
        newNode->next = head;
        head = newNode;
    }
    return head;
}

Node* addafter(Node* head, int u, int v) {
    if (!elementExist(head, v) || elementExist(head, u)) 
        return head;

    Node* current = head;
    while (current->value != v) 
        current = current->next;

    Node* newNode = new Node(u);
    newNode->next = current->next;
    current->next = newNode;
    
    return head;
}

Node* addbefore(Node* head, int u, int v) {
    if (!elementExist(head, v) || elementExist(head, u)) 
        return head;

    
    if (head->value == v) return addfirst(head, u);

    Node* current = head;
    while (current->next && current->next->value != v) 
        current = current->next;

    if (current->next) {
        Node* newNode = new Node(u);
        newNode->next = current->next;
        current->next = newNode;
    }
    
    return head;
}

Node* remove(Node* head, int k) {
    if (!head) return nullptr;

    if (head->value == k) {
        head = head->next;
        return head;
    }

    Node* current = head;
    while (current->next && current->next->value != k) 
        current = current->next;

    if (current->next) 
        current->next = current->next->next;

    return head;
}

Node* reverse(Node* head) {
    Node* prev = nullptr;
    while (head) {
        Node* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

void display(Node* head) {
    for (Node* current = head; current != nullptr; current = current->next) {
        cout << current->value << " ";
    }
    cout << endl;
}

int main() {
    int size;
    cin >> size;

    Node* head = nullptr;
    for (int i = 0; i < size; ++i) {
        int value;
        cin >> value;
        head = addlast(head, value);
    }

    string command;
    while (cin >> command) {
        if (command == "addlast" || command == "addfirst") {
            int k;
            cin >> k;
            head = (command == "addlast") ? addlast(head, k) : addfirst(head, k);
        } else if (command == "addafter" || command == "addbefore") {
            int u, v;
            cin >> u >> v;
            head = (command == "addafter") ? addafter(head, u, v) : addbefore(head, u, v);
        } else if (command == "remove") {
            int k;
            cin >> k;
            head = remove(head, k);
        } else if (command == "reverse") {
            head = reverse(head);
        } else if (command == "#") {
            break;
        }
    }
    display(head);
    return 0;
}
