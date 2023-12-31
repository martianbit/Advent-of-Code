import sys
from collections import defaultdict
import networkx as nx # import solution
inp = sys.stdin.read().strip()
g = defaultdict(list)
G = nx.Graph()
for x in inp.split('\n'):
    p1 = x.replace(':', "").split()
    for i in range(1, len(p1)):
        g[p1[0]].append(p1[i])
        g[p1[i]].append(p1[0])
        G.add_edge(p1[0], p1[i])
cut = nx.minimum_edge_cut(G)
st = [list(g.keys())[0]]
vis = set()
while len(st):
    cv = st.pop()
    if cv in vis:
        continue
    vis.add(cv)
    for x in g[cv]:
        if (cv, x) not in cut and (x, cv) not in cut:
            st.append(x)
print(len(vis) * (len(g) - len(vis)))

