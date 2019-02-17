#include <math.h>
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <climits>
using namespace std;
vector<vector<int>> adj_mat;
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> nums(n);
    adj_mat.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        nums[i].first = i;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> adj_mat[i][j];
    int final_weight = 0;
    for (int i = 1; i < pow(2, n) - 1; ++i) {
        int cur_weight = 0;
        bitset<20> bits(i);
        vector<int> part1;
        vector<int> part2;
        for (int j = 0; j < n; ++j) {
            if (bits[j] == 1) {
                part1.push_back(nums[j].first);
            } else {
                part2.push_back(nums[j].first);
            }
        }
        for (int v1 : part1) {
            for (int v2 : part2) {
                cur_weight += adj_mat[v1][v2];
            }
        }
        if (cur_weight > final_weight) {
            final_weight = cur_weight;
            for (int v1 : part1) {
                nums[v1].second = 1;
            }
            for (int v2 : part2) {
                nums[v2].second = 2;
            }
        }
    }
    cout << final_weight << endl;
    for (int i = 0; i < n; ++i) cout << nums[i].second << " ";
}
