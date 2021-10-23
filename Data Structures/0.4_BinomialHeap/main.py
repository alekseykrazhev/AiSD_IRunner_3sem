if __name__ == '__main__':
    fin = open('input.txt', 'r')
    fout = open('output.txt', 'w')

    n = int(fin.readline())
    binary = bin(n)
    #print(binary[5] == '1')
    fin.close()

    ans = []
    l = len(binary)
    count = 0
    for i in range(l - 1, 0, -1):
        if binary[i] == '1':
            ans.append(count)
        count += 1
    #print(ans)
    if len(ans) == 0:
        fout.write('-1')
        fout.close()
        quit()

    for i in ans:
        fout.write(str(i))
        fout.write('\n')

    fout.close()