#include <aoc.hpp>

vector<array<unordered_set<ll>, 2>> cards;

void parse(string s, stringstream &ss, ll li) {
    auto p1 = split(s);

    cards.emplace_back();

    for(ll i = 2, j = 0; i < p1.size(); i++) {
        if(p1[i] == "|")
            j++;
        else
            cards.back()[j].insert(stoll(p1[i]));
    }
}

void master() {
    ll matches;
    vector<ll> N(cards.size(), 1);

    loop(cards, i, x) {
        matches = count_if(all(x[1]), [&](auto a) { return x[0].contains(a); });

        for(ll j = 0; j < matches; j++)
            N[j + i + 1] += N[i];
    }

    ans = reduce(all(N));
}

