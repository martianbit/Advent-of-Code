#include <aoc.hpp>

vector<vector<vector<ll>>> almanac = {{}};

void parse(string s, stringstream &ss, ll li) {
    if(s.empty()) {
        almanac.push_back({});
        return;
    }

    if(s.substr(0, 7) == "seeds: ")
        while(ss.get() != ' ');
    else if(!isdigit(s[0]))
        return;

    almanac.back().push_back({});

    while(ss) {
        almanac.back().back().push_back(0);
        ss >> almanac.back().back().back();
        ss.get();
    }
}

void master() {
    vector<array<ll, 2>> ranges;
    ll ols, ole;

    for(ll i = 0; i < almanac[0][0].size(); i += 2)
        ranges.push_back({ almanac[0][0][i], almanac[0][0][i] + almanac[0][0][i + 1] });

    for(ll i = 1; i < almanac.size(); i++) {
        vector<array<ll, 2>> nrs;

        for(const auto &x : ranges) {
            vector<array<ll, 2>> ol;

            for(const auto &y : almanac[i]) {
                ols = max(x[0], y[1]);
                ole = min(x[1], y[1] + y[2]);

                if(ole > ols) {
                    nrs.push_back({ ols + y[0] - y[1], ole + y[0] - y[1] });
                    ol.push_back({ ols, ole });
                }
            }

            sort(all(ol), [](auto a, auto b) { return a[0] < b[0]; });

            if(ol.size() > 0) {
                if(ol[0][0] > x[0])
                    nrs.push_back({ x[0], ol[0][0] });

                if(x[1] > ol.back()[1])
                    nrs.push_back({ ol.back()[1], x[1] });
            }
            else
                nrs.push_back({ x[0], x[1] });

            for(ll j = 1; j < ol.size(); j++) {
                if(ol[j][0] > ol[j - 1][1])
                    nrs.push_back({ ol[j - 1][1], ol[j][0] });
            }
        }

        ranges = nrs;
    }

    ans = (*min_element(all(ranges), [](auto a, auto b) { return a[0] < b[0]; }))[0];
}

