#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 7;

long long computeCombination(int n, int k) {
    vector<vector<long long>> result(n + 1, vector<long long>(k + 1, 0));
    
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= min(i, k); ++j) {
            if (j == 0 || j == i) {
                result[i][j] = 1;
            } else {
                result[i][j] = (result[i - 1][j - 1] + result[i - 1][j]) % MOD;
            }
        }
    }
    
    return result[n][k];
}

int main() 
{ 
    int n, k;
    cin >> k >> n;
    cout << computeCombination(n, k);
    
}
