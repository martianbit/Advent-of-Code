#include <aoc.hpp>
vector<string> trails;
void parse(string s, stringstream &ss, ll li) {
    trails.push_back(s);
}
void master() {
    ll i, j, k, nx, ny, nbs;
    map<array<ll, 2>, vector<array<ll, 3>>> graph;
    for(i = 0; i < trails.size(); i++) {
        for(j = 0; j < trails[0].size(); j++) {
            if(trails[i][j] == '#')
                continue;
            nbs = 0;
            for(k = 0; k < 4; k++) {
                nx = j + D4[k][0];
                ny = i + D4[k][1];
                nbs += (0 <= nx && nx < trails[0].size() && 0 <= ny && ny < trails.size() && trails[ny][nx] != '#');
            }
            if(nbs > 2)
                graph[{ j, i }] = {};
        }
    }
    graph[{ 1, 0 }] = {};
    graph[{ (ll) trails[0].size() - 2, (ll) trails.size() - 1 }] = {};
    for(auto &x : graph) {
        stack<array<ll, 5>> st;
        st.push({ x.first[0], x.first[1], -1, -1, 0 });
        while(!st.empty()) {
            auto cs = st.top();
            st.pop();
            if(!(cs[0] == x.first[0] && cs[1] == x.first[1]) && graph.find({ cs[0], cs[1] }) != graph.end()) {
                x.second.push_back({ cs[0], cs[1], cs[4] });
                continue;
            }
            for(i = 0; i < 4; i++) {
                nx = cs[0] + D4[i][0];
                ny = cs[1] + D4[i][1];
                if(0 <= nx && nx < trails[0].size() && 0 <= ny && ny < trails.size() && !(nx == cs[2] && ny == cs[3]) && trails[ny][nx] != '#')
                    st.push({ nx, ny, cs[0], cs[1], cs[4] + 1 });
            }
        }
    }
    stack<pair<array<ll, 3>, unordered_set<ll>>> st;
    st.push({{ 1, 0, 0 }, {}});
    while(!st.empty()) {
        auto cs = st.top();
        st.pop();
        Point cp = { .x = (int) cs.first[0], .y = (int) cs.first[1] };
        if(cp.y == trails.size() - 1) {
            ans = max(ans, cs.first[2]);
            continue;
        }
        cs.second.insert(cp.key);
        for(const auto &x : graph[{ cp.x, cp.y }]) {
            Point np = { .x = (int) x[0], .y = (int) x[1] };
            if(cs.second.find(np.key) == cs.second.end())
                st.push({{ np.x, np.y, cs.first[2] + x[2] }, cs.second});
        }
    }
}

