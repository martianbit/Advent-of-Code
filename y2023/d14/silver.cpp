#include <aoc.hpp>
vector<string> positions;
void parse(string s, stringstream &ss, ll li) {
    positions.push_back(s);
}
void master() {
    ll i, j, k;
    for(i = 0; i < positions.size(); i++) {
        for(j = 0; j < positions[0].size(); j++) {
            if(positions[i][j] != 'O')
                continue;
            for(k = i; k > 0 && positions[k - 1][j] == '.'; k--);
            positions[i][j] = '.';
            positions[k][j] = 'O';
            ans += positions.size() - k;
        }
    }
}

