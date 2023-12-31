#include <aoc.hpp>
#define MINP 200000000000000
#define MAXP 400000000000000
vector<array<ll, 6>> stones;
void parse(string s, stringstream &ss, ll li) {
    ll i;
    auto p1 = split(replace(s, " @", ","), ", ");
    stones.emplace_back();
    for(i = 0; i < 6; i++)
        stones.back()[i] = stoll(p1[i]);
}
void master() {
    double t1, t2, mx, my;
    ll i, j, px1, py1, vx1, vy1, px2, py2, vx2, vy2;
    for(i = 0; i < stones.size(); i++) {
        px1 = stones[i][0];
        py1 = stones[i][1];
        vx1 = stones[i][3];
        vy1 = stones[i][4];
        for(j = i + 1; j < stones.size(); j++) {
            px2 = stones[j][0];
            py2 = stones[j][1];
            vx2 = stones[j][3];
            vy2 = stones[j][4];
            if(!(px1 == px2 && py1 == py2) && (vx1 * vy2 == vx2 * vy1))
                continue;
            t1 = (py1 - py2 - vy2 * (px1 - px2) / vx2) / (((double) vx1 * vy2) / vx2 - vy1);
            t2 = (py2 - py1 - vy1 * (px2 - px1) / vx1) / (((double) vx2 * vy1) / vx1 - vy2);
            mx = px1 + vx1 * t1;
            my = py1 + vy1 * t1;
            ans += (t1 >= 0 && t2 >= 0 && MINP <= mx && mx <= MAXP && MINP <= my && my <= MAXP);
        }
    }
}

