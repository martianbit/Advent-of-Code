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
    ll steps;
    // pulse, name, from
    queue<tuple<bool, string, string>> q;
    unordered_map<string, bool> ff;
    unordered_map<string, unordered_map<string, bool>> con;
    string to_rx;
    // name => times encountered, last seen, cycle length
    unordered_map<string, array<ll, 3>> watch;
    unordered_map<string, array<ll, 3>>::iterator found;
    for(const auto &x : mods) {
        if(x.first == BC)
            continue;
        if(x.second.first)
            ff[x.first] = false;
        for(const auto &y : x.second.second) {
            if(con.find(y) == con.end())
                con[y] = {};
            con[y][x.first] = false;
            if(y == "rx")
                to_rx = x.first;
        }
    }
    for(const auto &x : mods) {
        for(const auto &y : x.second.second) {
            if(y == to_rx) {
                watch[x.first] = { 0, 0, 0 };
                break;
            }
        }
    }
    for(steps = 0;;++steps) {
        q.push({ false, BC, "button" });
        while(!q.empty()) {
            tuple<bool, string, string> cs = q.front();
            q.pop();
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
                    ok = true; // all hi?
                    for(const auto &x : con[get<1>(cs)]) {
                        if(!x.second) {
                            ok = false;
                            break;
                        }
                    }
                    if(!ok) {
                        found = watch.find(get<1>(cs));
                        if(found != watch.end()) {
                            if(found->second[0] >= 2)
                                found->second[2] = steps - found->second[1];
                            found->second[0]++;
                            found->second[1] = steps;
                            for(const auto &x : watch) {
                                if(x.second[0] < 3)
                                    goto notdone;
                            }
                            goto done;
                            notdone:;
                        }
                    }
                    for(const auto &x : mods[get<1>(cs)].second)
                        q.push({ !ok, x, get<1>(cs) });
            }
        }
    }
    done:;
    ans = watch.begin()->second[2];
    for(auto it = ++watch.begin(); it != watch.end(); it++)
        ans = lcm(ans, it->second[2]);
}

