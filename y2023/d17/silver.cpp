#include <aoc.hpp>
vector<vector<ll>> blocks;
void parse(string s, stringstream &ss, ll li) {
    blocks.emplace_back();
    transform(all(s), back_inserter(blocks.back()), [](auto a) { return a - '0'; });
}
void master() {
    ll i;
    priority_queue<array<ll, 5>> q;
    unordered_set<string> vis;
    q.push({ blocks[0][0], 0, 0, 3, 0 });
    while(!q.empty()) {
        auto cs = q.top();
        q.pop();
        if(!(0 <= cs[1] && cs[1] < blocks[0].size() && 0 <= cs[2] && cs[2] < blocks.size()))
            continue;
        cs[0] -= blocks[cs[2]][cs[1]];
        if(cs[1] >= blocks[0].size() - 1 && cs[2] >= blocks.size() - 1) {
            ans = -cs[0];
            break;
        }
        string key;
        for(i = 1; i < 5; i++)
            key += to_string(cs[i]) + " ";
        if(vis.find(key) != vis.end())
            continue;
        vis.insert(key);
        for(i = 0; i < 4; i++) {
            if(!((D4[i][0] == -D4[cs[3]][0] && D4[i][1] == -D4[cs[3]][1]) || (i == cs[3])))
                q.push({ cs[0], cs[1] + D4[i][0], cs[2] + D4[i][1], i, 1 });
        }
        if(cs[4] < 3)
            q.push({ cs[0], cs[1] + D4[cs[3]][0], cs[2] + D4[cs[3]][1], cs[3], cs[4] + 1 });
    }
}

