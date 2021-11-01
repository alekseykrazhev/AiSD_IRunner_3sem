from queue import Queue
import numpy as np


order = []
component = []


def DFS1 (graph, v):
    used[v] = True
    for i in range (1, len(graph[v])):
        if not used[graph[v][i]] and graph[v][i] != 0:
            DFS1(graph, graph[v][i])
    order.append(v)


def DFS2 (v):
    used[v] = True
    component.append(v)
    for i in range (0, len(transp[v])):
        if not used[transp[v][i]]:
            DFS2(transp[v][i])


if __name__ == '__main__':
    fin = open('input.txt', 'r')
    fout = open('output.txt', 'w')

    n = int(fin.readline())
    N = 101
    list = []
    transp = [[] for i in range (n+1)]
    list.append([0])

    for i in range(n):
        l = [int(x) for x in fin.readline().split()]
        list.append(l)
    
    #print (list)
    fin.close()
    #print (transp)
    count = np.zeros(len(list), dtype = int)

    for i in range (len(list)):
        for j in range (len(list[i])):
            count[list[i][j]] += 1
            transp[list[i][j]].append(i)
        
    #print(count)

    #print (transp)

    ans1 = 1
    for i in range(1, len(count)):
        if count[i] == 0:
            ans1 += 1

    used = np.zeros(N, dtype = bool)
    for i in range (1, n):
        if not used[i]:
            DFS1(list, i)

    #print(order)
    ans2 = 0
    #used = np.zeros(N, N, dtype = bool)
    used = np.zeros(N, dtype = bool)
    for i in range (1, n):
        v = order[n-1-i]
        if not used[v]:
            DFS2(v)
            if  len(component) == 1:
                ans2 += 1
            component.clear()

    fout.write(str(ans1))
    fout.write('\n')
    fout.write(str(ans2))
    fout.close()
