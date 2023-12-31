#include <aoc.hpp>

unordered_map<string, ll> bids;

void parse(string s, stringstream &ss, ll li) {
    auto p1 = split(s);
    bids[p1[0]] = stoll(p1[1]);
}

void master() {
    ll type, rank, joker;
    array<vector<string>, 7> types;

    for(const auto &x : bids) {
        unordered_map<char, ll> counts;
        joker = 0;

        for(const auto &y : x.first) {
            if(y == 'J') {
                joker++;
                continue;
            }

            if(counts.find(y) == counts.end())
                counts[y] = 0;

            counts[y]++;
        }

        vector<ll> N;
        transform(all(counts), back_inserter(N), [](auto a) { return a.second; });
        sort(all(N), greater());

        if(N.empty())
            N.emplace_back();

        N[0] += joker;

        if(N == vector<ll>{ 5 })
            type = 6;
        else if(N == vector<ll>{ 4, 1 })
            type = 5;
        else if(N == vector<ll>{ 3, 2 })
            type = 4;
        else if(N == vector<ll>{ 3, 1, 1 })
            type = 3;
        else if(N == vector<ll>{ 2, 2, 1 })
            type = 2;
        else if(N == vector<ll>{ 2, 1, 1, 1 })
            type = 1;
        else if(N == vector<ll>{ 1, 1, 1, 1, 1 })
            type = 0;
        else
            exit(1);

        types[type].push_back(x.first);
    }

    rank = 1;

    for(auto &x : types) {
        sort(all(x), [](auto a, auto b) {
            string strength = "AKQT98765432J";

            for(ll i = 0; i < 5; i++) {
                if(a[i] != b[i])
                    return strength.find(a[i]) > strength.find(b[i]);
            }

            return false;
        });

        for(const auto &y : x)
            ans += rank++ * bids[y];
    }
}

