import numpy as np
import sys

def FillMatrix (sizes):
    size = len(sizes)
    matrix = np.zeros((size, size), dtype = np.longlong)

    for p in range(2, size):
        for i in range(1, size - p + 1):
            j = i+p-1
            matrix[i][j] = sys.maxsize
            for k in range(i, j):
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k+1][j] + sizes[i-1]*sizes[j])

    print (matrix)
    return str(matrix[1][size-1])

if __name__ == '__main__':
    s = int(input())
    sizes = []
    
    for i in range(0, s):
        n, k = (int(i) for i in input().split())
        sizes.append(n)
        if (i >= s-1):
            sizes.append(k) 
            
    print(FillMatrix(sizes))