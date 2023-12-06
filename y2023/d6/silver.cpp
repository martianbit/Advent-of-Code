#include <aoc.hpp>

array<vector<ll>, 2> race;

void parse(string s, stringstream &ss, ll li) {
    auto p1 = split(s);
    transform(p1.begin() + 1, p1.end(), back_inserter(race[li]), [](auto a) { return stoll(a); });
}

void master() {
    double D;

    ans = 1;

    for(ll i = 0; i < race[0].size(); i++) {
        D = sqrt(pow(race[0][i], 2) - 4 * race[1][i]);
        ans *= ceil((race[0][i] + D) / 2) - floor((race[0][i] - D) / 2) - 1;
    }
}

