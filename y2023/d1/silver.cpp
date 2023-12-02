#include <aoc.hpp>

vector<string> lines;

void parse(string s, ll li)
{
    lines.push_back(s);
}

void master()
{
    ans = accumulate(all(lines), 0, [](auto a, auto b) { return a + 10 * (*find_if(all(b), ::isdigit) - '0') + *find_if(rall(b), ::isdigit) - '0'; });
}

