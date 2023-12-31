#include <aoc.hpp>
vector<vector<string>> patterns = {{}};
void parse(string s, stringstream &ss, ll li) {
    if(s.empty())
        patterns.emplace_back();
    else
        patterns.back().push_back(s);
}
ll find_axis(const vector<string> &pattern) {
    bool ok;
    ll i, j;
    for(i = 1; i < pattern.size(); i++) {
        ok = true;
        for(j = min(i, ((ll) pattern.size()) - i); j > 0; j--) {
            if(pattern[i - j] != pattern[i + j - 1]) {
                ok = false;
                break;
            }
        }
        if(ok)
            return i;
    }
    return 0;
}
void master() {
    for(const auto &x : patterns) {
        vector<string> columns(x[0].size(), string(x.size(), '.'));
        loop(x, i, y) {
            loop(y, j, z)
                columns[j][i] = z;
        }
        ans += find_axis(columns) + find_axis(x) * 100;
    }
}

