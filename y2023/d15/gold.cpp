#include <aoc.hpp>
vector<pair<string, ll>> initseq;
void parse(string s, stringstream &ss, ll li) {
    auto p1 = split(s, ",");
    for(const auto &x : p1) {
        if(x.back() == '-')
            initseq.push_back({ x.substr(0, x.size() - 1), -1 });
        else {
            auto p2 = split(x, "=");
            initseq.push_back({ p2[0], stoll(p2[1]) });
        }
    }
}
ll my_hash(string s) {
    ll h;
    h = 0;
    for(const auto &x : s)
        h = ((h + x) * 17) % 256;
    return h;
}
void master() {
    ll i, j, h;
    array<vector<pair<string, ll>>, 256> boxes;
    for(const auto &x : initseq) {
        h = my_hash(x.first);
        auto found = find_if(all(boxes[h]), [&](auto &a) { return a.first == x.first; });
        if(x.second == -1) {
            if(found != boxes[h].end())
                boxes[h].erase(found);
        }
        else {
            if(found == boxes[h].end())
                boxes[h].push_back(x);
            else
                found->second = x.second;
        }
    }
    for(i = 0; i < 256; i++) {
        for(j = 0; j < boxes[i].size(); j++)
            ans += (i + 1) * (j + 1) * boxes[i][j].second;
    }
}

