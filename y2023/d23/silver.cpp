#include <aoc.hpp>
vector<string> trails;
void parse(string s, stringstream &ss, ll li) {
    trails.push_back(s);
}
void master() {
    ll i;
    stack<pair<array<ll, 3>, unordered_set<ll>>> st;
    st.push({{ 1, 0, 0 }, {}});
    while(!st.empty()) {
        auto cs = st.top();
        st.pop();
        Point cp = { .x = (int) cs.first[0], .y = (int) cs.first[1] };
        if(cp.y >= trails.size() - 1) {
            ans = max(ans, cs.first[2]);
            continue;
        }
        cs.second.insert(cp.key);
        for(i = 0; i < 4; i++) {
            if(trails[cp.y][cp.x] == '>' && !(D4[i][0] == 1 && !D4[i][1]))
                continue;
            if(trails[cp.y][cp.x] == 'v' && !(!D4[i][0] && D4[i][1] == 1))
                continue;
            if(trails[cp.y][cp.x] == '<' && !(D4[i][0] == -1 && !D4[i][1]))
                continue;
            if(trails[cp.y][cp.x] == '^' && !(!D4[i][0] && D4[i][1] == -1))
                continue;
            Point np = { .x = (int) (cp.x + D4[i][0]), .y = (int) (cp.y + D4[i][1]) };
            if(0 <= np.x && np.x < trails[0].size() && 0 <= np.y && np.y < trails.size() && trails[np.y][np.x] != '#' && cs.second.find(np.key) == cs.second.end())
                st.push({{ np.x, np.y, cs.first[2] + 1 }, cs.second});
        }
    }
}

