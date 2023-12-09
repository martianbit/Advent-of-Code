#include <aoc.hpp>

vector<vector<ll>> seqs;

void parse(string s, stringstream &ss, ll li) {
    seqs.emplace_back();
    auto p1 = split(s);
    transform(all(p1), back_inserter(seqs.back()), [](auto a) { return stoll(a); });
}

void master() {
    for(auto &x : seqs) {
        reverse(all(x));
        vector<vector<ll>> diffs = { x };

        while(any_of(all(diffs.back()), [](auto a) { return a; })) {
            diffs.emplace_back();
            for(ll i = 1; i < (diffs.end() - 2)->size(); i++)
                diffs.back().push_back((*(diffs.end() - 2))[i] - (*(diffs.end() - 2))[i - 1]);
        }

        ans += accumulate(all(diffs), 0, [](auto a, auto b) { return a + b.back(); });
    }
}

