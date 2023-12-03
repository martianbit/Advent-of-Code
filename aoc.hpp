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
typedef vector<vector<ll*>> Graph; // 0: node; 1: weight

const ll INF = ~(1LL << 63);
const ll D4[][2] {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
const ll D5[][2] {{-1, 0}, {0, -1}, {0, 0}, {0, 1}, {1, 0}};
const ll D8[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const ll D9[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

ll ans;
string sans;

void parse(string s, ll li);
void master();

vector<string> split(string in_str, string at = " ")
{
    vector<string> result;

    auto itable = in_str | views::split(at) | views::transform([](auto a) {
        return string(&*a.begin(), ranges::distance(a));
    });

    for(const auto &x : itable)
        result.push_back(x);

    return result;
}

string replace_all(string in_str, string what, string with)
{
    ll fi;

    fi = -1;

    while(true)
    {
        fi = in_str.find(what, fi + 1);

        if(fi == string::npos)
            break;

        in_str = in_str.substr(0, fi) + with + in_str.substr(fi + what.size());
    }

    return in_str;
}

ll dijkstra(vector<ll> sis, vector<ll> eis, Graph g)
{
    bool *vis;
    ll i, cn, nd, sd, *dist;

    dist = (ll*) malloc(g.size() * sizeof(ll));
    vis = (bool*) malloc(g.size());

    auto cmp = [dist](ll a, ll b) { return dist[a] > dist[b]; };
    priority_queue<ll, vector<ll>, decltype(cmp)> q(cmp);

    for(i = 0; i < g.size(); i++)
    {
        dist[i] = INF;
        vis[i] = false;
    }

    for(i = 0; i < sis.size(); i++)
    {
        dist[sis[i]] = 0;
        vis[sis[i]] = true;

        q.push(sis[i]);
    }

    while(!q.empty())
    {
        cn = q.top();
        q.pop();

        for(i = 0; i < g[cn].size(); i++)
        {
            nd = dist[cn] + g[cn][i][1];

            if(nd < dist[g[cn][i][0]])
            {
                dist[g[cn][i][0]] = nd;

                if(!vis[g[cn][i][0]])
                {
                    q.push(g[cn][i][0]);
                    vis[g[cn][i][0]] = true;
                }
            }
        }
    }

    sd = INF;

    for(i = 0; i < eis.size(); i++)
        sd = min(dist[eis[i]], sd);

    return sd;
}

int main()
{
    ll li;
    string s;

    li = 0;

    while(getline(cin, s))
        parse(s, li++);

    master();

    if(sans.empty())
        sans = to_string(ans);

    cout << sans << endl;

    return 0;
}

