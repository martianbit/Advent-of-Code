#include <aoc.hpp>
#define BC "broadcaster"
unordered_map<string, pair<char, vector<string>>> mods;
void parse(string s, stringstream &ss, ll li) {
    auto p1 = split(s, " -> ");
    auto p2 = split(p1[1], ", ");
    if(p1[0] == BC)
        mods[p1[0]] = { -1, p2 };
    else
        mods[p1[0].substr(1)] = { p1[0][0], p2 };
}
void master() {
    bool ok;
    ll i, lo, hi;
    // pulse, name, from
    queue<tuple<bool, string, string>> q;
    unordered_map<string, bool> ff;
    unordered_map<string, unordered_map<string, bool>> con;
    for(const auto &x : mods) {
        if(x.first == BC)
            continue;
        if(x.second.first)
            ff[x.first] = false;
        for(const auto &y : x.second.second) {
            if(con.find(y) == con.end())
                con[y] = {};
            con[y][x.first] = false;
        }
    }
    lo = hi = 0;
    for(i = 0; i < 1000; i++) {
        q.push({ false, BC, "button" });
        while(!q.empty()) {
            tuple<bool, string, string> cs = q.front();
            q.pop();
            if(get<0>(cs))
                hi++;
            else
                lo++;
            if(get<1>(cs) == BC) {
                for(const auto &x : mods[BC].second)
                    q.push({ false, x, BC });
                continue;
            }
            switch(mods[get<1>(cs)].first) {
                case '%':
                    if(get<0>(cs))
                        break;
                    ff[get<1>(cs)] = !ff[get<1>(cs)];
                    for(const auto &x : mods[get<1>(cs)].second)
                        q.push({ ff[get<1>(cs)], x, get<1>(cs) });
                    break;
                case '&':
                    con[get<1>(cs)][get<2>(cs)] = get<0>(cs);
                    ok = true;
                    for(const auto &x : con[get<1>(cs)]) {
                        if(!x.second) {
                            ok = false;
                            break;
                        }
                    }
                    for(const auto &x : mods[get<1>(cs)].second)
                        q.push({ !ok, x, get<1>(cs) });
            }
        }
    }
    ans = lo * hi;
}

