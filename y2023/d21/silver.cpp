#include <aoc.hpp>
#define TOT_STEPS 64LL
vector<string> grid;
void parse(string s, stringstream &ss, ll li) {
    grid.push_back(s);
}
void master() {
    ll i, j, nx, ny;
    unordered_set<ll> seen;
    array<ll, 2> sp;
    for(i = 0; i < grid.size(); i++) {
        auto found = grid[i].find('S');
        if(found != string::npos) {
            sp = { (ll) found, i };
            break;
        }
    }
    seen.insert(sp[0] | (sp[1] << 32));
    for(i = 0; i < TOT_STEPS; i++) {
        unordered_set<ll> ns;
        for(const auto &x : seen) {
            for(j = 0; j < 4; j++) {
                nx = (x & ((1LL << 32) - 1)) + D4[j][0];
                ny = (x >> 32) + D4[j][1];
                if(!(0 <= nx && nx < grid[0].size() && 0 <= ny && ny < grid.size() && grid[ny][nx] != '#'))
                    continue;
                ns.insert(nx | (ny << 32));
            }
        }
        seen = ns;
    }
    ans = seen.size();
}

