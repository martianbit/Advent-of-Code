#include <aoc.hpp>

string I;
unordered_map<string, array<string, 2>> net;

void parse(string s, stringstream &ss, ll li) {
    switch(li) {
        case 0:
            I = s;
            break;
        case 1:
            break;
        default:
            auto p1 = split(s);
            net[p1[0]] = { p1[2].substr(1, 3), p1[3].substr(0, 3) };
    }
}

void master() {
    vector<ll> dists;
    string node;

    for(const auto &x : net) {
        if(x.first[2] != 'A')
            continue;

        node = x.first;
        dists.emplace_back();

        while(node[2] != 'Z')
            node = net[node][I[dists.back()++ % I.size()] == 'R'];
    }

    ans = reduce(dists.begin() + 1, dists.end(), dists[0], [](auto a, auto b) { return lcm(a, b); });
}

