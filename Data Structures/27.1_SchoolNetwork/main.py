from queue import Queue
import numpy as np

def BFS(graph, vertex, n):
    q = Queue()
    visited = np.zeros(n+1)
    left = []
    q.put(vertex)
    visited[0] = 1
    visited[vertex] = 1
    while not q.empty():
        vert = q.get()
        #print(vert, end='-->')
        for u in graph[vert]:
            if visited[u] != 1:
                q.put(u)
                visited[u] = 1
    b = True
    for i in range(n+1):
        if visited[i] != 1:
            left.append(i)
            return left
    return []

def FillGraph(graph, n, i):
    count = 0
    if len(i) == 1:
        m = i[0]
    for u in range(1, n+1):
        left = BFS(graph, u, n)
        #print(left)
        if len(left) != 0:
            graph[u].append(m)
            count += 1

    return count

if __name__ == '__main__':
    fin = open('input.txt', 'r')
    fout = open('output.txt', 'w')

    n = int(fin.readline())
    list = []
    list.append([0])

    for i in range(n):
        l = [int(x) for x in fin.readline().split()]
        list.append(l)
    fin.close()

    #print(list)
    m = len(list[1])
    for j in range(1, n+1):
        if len(list[j]) > m:
            m = len(list[j])

    i = []
    for j in range(1, n+1):
        if len(list[j]) == m:
            i.append(j)

    min_len = float('Inf')
    min_indx = -1
    min_left = []
    for u in i:
        left = BFS(list, u, n)
        if len(left) == 0:
            fout.write('1')
            fout.write('\n')
            fout.write(str(FillGraph(list, n, i)))
            fout.close()
            quit()

        if len(left) < min_len:
            min_len = len(left)
            min_indx = u
            min_left = left

    indx = 0
    count = 0
    for i in list[indx]:
        for j in min_left:
            if j == i:
                min_len -= 1
                count += 1
            if min_len <= 0:
                break
        indx += 1
        
    fout.write(str(FillGraph(list, n, i)))
    fout.close()
