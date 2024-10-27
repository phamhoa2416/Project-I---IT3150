#include <iostream>

using namespace std;

int hashCode(string line, int m) {
    int length = line.size();
    int hash_code = 0;
    for (int i = 0; i < length; ++i) {
        hash_code = (256 * hash_code + line[i]) % m;
    }
    return hash_code;
}

int main() {
    int num, m;
    cin >> num >> m;
    
    for (int i = 0; i < num; ++i) {
        string line;
        cin >> line;
        cout << hashCode(line, m) << endl;
    }
    
    return 0;
}
