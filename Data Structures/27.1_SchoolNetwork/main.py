import numpy as np


order = []
component = []


def dfs1 (graph, v):
    used[v] = True
    for i in range (0, len(graph[v])):
        if not used[graph[v][i]]:
            dfs1(graph, graph[v][i])
    order.append(v)


def dfs2 (v):
    used[v] = True
    component.append(v)
    for i in range (0, len(transp[v])):
        if not used[transp[v][i]]:
            dfs2(transp[v][i])


if __name__ == '__main__':
    fin = open('input.txt', 'r')
    fout = open('output.txt', 'w')

    n = int(fin.readline())
    N = 101
    graph = []
    transp = [[] for i in range (n)]

    for i in range(n):
        l = [int(x)-1 for x in fin.readline().split()]
        l.remove(-1)
        graph.append(l)
    fin.close()

    count = np.zeros(len(graph), dtype = int)
    count1 = np.zeros(len(graph), dtype = int)

    for i in range (len(graph)):
        for j in range (len(graph[i])):
            count[graph[i][j]] += 1
            count1[i] += 1
            transp[graph[i][j]].append(i)
    print (count)
    print (count1)
    ans1 = 0
    for i in range(len(count)):
        if count[i] == 0:
            ans1 += 1
    if ans1 == 0:
        ans1 = 1

    used = np.zeros(N, dtype = bool)
    for i in range (n):
        if not used[i]:
            dfs1(graph, i)

    ans2 = 0
    used = np.zeros(N, dtype = bool)
    s = 0
    t = 0
    q = 0
    components = []
    for i in range (n):
        v = order[n-1-i]
        if not used[v]:
            dfs2(v)
            components.append(component.copy())
            component.clear()

    print(components)
    cond = [[] for i in range(len(components))]
    sheesh = [[] for i in range(len(components))]
    numb = 0
    for i in range(len(components)):
        for j in components[i]:
            for k in graph[j]:
                if not k in components[i] and not k in sheesh[i]:
                    cond[i].append(numb)
                    sheesh[i].append(k)
                    numb += 1

    count = np.zeros(len(cond), dtype = int)
    count1 = np.zeros(len(cond), dtype = int)
    for i in range (len(cond)):
        for j in range (len(cond[i])):
            count[cond[i][j]] += 1
            count1[i] += 1
    
    for i in range(len(components)):
        if count[i] == 0 and count1[i] > 0:
            s += 1
        if count[i] > 0 and count1[i] == 0:
            t += 1
        if count[i] == 0 and count1[i] == 0:
            q += 1

    fout.write(str(ans1))
    fout.write('\n')
    fout.write(str(max(s + q, t + q)))
    fout.close()
