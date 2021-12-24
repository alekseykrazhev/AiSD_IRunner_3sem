from typing import List


def counting_sort(alist, largest):
    c = [0]*(largest + 1)
    for i in range(len(alist)):
        c[alist[i]] = c[alist[i]] + 1
 
    c[0] = c[0] - 1
    for i in range(1, largest + 1):
        c[i] = c[i] + c[i - 1]
 
    result = [None]*len(alist)
 
    for x in reversed(alist):
        result[c[x]] = x
        c[x] = c[x] - 1
 
    return result


if __name__ == '__main__':
    size = str(input())
    sizes = size.split()
    n = int(sizes[0])
    p = int(sizes[1])

    mas_str = str(input())
    mas = mas_str.split()
    arr:List[int] = []
    ans:List[int] = []
    for i in range (n):
        arr.append(int(mas[i]))
    
    for i in range(p):
        s = str(input())
        st = s.split()
        if st[0] == '=':
            arr[int(st[1]) - 1] = int(st[2])
        
        if st[0] == '?':
            copy = counting_sort(arr[int(st[1])-1:int(st[2])], int(st[2]) - int(st[1]) + 1)
            an = copy[len(copy)-1]*copy[len(copy)-2]
            if copy[0] < 0 and copy[1] < 0:
                comp = copy[0] * copy[1]
                an = max(comp, copy[len(copy)-1]*copy[len(copy)-2])
            ans.append(an)

    for i in ans:
        print (i)
        