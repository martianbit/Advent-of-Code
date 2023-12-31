#include <aoc.hpp>
vector<string> initseq;
void parse(string s, stringstream &ss, ll li) {
    initseq = split(s, ",");
}
ll my_hash(string s) {
    ll h;
    h = 0;
    for(const auto &x : s)
        h = ((h + x) * 17) % 256;
    return h;
}
void master() {
    for(const auto &x : initseq)
        ans += my_hash(x);
}

