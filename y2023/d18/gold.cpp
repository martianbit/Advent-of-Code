#include <aoc.hpp>
vector<pair<char, ll>> plan;
void parse(string s, stringstream &ss, ll li) {
    auto p1 = split(s);
    plan.push_back({ "RDLU"[p1[2][p1[2].size() - 2] - '0'], stoll(p1[2].substr(2, 5), nullptr, 16) });
}
void master() {
    ll i, j, cx, cy, nx, ny, x0, y0, x1, y1;
    set<ll> XS, YS;
    cx = cy = 0;
    XS = YS = { 0, 1 };
    for(const auto &x : plan) {
        switch(x.first) {
            case 'R':
                cx += x.second;
                break;
            case 'D':
                cy += x.second;
                break;
            case 'L':
                cx -= x.second;
                break;
            case 'U':
                cy -= x.second;
        }
        XS.insert(cx);
        YS.insert(cy);
        XS.insert(cx + 1);
        YS.insert(cy + 1);
    }
    vector<ll> X(all(XS));
    vector<ll> Y(all(YS));
    vector<vector<bool>> view(Y.size() - 1, vector<bool>(X.size() - 1, false));
    nx = ny = 0;
    for(const auto &x : plan) {
        cx = nx;
        cy = ny;
        switch(x.first) {
            case 'R':
                nx += x.second;
                break;
            case 'D':
                ny += x.second;
                break;
            case 'L':
                nx -= x.second;
                break;
            case 'U':
                ny -= x.second;
        }
        x0 = lower_bound(all(X), cx) - X.begin();
        y0 = lower_bound(all(Y), cy) - Y.begin();
        x1 = lower_bound(all(X), nx) - X.begin();
        y1 = lower_bound(all(Y), ny) - Y.begin();
        for(i = min(y0, y1); i <= max(y0, y1); i++) {
            for(j = min(x0, x1); j <= max(x0, x1); j++)
                view[i][j] = true;
        }
    }
    flood_fill(find(all(view[1]), true) - view[1].begin() + 1, 1, true, {false}, true, view, D4);
    for(i = 0; i < view.size(); i++) {
        for(j = 0; j < view[0].size(); j++)
            ans += view[i][j] * (X[j + 1] - X[j]) * (Y[i + 1] - Y[i]);
    }
}

