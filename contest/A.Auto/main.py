

if __name__ == '__main__':
    inp = str(input())
    inp1 = inp.split()
    x = int(inp1[0])
    y = int(inp1[1])

    ans = max(x + y, x, y)
    print(ans)
