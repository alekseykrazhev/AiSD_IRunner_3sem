import numpy as np

def FillMatrix (sizes):
    size = len(sizes)
    matrix = np.zeros((size, size), dtype = float)

    for p in range(2, size):
        for i in range(1, size - p + 1):
            j = i+p-1
            matrix[i][j] = float('Inf')
            for k in range(i, j):
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k+1][j] + sizes[i-1]*sizes[k]*sizes[j])

    #print(matrix)
    return int(matrix[1][size-1])
            

if __name__ == '__main__':
    fin = open('input.txt', 'r')
    fout = open('output.txt', 'w')

    s = int(fin.readline())
    sizes = []
    
    for i in range(0, s):
        n, k = (int(i) for i in fin.readline().split())
        sizes.append(n)
        if (i >= s-1):
            sizes.append(k) 

    fin.close()
    #print(sizes)
    fout.write(str(FillMatrix(sizes)))
    fout.close()
