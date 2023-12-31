#include <aoc.hpp>

string W = "-LF";
string N = "|7F";
string E = "-J7";
string S = "|LJ";

vector<string> sketch;

void parse(string s, stringstream &ss, ll li) {
    sketch.push_back(s);
}

void master() {
    ll sx, sy;
    bool conns[4];
    vector<vector<bool>> vis(sketch.size(), vector<bool>(sketch[0].size(), false));
    queue<array<ll, 3>> q;

    loop(sketch, i, x) {
        loop(x, j, y) {
            if(y == 'S') {
                sx = j;
                sy = i;

                goto S;
            }
        }
    }

    S:;

    conns[0] = (sx > 0 && W.find(sketch[sy][sx - 1]) != string::npos);
    conns[1] = (sy > 0 && N.find(sketch[sy - 1][sx]) != string::npos);
    conns[2] = (sx < sketch[0].size() - 1 && E.find(sketch[sy][sx + 1]) != string::npos);
    conns[3] = (sy < sketch.size() - 1 && S.find(sketch[sy + 1][sx]) != string::npos);

    if(conns[1] && conns[2])
        sketch[sy][sx] = 'L';
    else if(conns[2] && conns[3])
        sketch[sy][sx] = 'F';
    else if(conns[3] && conns[0])
        sketch[sy][sx] = '7';
    else if(conns[0] && conns[1])
        sketch[sy][sx] = 'J';
    else if(conns[0] && conns[2])
        sketch[sy][sx] = '-';
    else if(conns[1] && conns[3])
        sketch[sy][sx] = '|';
    else
        exit(1);

    q.push({ sx, sy, 0 });

    while(!q.empty()) {
        array<ll, 3> cs = q.front();
        q.pop();

        if(cs[0] < 0 || cs[0] >= sketch[0].size() || cs[1] < 0 || cs[1] >= sketch.size() || vis[cs[1]][cs[0]])
            continue;

        vis[cs[1]][cs[0]] = true;

        switch(sketch[cs[1]][cs[0]]) {
            case 'L':
                q.push({ cs[0] + 1, cs[1], cs[2] + 1 });
                q.push({ cs[0], cs[1] - 1, cs[2] + 1 });
                break;
            case 'F':
                q.push({ cs[0] + 1, cs[1], cs[2] + 1 });
                q.push({ cs[0], cs[1] + 1, cs[2] + 1 });
                break;
            case '7':
                q.push({ cs[0] - 1, cs[1], cs[2] + 1 });
                q.push({ cs[0], cs[1] + 1, cs[2] + 1 });
                break;
            case 'J':
                q.push({ cs[0] - 1, cs[1], cs[2] + 1 });
                q.push({ cs[0], cs[1] - 1, cs[2] + 1 });
                break;
            case '-':
                q.push({ cs[0] + 1, cs[1], cs[2] + 1 });
                q.push({ cs[0] - 1, cs[1], cs[2] + 1 });
                break;
            case '|':
                q.push({ cs[0], cs[1] + 1, cs[2] + 1 });
                q.push({ cs[0], cs[1] - 1, cs[2] + 1 });
        }
    }

    vector<vector<char>> hires(sketch.size() * 2 + 1, vector<char>(sketch[0].size() * 2 + 1, ' '));

    loop(sketch, i, x) {
        loop(x, j, y)
            hires[i * 2 + 1][j * 2 + 1] = vis[i][j] ? y : '.';
    }

    for(ll i = 1; i < hires.size() - 1; i++) {
        for(ll j = 1; j < hires[0].size() - 1; j++) {
            if(!(i % 2)) {
                for(const auto &x : N) {
                    for(const auto &y : S) {
                        if(hires[i - 1][j] == x && hires[i + 1][j] == y)
                            hires[i][j] = '|';
                    }
                }
            }

            if(!(j % 2)) {
                for(const auto &x : W) {
                    for(const auto &y : E) {
                        if(hires[i][j - 1] == x && hires[i][j + 1] == y)
                            hires[i][j] = '-';
                    }
                }
            }
        }
    }

    flood_fill(0, 0, '#', { '.', ' ' }, true, hires, D4);
    ans = accumulate(all(hires), 0, [](auto a, auto b) { return a + count_if(all(b), [](auto c) { return c == '.'; }); });
}

