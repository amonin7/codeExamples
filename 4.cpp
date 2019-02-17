#include <math.h>
#include <iostream>
#include <bitset>
#include <vector>
#include <climits>
using namespace std;
int n, k;
vector < vector<double> > adj_mat;
vector<pair<int, int>> coord;
double dist(pair<int, int> c1, pair<int, int> c2) {
    return sqrt((c1.first - c2.first) * (c1.first - c2.first) +
                (c1.second - c2.second) * (c1.second - c2.second));
}
vector<int> input() {
    int min_x = INT_MAX / 2, max_x = -INT_MAX / 2, min_y = INT_MAX / 2, max_y = -INT_MAX / 2;
    for (int i = 0; i < n; ++i) {
        cin >> coord[i].first >> coord[i].second;
        if (max_x < coord[i].first) {
            max_x = coord[i].first;
        }
        if (min_x > coord[i].first) {
            min_x = coord[i].first;
        }
        if (max_y < coord[i].second) {
            max_y = coord[i].second;
        }
        if (min_y > coord[i].second) {
            min_y = coord[i].second;
        }
        for (int j = 0; j < i; ++j) {
            double d = dist(coord[i], coord[j]);
            adj_mat[i][j] = d;
            adj_mat[j][i] = d;
        }
    }
    return {max_x, min_x, max_y, min_y};
}
double prim() {
    const double max = INT_MAX / 2 - 1;
    double min_dist = 0;
    vector<bool> used (adj_mat.size());
    vector<double> weight_min_edge (adj_mat.size(), max);
    vector<int> end_min_edge (adj_mat.size(), -1);
    weight_min_edge[0] = 0;
    for (int i=0; i<adj_mat.size(); ++i) {
        int v = -1;
        for (int j=0; j<adj_mat.size(); ++j)
            if (!used[j] && (v == -1 || weight_min_edge[j] < weight_min_edge[v]))
                v = j;
        used[v] = true;
        if (end_min_edge[v] != -1)
            min_dist += adj_mat[v][end_min_edge[v]];
        for (int i=0; i<adj_mat.size(); ++i)
            if (adj_mat[v][i] < weight_min_edge[i]) {
                weight_min_edge[i] = adj_mat[v][i];
                end_min_edge[i] = v;
            }
    }
    return min_dist;
}
int addit(int left, int right) {
    if (right - left < 500) return 1;
    else if (right - left < 1000) return 2;
    else if (right - left < 2000) return 4;
    else if (right - left < 4000) return 8;
    else if (right - left < 8000) return 16;
    else return 32;
}
int main() {
    cin >> n >> k;
    adj_mat.resize(n, vector<double>(n, 0));
    coord.resize(n);
    vector<int> max_min = input();
    vector<pair<int, int>> result;
    double clean_min = prim();
    double min = 0;
    for (int am_r = 0; am_r < k; ++am_r) { //amount routers
        vector<vector<double>> new_mat;
        double min_w_am = 0; // minimal with all positions of router
        int x_new = -1, y_new = -1;
        for (int x = max_min[1] + 1; x < max_min[0]; x += addit(max_min[1], max_min[0])) {
            for (int y = max_min[3] + 1; y < max_min[2]; y += addit(max_min[3], max_min[2])) {
                bool flag = false;
                for (int i = 0; i < coord.size(); ++i) {
                    if (coord[i].first == x && coord[i].second == y) {
                        flag = true;
                    }
                }
                if (flag) continue;
                adj_mat.push_back(vector<double>(n + 1, 0));
                for (int j = 0; j < n; ++j) {
                    double d = dist(coord[j], make_pair(x, y));
                    adj_mat[j].push_back(d);
                    adj_mat[n][j] = d;
                }
                double cur_min = prim();
                if (min_w_am == 0 || min_w_am > cur_min) {
                    new_mat = adj_mat;
                    min_w_am = cur_min;
                    x_new = x;
                    y_new = y;
                }
                adj_mat.pop_back();
                for (int i = 0; i < n; ++i) {
                    adj_mat[i].pop_back();
                }
            }
        }
        if (min > min_w_am || min == 0) {
            min = min_w_am;
            adj_mat = std::move(new_mat);
            ++n;
            coord.emplace_back(make_pair(x_new, y_new));
            result.emplace_back(make_pair(x_new, y_new));
        } else {
            break;
        }
    }
    if (min >= clean_min) {
        cout << "0" << endl;
        return 0;
    } else {
        cout << result.size() << endl;
        for (pair<int, int> coordinates : result) {
            cout << coordinates.first << " " << coordinates.second << endl;
        }
    }
    return 0;
}
