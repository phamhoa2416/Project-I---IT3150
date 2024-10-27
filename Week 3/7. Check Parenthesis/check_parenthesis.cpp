#include <iostream>
#include <stack>

using namespace std;

int checkParenthesis(string line) {
    stack<char> s;
    int length = line.size();
    
    for (int i = 0; i < length; ++i) {
        if (line[i] == '(' || line[i] == '[' || line[i] == '{') 
            s.push(line[i]);
    else if (!s.empty() && ((line[i] == ')' && s.top() == '(') || 
                            (line[i] == ']' && s.top() == '[') ||
                            (line[i] == '}' && s.top() == '{')))
            s.pop();
        else return 0;
    }
    
    if (s.empty()) return 1;
    else return 0;
}

int main() 
{ 
    string line;
    cin >> line;
    cout << checkParenthesis(line) << endl;
    return 0;
}
