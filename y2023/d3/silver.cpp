#include <aoc.hpp>

vector<string> lines;

void parse(string s, stringstream &ss, ll li) {
    lines.push_back(s + '.');
}

void master() {
    bool ok;
    ll nx, ny;
    string cn;

    ok = false;

    loop(lines, i, x) {
        loop(x, j, y) {
            if(!isdigit(y)) {
                if(!cn.empty() && ok)
                    ans += stoi(cn);

                ok = false;
                cn = "";

                continue;
            }

            cn += y;

            for(ll k = 0; !ok && k < 8; k++) {
                nx = j + D8[k][0];
                ny = i + D8[k][1];

                ok = (nx >= 0 &&
                      nx < x.size() &&
                      ny >= 0 &&
                      ny < lines.size() &&
                      lines[ny][nx] != '.' && !isdigit(lines[ny][nx]));
            }
        }
    }
}

