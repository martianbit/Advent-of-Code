#include <bits/stdc++.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#define mod(a, b) ((a % b + b) % b)
#define all(x) (x).begin(), (x).end()
#define rall(x) reverse_iterator((x).end()), reverse_iterator((x).begin())

#define loop(v, i, x) \
    for(ll i = 0; i < v.size(); i++) \
        for(bool run_once = true; run_once;) \
            for(auto &x = v[i]; run_once; run_once = false)

using namespace std;
using namespace fmt;

typedef long long ll;
typedef vector<vector<array<ll, 2>>> Graph; // 0: node; 1: weight

typedef union {
    ll key;
    struct {
        int x;
        int y;
    };
} Point;

const ll INF = (1LL << 62);

vector<array<ll, 2>> D4 = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
vector<array<ll, 2>> D5 = {{-1, 0}, {0, -1}, {0, 0}, {0, 1}, {1, 0}};
vector<array<ll, 2>> D8 = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
vector<array<ll, 2>> D9 = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

ll ans;
string sans;

void parse(string s, stringstream &ss, ll li);
void master();

vector<string> split(string in_str, string at = " ") {
    vector<string> result;

    auto itable = in_str | views::split(at) | views::transform([](auto a) {
        return string(&*a.begin(), ranges::distance(a));
    });

    copy_if(all(itable), back_inserter(result), [](auto a) { return a.size(); });
    return result;
}

string replace(string in_str, string what, string with) {
    ll fi;

    fi = -1;

    while(true) {
        fi = in_str.find(what, fi + 1);

        if(fi == string::npos)
            break;

        in_str = in_str.substr(0, fi) + with + in_str.substr(fi + what.size());
    }

    return in_str;
}

template<typename T>
void flood_fill(ll x, ll y, T with, vector<T> what, bool is_whitelist, vector<vector<T>> &grid, vector<array<ll, 2>> &D) {
    if(x < 0 || x >= grid[y].size() || y < 0 || y >= grid.size())
        return;

    auto found = find(all(what), grid[y][x]);

    if((is_whitelist && found == what.end()) || (!is_whitelist && found != what.end()))
        return;

    grid[y][x] = with;

    for(ll i = 0; i < D.size(); i++)
        flood_fill(x + D[i][0], y + D[i][1], with, what, is_whitelist, grid, D);
}

int main() {
    ll li;
    string s;

    cout << unitbuf;

    li = 0;

    while(getline(cin, s)) {
        stringstream ss(s);
        parse(s, ss, li++);
    }

    master();

    if(sans.empty())
        sans = to_string(ans);

    cout << sans << endl;

    return 0;
}

