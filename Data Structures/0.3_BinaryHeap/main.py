import math


def isBinary(arr, depth):
    left = pow(2, depth)
    right = pow(2, depth + 1) - 1

    numb = True
    if not left <= len(arr) <= right:
        numb = False
    #print(str(len(arr)))
    for i in range(int(math.floor(len(arr) / 2))):
        if n % 2 == 1 and not i == n / 2 - 1:
            if arr[i] > arr[2*i + 1] or arr[i] > arr[2*i + 2]:
                numb = False
        else:
            if arr[i] > arr[2 * i + 1]:
                numb = False
    return numb


if __name__ == '__main__':
    fin = open('input.txt', 'r')
    fout = open('output.txt', 'w')

    n = int(fin.readline())
    list = [int(x) for x in fin.readline().split()]
    fin.close()

    depth = math.ceil(math.log2(n + 1)) - 1

    #print(depth)
    ans = isBinary(list, depth)
    if ans:
        fout.write('Yes')
    else:
        fout.write('No')
    fout.close()