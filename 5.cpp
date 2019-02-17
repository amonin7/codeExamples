#include <math.h>
#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <algorithm>
using namespace std;
int n;
vector < vector<float> > adj_mat;
vector<pair<float, float>> coord;
double dist(pair<float, float> c1, pair<float, float> c2) {
    return sqrt((c1.first - c2.first) * (c1.first - c2.first) +
                (c1.second - c2.second) * (c1.second - c2.second));
}
void input() {
    for (int i = 0; i < n; ++i) {
        cin >> coord[i].first >> coord[i].second;
        for (int j = 0; j < i; ++j) {
            adj_mat[i][j] = dist(coord[i], coord[j]);
            adj_mat[j][i] = dist(coord[i], coord[j]);
        }
    }
}
pair<vector<int>, double> find_min_way() {
    vector<int> answer;
    vector<bool> used(n, false);
    answer.push_back(0);
    double length = 0;
    int cur_v = 0;
    for (int i = 1; i <= n; ++i) {
        used[cur_v] = true;
        double min_lenth = INT_MAX;
        int next_v = -1;
        for (int j = 0; j < adj_mat[cur_v].size(); ++j) {
            if (adj_mat[cur_v][j] < min_lenth && !used[j]) {
                next_v = j;
                min_lenth = adj_mat[cur_v][j];
            }
        }
        if (next_v != -1) {
            answer.push_back(next_v);
            length += min_lenth;
            cur_v = next_v;
        } else {
            answer.push_back(0);
            length += adj_mat[cur_v][0];
            break;
        }

    }
    return make_pair(answer, length);
}
int main() {
    cin >> n;
    coord.resize(n);
    adj_mat.resize(n, vector<float>(n, 0));
    input();
    pair<vector<int>, double> p = find_min_way();
    
    double found_len = p.second;
    vector<int> cur_way = p.first;

    auto start = chrono::steady_clock::now();
    while (chrono::steady_clock::now() <= start + 9s) {
        vector<int> cur_ans = cur_way;
        int v1 = rand() % n + 1;
        int v2 = rand() % n + 1;
        if (v1 > v2) {
            int t = v1;
            v1 = v2;
            v2 = t;
        }
        if (v1 != v2) {
            reverse(cur_ans.begin() + v1, cur_ans.begin() + v2);
            double cur_len = 0;
            for (int i = 0; i < n; ++i) {
                cur_len += adj_mat[cur_ans[i]][cur_ans[i + 1]];
            }
            if (found_len > cur_len) {
                cur_way = std::move(cur_ans);
                found_len = cur_len;
            }
        } else {
            continue;
        }
    }
    for (int v : cur_way) cout << v + 1 << " ";
    cout << "\n";
    return 0;
}
