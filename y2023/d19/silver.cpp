#include <aoc.hpp>
unordered_map<char, ll> xmas = { { 'x', 0 }, { 'm', 1 }, { 'a', 2 }, { 's', 3 } };
unordered_map<string, pair<vector<tuple<ll, bool, ll, string>>, string>> workflows;
vector<array<ll, 4>> ratings;
void parse(string s, stringstream &ss, ll li) {
    ll i;
    if(s.empty())
        return;
    if(s[0] == '{') {
        auto p1 = split(s.substr(1, s.size() - 2), ",");
        ratings.emplace_back();
        for(i = 0; i < 4; i++)
            ratings.back()[i] = stoll(p1[i].substr(2));
    }
    else {
        auto p1 = split(s, "{");
        auto p2 = split(p1[1].substr(0, p1[1].size() - 1), ",");
        workflows[p1[0]] = { {}, p2.back() };
        for(i = 0; i < p2.size() - 1; i++)
            workflows[p1[0]].first.push_back({ xmas[p2[i][0]], (p2[i][1] == '<'), stoll(p2[i].substr(2)), split(p2[i], ":")[1] });
    }
}
bool trace(string wf, const array<ll, 4> &rating) {
    if(wf == "A")
        return true;
    else if(wf == "R")
        return false;
    for(const auto &x : workflows[wf].first) {
        if((get<1>(x) && rating[get<0>(x)] < get<2>(x)) || (!get<1>(x) && rating[get<0>(x)] > get<2>(x)))
            return trace(get<3>(x), rating);
    }
    return trace(workflows[wf].second, rating);
}
void master() {
    for(const auto &x : ratings)
        ans += trace("in", x) * reduce(all(x));
}

