#include <aoc.hpp>
vector<pair<string, vector<ll>>> records;
void parse(string s, stringstream &ss, ll li) {
    records.emplace_back();
    auto p1 = split(s);
    records.back().first = p1[0];
    auto p2 = split(p1[1], ",");
    transform(all(p2), back_inserter(records.back().second), [](auto a) { return stoll(a); });
}
ll solve(ll ci, ll gi, ll streak, const pair<string, vector<ll>> &record) {
    ll sol;
    if(ci >= record.first.size())
        sol = ((gi >= record.second.size() && !streak) || (gi == record.second.size() - 1 && streak == record.second.back()));
    else {
        sol = 0;
        for(const auto &x : ".#") {
            if(!(x == record.first[ci] || record.first[ci] == '?'))
                continue;
            switch(x) {
                case '.':
                    if(streak) {
                        if(gi < record.second.size() && streak == record.second[gi])
                            sol += solve(ci + 1, gi + 1, 0, record);
                    }
                    else
                        sol += solve(ci + 1, gi, 0, record);
                    break;
                case '#':
                    sol += solve(ci + 1, gi, streak + 1, record);
            }
        }
    }
    return sol;
}
void master() {
    for(const auto &x : records)
        ans += solve(0, 0, 0, x);
}

