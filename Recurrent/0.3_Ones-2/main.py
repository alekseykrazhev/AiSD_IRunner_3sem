def Func (base, exp, mod):
    n = 1
    while (exp):
        if (exp % 2):
            n *= base % mod
        base = (base ** 2) % mod
        exp //= 2
    return n

if __name__ == '__main__':
    n, k = (int(i) for i in input().split())

    mod = 1000000007

    num = 1
    den = 1
    for i in range(1, k + 1):
        den = (den * i) % mod

    for i in range(n, n - k, -1):
        num = (num * i) % mod

    ans = (num * Func(den, mod - 2, mod)) % mod
    print (ans)
