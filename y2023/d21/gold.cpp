#include <aoc.hpp>
#define TOT_STEPS 26501365LL
#define SKIP 524LL
#define VS 393LL
vector<string> grid;
void parse(string s, stringstream &ss, ll li) {
    grid.push_back(s);
}
void master() {
    ll i, j, gs, diff;
    Point sp, np;
    vector<ll> values, d2s, as, ds;
    unordered_set<ll> seen;
    assert(grid.size() == grid[0].size());
    gs = grid.size();
    for(i = 0; i < gs; i++) {
        auto found = grid[i].find('S');
        if(found != string::npos) {
            sp = { .x = (int) found, .y = (int) i };
            break;
        }
    }
    seen.insert(sp.key);
    for(i = 0; values.size() < VS; i++) {
        unordered_set<ll> ns;
        for(const auto &x : seen) {
            for(j = 0; j < 4; j++) {
                np = { .key = x };
                np.x += D4[j][0];
                np.y += D4[j][1];
                if(grid[mod(np.y, gs)][mod(np.x, gs)] == '#')
                    continue;
                ns.insert(np.key);
            }
        }
        seen = ns;
        if(i >= SKIP)
            values.push_back(seen.size());
    }
    for(i = 2; i < values.size(); i++)
        d2s.push_back(values[i] + values[i - 2] - 2 * values[i - 1]);
    vector<vector<ll>> seqs(gs);
    for(i = 0; i < d2s.size(); i++)
        seqs[i % gs].push_back(d2s[i]);
    for(i = 0; i < gs; i++) {
        as.push_back(seqs[i][0]);
        ds.push_back(seqs[i][1] - seqs[i][0]);
    }
    diff = values[1] - values[0];
    ans = values[0];
    for(i = 0; i < TOT_STEPS - SKIP - 1; i++) {
        ans += diff;
        diff += as[i % gs];
        as[i % gs] += ds[i % gs];
    }
}

