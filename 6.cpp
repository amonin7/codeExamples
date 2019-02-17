#include <iostream>
#include <set>
#include <vector>
using namespace std;
int am_v;
vector<set<int>> adj_mat;
bool if_one_empty() {
    for (int i = 0; i < adj_mat.size(); ++i) {
        if (!adj_mat[i].empty()) {
            return false;
        }
    }
    return true;
}
int main() {
    cin >> am_v;
    adj_mat.resize(am_v);
    int cur_vertex_deg;
    int cur_v;
    for (int i = 0; i < am_v; ++i) {
        cin >> cur_vertex_deg;
        for (int j = 0; j < cur_vertex_deg; ++j) {
            cin >> cur_v;
            adj_mat[i].insert(cur_v);
        }
    }
    int min_cover_size = 0;
    bool flag = false;
    while(!flag) {
        for (int i = 0; i < am_v; ++i) {
            if (adj_mat[i].size() == 1) {
                min_cover_size += 1;
                int cur_p = *(adj_mat[i].begin());
                for (auto& v: adj_mat[cur_p]) {
                    adj_mat[v].erase(cur_p);
                }
                adj_mat[cur_p].clear();
            }
        }
        flag = if_one_empty();
    }
    cout << min_cover_size;
}
