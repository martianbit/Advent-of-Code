#include <aoc.hpp>

struct Ball
{
    ll count;
    string color;
};

struct Game
{
    ll id;
    vector<vector<struct Ball>> rounds;
};

vector<struct Game> games;

void parse(string s, ll li)
{
    struct Game g;
    struct Ball b;

    auto p1 = split(s, ": ");
    g.id = stoi(split(p1[0])[1]);

    auto p2 = split(p1[1], "; ");

    for(const auto &x : p2)
    {
        g.rounds.push_back({});
        auto p3 = split(x, ", ");

        for(const auto &y : p3)
        {
            auto p4 = split(y);

            b.count = stoi(p4[0]);
            b.color = p4[1];

            g.rounds.back().push_back(b);
        }
    }

    games.push_back(g);
}

void master()
{
    ans = accumulate(all(games), 0, [](auto a, auto b) {
        return a + (all_of(all(b.rounds), [](auto c) {
            return all_of(all(c), [](auto d) {
                if(d.color == "red")
                    return d.count <= 12;
                else if(d.color == "green")
                    return d.count <= 13;
                else
                    return d.count <= 14;
            });
        }) ? b.id : 0);
    });
}

