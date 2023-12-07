#include <aoc.hpp>

array<vector<ll>, 2> races;

void parse(string s, stringstream &ss, ll li) {
    auto p1 = split(s);
    transform(p1.begin() + 1, p1.end(), back_inserter(races[li]), [](auto a) { return stoll(a); });
}

void master() {
    double D;

    ans = 1;

    for(ll i = 0; i < races[0].size(); i++) {
        D = sqrt(pow(races[0][i], 2) - 4 * races[1][i]);
        ans *= ceil((races[0][i] + D) / 2) - floor((races[0][i] - D) / 2) - 1;
    }
}

