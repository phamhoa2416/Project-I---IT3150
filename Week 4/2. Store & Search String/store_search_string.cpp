#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<string> database;
    string line, command;
    
    while (cin >> line) {
        if (line == "*") break;
        database.insert(line);
    }
    
    while (cin >> command) {
        if (command == "***") break;
        
        cin >> line;
        if (command == "find") {
            if (database.find(line) != database.end()) 
                cout << 1 << endl;
            else
                cout << 0 << endl;
        } else if (command == "insert") {
            if (database.find(line) != database.end())
                cout << 0 << endl;
            else 
                cout << 1 << endl;
            database.insert(line);
        }
    }
    
    return 0;
}
