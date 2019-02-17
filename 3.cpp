#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
using namespace std;
vector<pair<int, int>> edges;
int n, m, k;
bool if_a_cover(vector<bool>& cover) {
    for (size_t i = 0; i != edges.size(); ++i) {
        if (cover[edges[i].first] || cover[edges[i].second]) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}
vector<bool> generate_cover() {
    int amount = k + rand() % (n - k + 1);
    vector<bool> cover(n, true);
    for (int i = 0; i < n - amount; ++i) {
        cover[i] = false;
    }
    random_shuffle(cover.begin(), cover.end());
    if (if_a_cover(cover)) {
        return cover;
    } else {
        cover.clear();
        return cover;
    }
}
vector<bool> find_cover() {
    for (int i = 0; i < 100000; ++i) {
        vector<bool> cover = generate_cover();
        if (cover.empty()) {
            continue;
        }
        for (int vertex = 0; vertex < cover.size(); ++vertex) {
            cover[vertex] = false;
            if (if_a_cover(cover)) {
                continue;
            } else {
                cover[vertex] = true;
            }
        }
        int cnt = 0;
        for (int i = 0; i < cover.size(); ++i) {
            if (cover[i]) ++cnt;
        }
        if (cnt == k) return cover;
    }
    return vector<bool>();
}
int main() {
    cin >> n >> m >> k;
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        int v1, v2;
        cin >> v1 >> v2;
        edges[i] = make_pair(v1 - 1, v2 - 1);
    }
    vector<bool> cover = find_cover();
    if (cover.empty()) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        for (int i = 0; i < cover.size(); ++i) {
            if (cover[i]) cout << i + 1 << " ";
        }
        cout << endl;
    }
}
