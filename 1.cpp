#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
vector<vector<int>> adj_mat;
vector<bool> used;
long long final_weight = INT_MAX, n;
int main() {
    cin >> n;
    adj_mat.resize(n, vector<int>(n, 0));
    used.resize(n, false);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> adj_mat[i][j];

    vector<int> ord_num(n);
    for (int i = 0; i <= n - 1; ++i) {
        ord_num[i] = i;
    }
    do {
        long long cur_len = 0;
        for (int i = 1; i <= n - 1; ++i) {
            if (adj_mat[ord_num[i-1]][ord_num[i]] != 0) {
                cur_len += adj_mat[ord_num[i-1]][ord_num[i]];
            } else {
                cur_len = INT_MAX;
                break;
            }
        }
        if (cur_len != INT_MAX && adj_mat[ord_num[n - 1]][0] != 0) {
            cur_len += adj_mat[ord_num[n - 1]][0];
        } else if (adj_mat[ord_num[n - 1]][0] == 0 && n != 1) {
            cur_len = INT_MAX;
        }
        if (cur_len < final_weight) final_weight = cur_len;
    } while (next_permutation(ord_num.begin() + 1, ord_num.end()));
    if (final_weight == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << final_weight << endl;
    }
    return 0;
}
