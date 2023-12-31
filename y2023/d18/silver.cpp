#include <aoc.hpp>
vector<pair<char, ll>> plan;
void parse(string s, stringstream &ss, ll li) {
    auto p1 = split(s);
    plan.push_back({ p1[0][0], stoll(p1[1]) });
}
void master() {
    ll i;
    array<ll, 2> cp, bx, by;
    set<array<ll, 2>> trench;
    cp = { 0, 0 };
    bx = by = { INF, -INF };
    trench.insert(cp);
    for(const auto &x : plan) {
        for(i = 0; i < x.second; i++) {
            switch(x.first) {
                case 'R':
                    cp[0]++;
                    break;
                case 'D':
                    cp[1]++;
                    break;
                case 'L':
                    cp[0]--;
                    break;
                case 'U':
                    cp[1]--;
            }
            bx[0] = min(bx[0], cp[0]);
            bx[1] = max(bx[1], cp[0]);
            by[0] = min(by[0], cp[1]);
            by[1] = max(by[1], cp[1]);
            trench.insert(cp);
        }
    }
    vector<vector<bool>> view(by[1] - by[0] + 1, vector<bool>(bx[1] - bx[0] + 1, false));
    for(const auto &x : trench)
        view[x[1] - by[0]][x[0] - bx[0]] = true;
    flood_fill(find(all(view[1]), true) - view[1].begin() + 1, 1, true, {false}, true, view, D4);
    for(const auto &x : view)
        ans += count(all(x), true);
}

