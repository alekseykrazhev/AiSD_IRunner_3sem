def FindMaxWay (vec, sums):
    for i in range (0, len(vec) - 2):
        if (sums[i] == -1):
            continue

        sums[i + 2] = max(int(vec[i + 2]) + int(sums[i]), int(sums[i + 2]))
        if (i < len(vec) - 3):
            sums[i + 3] = max(int(vec[i + 3]) + int(sums[i]), int(sums[i + 3]))

f = open('input.txt', 'r')
out = open('output.txt', 'w')

n = int(f.readline())
if (n == 0):
    out.write("-1")
    out.close()
    quit()

vec =list(map(int, f.readline().split()))
f.close()

if (n == 1):
    out.write(str(vec[0]))
    out.close()
    quit()

sums = list(vec)
sums[1] = -1
FindMaxWay(vec, sums)
print(vec)

out.write(str(sums[n - 1]))
out.close()
