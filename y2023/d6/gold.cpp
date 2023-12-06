#include <aoc.hpp>

array<ll, 2> race;

void parse(string s, stringstream &ss, ll li) {
    string p1;
    copy_if(all(s), back_inserter(p1), ::isdigit);
    race[li] = stoll(p1);
}

void master() {
    double D;
    D = sqrt(pow(race[0], 2) - 4 * race[1]);
    ans = ceil((race[0] + D) / 2) - floor((race[0] - D) / 2) - 1;
}

