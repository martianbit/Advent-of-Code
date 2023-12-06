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
    vector<ll> mappings = almanac[0][0];

    for(ll i = 1; i < almanac.size(); i++) {
        vector<bool> mapped(mappings.size(), false);

        for(const auto &x : almanac[i]) {
            loop(mappings, j, y) {
                if(y >= x[1] && y < x[1] + x[2] && !mapped[j]) {
                    y += x[0] - x[1];
                    mapped[j] = true;
                }
            }
        }
    }

    ans = *min_element(all(mappings));
}

