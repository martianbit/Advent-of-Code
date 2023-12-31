#include <aoc.hpp>

#define EXPAND_RATE 1000000

vector<string> image;

void parse(string s, stringstream &ss, ll li) {
    image.push_back(s);
}

ll solve(vector<ll> &g) {
    ll lb, ds, s;

    lb = ds = s = 0;

    for(ll i = 0; i < g.size(); i++) {
        if(g[i]) {
            s += g[i] * ds;
            lb += g[i];
            ds += lb;
        }
        else
            ds += EXPAND_RATE * lb;
    }

    return s;
}

void master() {
    vector<ll> gr(image.size(), 0);
    vector<ll> gc(image[0].size(), 0);

    for(ll i = 0; i < image.size(); i++) {
        for(ll j = 0; j < image[0].size(); j++) {
            if(image[i][j] == '.')
                continue;

            gr[i]++;
            gc[j]++;
        }
    }

    ans = solve(gr) + solve(gc);
}

