def FillRooms(list):
    

if __name__ == '__main__':
    fin = open('input.txt', 'r')
    fout = open('output.txt', 'w')

    a = int(fin.readline())
    b = int(fin.readline())
    p = int(fin.readline())

    list = []
    for i in range(p):
        l = [int(x) for x in fin.readline().split()]
        list.append(l)

    FillRooms(list)
    print(list)
