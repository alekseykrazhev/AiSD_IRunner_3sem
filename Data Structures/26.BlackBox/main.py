import heapq
from typing import List


def add_to_black_box(now, minHeap, maxHeap):
    if -1 * maxHeap[0] > now:
        heapq.heappush(minHeap, -1 * int(maxHeap[0]))
        heapq.heappop(maxHeap)
        heapq.heappush(maxHeap, -1 * int(now))
    else:
        heapq.heappush(minHeap, int(now))


if __name__ == '__main__':
    fin = open('input.txt', 'r')
    fout = open('output.txt', 'w')

    fin.readline()
    add = [int(x) for x in fin.readline().split()]
    get = [int(x) for x in fin.readline().split()]
    fin.close()
    
    minHeap:List[int] = []
    maxHeap:List[int] = []
        
    get_count = int(0)
    for i in range(len(get)):
        if len(minHeap) == 0:
            heapq.heappush(maxHeap, -1 * int(add[get_count]))
            get_count += 1
        else:
            heapq.heappush(maxHeap, -1 * int(minHeap[0]))
            heapq.heappop(minHeap)

        while get_count != get[i]:
            add_to_black_box(int(add[get_count]), minHeap, maxHeap)
            #print(maxHeap, minHeap)
            get_count += 1

        fout.write(str(-1 * int(maxHeap[0])))
        if i != len(get) - 1:
            fout.write(' ')

    fout.close()
