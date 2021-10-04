class Node(object):
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

class Tree(object):
    def __init__(self):
        self.root = None

    def search_iteratively(x):
        v = root
        while v is not None:
            if v.key == x:
                return v
            elif x < v.key:
                v = v.left
            else:  # x > v.key:
                v = v.right
        return None

    def insert(x, m):


fin = open('bst.in', 'r')
fout = open('bst.out', 'w')

fout.write("NO")    

fin.close()
fout.close()