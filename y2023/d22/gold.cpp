#include <aoc.hpp>
vector<array<ll, 6>> bricks;
void parse(string s, stringstream &ss, ll li) {
    ll i;
    auto p1 = split(replace(s, "~", ","), ",");
    bricks.emplace_back();
    for(i = 0; i < 6; i++)
        bricks.back()[i] = stoll(p1[i]);
}
void master() {
    ll i, j, k, l;
    array<ll, 6> borders;
    for(i = 0; i < 3; i++)
        borders[i] = INF;
    for(i = 3; i < 6; i++)
        borders[i] = -INF;
    for(const auto &x : bricks) {
        for(i = 0; i < 3; i++)
            borders[i] = min(borders[i], x[i]);
        for(i = 3; i < 6; i++)
            borders[i] = max(borders[i], x[i]);
    }
    vector<vector<vector<ll>>> space(borders[5] - borders[2] + 1, vector<vector<ll>>(borders[4] - borders[1] + 1, vector<ll>(borders[3] - borders[0] + 1, -1)));
    for(i = 0; i < bricks.size(); i++) {
        for(j = bricks[i][2]; j <= bricks[i][5]; j++) {
            for(k = bricks[i][1]; k <= bricks[i][4]; k++) {
                for(l = bricks[i][0]; l <= bricks[i][3]; l++)
                    space[space.size() - j + borders[2] - 1][space[0].size() - k + borders[1] - 1][space[0][0].size() - l + borders[0] - 1] = i;
            }
        }
    }
    while(true) {
        vector<bool> rtm(bricks.size(), true);
        for(i = 0; i < space.size(); i++) {
            for(j = 0; j < space[0].size(); j++) {
                for(k = 0; k < space[0][0].size(); k++) {
                    if(space[i][j][k] != -1 && (i >= space.size() - 1 || (space[i + 1][j][k] != -1 && space[i + 1][j][k] != space[i][j][k])))
                        rtm[space[i][j][k]] = false;
                }
            }
        }
        for(i = space.size() - 2; i >= 0; i--) {
            for(j = 0; j < space[0].size(); j++) {
                for(k = 0; k < space[0][0].size(); k++) {
                    if(rtm[space[i][j][k]]) {
                        space[i + 1][j][k] = space[i][j][k];
                        space[i][j][k] = -1;
                    }
                }
            }
        }
        if(all_of(all(rtm), [](auto a) { return !a; }))
            break;
    }
    vector<vector<bool>> supported_by(bricks.size(), vector<bool>(bricks.size(), false));
    for(i = 0; i < space.size() - 1; i++) {
        for(j = 0; j < space[0].size(); j++) {
            for(k = 0; k < space[0][0].size(); k++) {
                if(space[i][j][k] != -1 && space[i + 1][j][k] != -1 && space[i][j][k] != space[i + 1][j][k])
                    supported_by[space[i][j][k]][space[i + 1][j][k]] = true;
            }
        }
    }
    for(i = 0; i < bricks.size(); i++) {
        queue<ll> q;
        auto nsb = supported_by;
        ans--;
        q.push(i);
        while(!q.empty()) {
            auto cb = q.front();
            q.pop();
            ans++;
            for(j = 0; j < bricks.size(); j++) {
                if(!nsb[j][cb])
                    continue;
                nsb[j][cb] = false;
                if(all_of(all(nsb[j]), [](auto a) { return !a; }))
                    q.push(j);
            }
        }
    }
}

