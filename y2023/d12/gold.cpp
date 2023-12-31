#include <aoc.hpp>
#define N 5
vector<pair<string, vector<ll>>> records;
void parse(string s, stringstream &ss, ll li) {
    ll i;
    records.emplace_back();
    auto p1 = split(s);
    for(i = 1; i < N; i++)
        records.back().first += p1[0] + '?';
    records.back().first += p1[0];
    auto p2 = split(p1[1], ",");
    for(i = 0; i < N; i++)
        transform(all(p2), back_inserter(records.back().second), [](auto a) { return stoll(a); });
}
ll solve(ll ci, ll gi, ll streak, const pair<string, vector<ll>> &record, unordered_map<string, ll> &dp) {
    ll sol;
    string key = to_string(ci) + " " + to_string(gi) + " " + to_string(streak);
    auto found = dp.find(key);
    if(found == dp.end()) {
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
                                sol += solve(ci + 1, gi + 1, 0, record, dp);
                        }
                        else
                            sol += solve(ci + 1, gi, 0, record, dp);
                        break;
                    case '#':
                        sol += solve(ci + 1, gi, streak + 1, record, dp);
                }
            }
        }
        dp[key] = sol;
    }
    else
        sol = found->second;
    return sol;
}
void master() {
    for(const auto &x : records) {
        unordered_map<string, ll> dp;
        ans += solve(0, 0, 0, x, dp);
    }
}

