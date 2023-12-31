#include <aoc.hpp>
#define CYCLES 1000000000
vector<string> positions;
void parse(string s, stringstream &ss, ll li) {
    positions.push_back(s);
}
void tilt(ll dx, ll dy, ll limit) {
    ll i, j, k;
    for(i = (dy > 0 ? limit : 0); i != (dy > 0 ? -1 : positions.size()); i += (dy > 0 ? -1 : 1)) {
        for(j = (dx > 0 ? limit : 0); j != (dx > 0 ? -1 : positions[0].size()); j += (dx > 0 ? -1 : 1)) {
            if(positions[i][j] != 'O')
                continue;
            for(k = (dx ? j : i); k != limit && positions[dy ? (k + dy) : i][dx ? (k + dx) : j] == '.'; k += (dx ? dx : dy));
            positions[i][j] = '.';
            positions[dy ? k : i][dx ? k : j] = 'O';
        }
    }
}
void do_cycle() {
    tilt(0, -1, 0);
    tilt(-1, 0, 0);
    tilt(0, 1, positions.size() - 1);
    tilt(1, 0, positions[0].size() - 1);
}
void master() {
    bool simplified;
    ll i;
    unordered_map<string, ll> seen;
    simplified = false;
    for(i = 0; i < CYCLES; i++) {
        do_cycle();
        if(simplified)
            continue;
        string key;
        for(const auto &x : positions)
            key += x;
        auto found = seen.find(key);
        if(found != seen.end()) {
            i = CYCLES - 1 - (CYCLES - i - 1) % (i - found->second);
            simplified = true;
            seen.clear();
            continue;
        }
        seen[key] = i;
    }
    loop(positions, i, x)
        ans += count(all(x), 'O') * (positions.size() - i);
}

