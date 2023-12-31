import sys
import sympy # import solution
inp = sys.stdin.read().strip()
stones = []
for x in inp.split('\n'):
    stones.append(list(map(int, x.replace('@', ',').split(','))))
syms = list(sympy.symbols("a,b,c,d,e,f"))
pxx, pyx, pzx, vxx, vyx, vzx = syms
eqsys = []
for i in range(3):
    t = sympy.Symbol('t' + str(i))
    syms.append(t)
    eqsys.append(pxx + vxx * t - stones[i][0] - stones[i][3] * t)
    eqsys.append(pyx + vyx * t - stones[i][1] - stones[i][4] * t)
    eqsys.append(pzx + vzx * t - stones[i][2] - stones[i][5] * t)
ans = sympy.solve(eqsys, syms, dict=True)[0]
print(ans[pxx] + ans[pyx] + ans[pzx])

