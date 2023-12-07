#include <aoc.hpp>

vector<string> lines;

void parse(string s, stringstream &ss, ll li) {
    lines.push_back(s + '.');
}

void master() {
    ll nx, ny;
    string cn;
    unordered_set<ll> gears;
    unordered_map<ll, vector<ll>> adj;

    loop(lines, i, x) {
        loop(x, j, y) {
            if(!isdigit(y)) {
                if(!cn.empty()) {
                    for(const auto &z : gears) {
                        if(adj.find(z) == adj.end())
                            adj[z] = {};
                        adj[z].push_back(stoi(cn));
                    }

                    gears.clear();
                }

                cn = "";
                continue;
            }

            cn += y;

            for(const auto &z : D8) {
                nx = j + z[0];
                ny = i + z[1];

                if(nx >= 0 && nx < x.size() && ny >= 0 && ny < lines.size() && lines[ny][nx] == '*')
                    gears.insert(ny * x.size() + nx);
            }
        }
    }

    ans = accumulate(all(adj), 0, [](auto a, auto b) {
        return a + ((b.second.size() == 2) ? reduce(all(b.second), 1, multiplies()) : 0);
    });
}

