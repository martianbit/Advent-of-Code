#include <aoc.hpp>

vector<string> lines;

void parse(string s, ll li)
{
    lines.push_back(s);
}

void master()
{
    unordered_map<string, string> remap;

    remap["one"] = "o1e";
    remap["two"] = "t2o";
    remap["three"] = "t3ree";
    remap["four"] = "f4ur";
    remap["five"] = "f5ve";
    remap["six"] = "s6x";
    remap["seven"] = "s7ven";
    remap["eight"] = "e8ght";
    remap["nine"] = "n9ne";

    loop(lines, i, x) {
        for(const auto &y : remap)
            x = replace_all(x, y.first, y.second);

        ans += 10 * (*find_if(all(x), ::isdigit) - '0') + *find_if(rall(x), ::isdigit) - '0';
    }
}

