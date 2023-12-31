#include <aoc.hpp>
vector<string> layout;
void parse(string s, stringstream &ss, ll li) {
    layout.push_back(s);
}
void master() {
    char c;
    ll pb, nx, ny;
    set<array<ll, 4>> beams;
    set<array<ll, 2>> energized;
    pb = 0;
    beams.insert({ 0, 0, 1, 0 });
    while(pb < beams.size()) {
        pb = beams.size();
        vector<array<ll, 4>> nb;
        for(const auto &x : beams) {
            c = layout[x[1]][x[0]];
            switch(c) {
                case '.':
                    nb.push_back(x);
                    break;
                case '/':
                case '\\':
                    if(x[2] == 1 && !x[3])
                        nb.push_back({ x[0], x[1], 0, (c == '/' ? -1 : 1) });
                    else if(x[2] == -1 && !x[3])
                        nb.push_back({ x[0], x[1], 0, (c == '/' ? 1 : -1) });
                    else if(!x[2] && x[3] == 1)
                        nb.push_back({ x[0], x[1], (c == '/' ? -1 : 1), 0 });
                    else if(!x[2] && x[3] == -1)
                        nb.push_back({ x[0], x[1], (c == '/' ? 1 : -1), 0 });
                    break;
                case '-':
                    if(x[2])
                        nb.push_back(x);
                    else {
                        nb.push_back({ x[0], x[1], 1, 0 });
                        nb.push_back({ x[0], x[1], -1, 0 });
                    }
                    break;
                case '|':
                    if(x[3])
                        nb.push_back(x);
                    else {
                        nb.push_back({ x[0], x[1], 0, 1 });
                        nb.push_back({ x[0], x[1], 0, -1 });
                    }
            }
        }
        for(const auto &x : nb) {
            nx = x[0] + x[2];
            ny = x[1] + x[3];
            if(0 <= nx && nx < layout[0].size() && 0 <= ny && ny < layout.size())
                beams.insert({ nx, ny, x[2], x[3] });
        }
    }
    for(const auto &x : beams)
        energized.insert({ x[0], x[1] });
    ans = energized.size();
}

