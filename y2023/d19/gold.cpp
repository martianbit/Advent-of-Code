#include <aoc.hpp>
unordered_map<char, ll> xmas = { { 'x', 0 }, { 'm', 1 }, { 'a', 2 }, { 's', 3 } };
unordered_map<string, pair<vector<tuple<ll, bool, ll, string>>, string>> workflows;
void parse(string s, stringstream &ss, ll li) {
    ll i;
    if(s.empty() || s[0] == '{')
        return;
    auto p1 = split(s, "{");
    auto p2 = split(p1[1].substr(0, p1[1].size() - 1), ",");
    workflows[p1[0]] = { {}, p2.back() };
    for(i = 0; i < p2.size() - 1; i++)
        workflows[p1[0]].first.push_back({ xmas[p2[i][0]], (p2[i][1] == '<'), stoll(p2[i].substr(2)), split(p2[i], ":")[1] });
}
void trace(string wf, array<array<ll, 2>, 4> ratings) {
    if(wf == "R")
        return;
    if(wf == "A") {
        ans += accumulate(all(ratings), 1LL, [](auto a, const auto &b) { return a * max(b[1] - b[0], 0LL); });
        return;
    }
    for(const auto &x : workflows[wf].first) {
        auto nr = ratings;
        nr[get<0>(x)][get<1>(x)] = get<2>(x) + !get<1>(x);
        ratings[get<0>(x)][!get<1>(x)] = get<2>(x) + !get<1>(x);
        trace(get<3>(x), nr);
    }
    trace(workflows[wf].second, ratings);
}
void master() {
    ll i;
    array<array<ll, 2>, 4> ratings;
    for(i = 0; i < 4; i++)
        ratings[i] = { 1, 4001 };
    trace("in", ratings);
}

