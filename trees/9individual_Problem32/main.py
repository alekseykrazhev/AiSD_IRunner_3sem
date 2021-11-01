import math
from typing import List


class Node(object):
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.sum_of_sons = 0
        self.height = 0
        self.amount_of_leaves = 0
        self.a = 0
        self.b = 0
        self.c = 0


class Tree(object):
    def __init__(self):
        self.root = None


def insert_recursively(v, x):
    if v is None:
        return Node(x)
    if x < v.key:
        v.left = insert_recursively(v.left, x)
    elif x > v.key:
        v.right = insert_recursively(v.right, x)
    # v.key == x
    return v


def ShowOrder (v, fout):
    fout.write(str(v.key))
    fout.write('\n')
    if v.left:
        ShowOrder(v.left, fout)
    if v.right:
        ShowOrder(v.right, fout)


def find_min(v):
    if v.left is not None:
        return find_min(v.left)
    else:
        return v


def delete_recursively(v, x):
    if v is None:
        return None
 
    if x < v.key:
        v.left = delete_recursively(v.left, x)
        return v
    elif x > v.key:
        v.right = delete_recursively(v.right, x)
        return v
 
    # v.key == x
    if v.left is None:
        return v.right
    elif v.right is None:
        return v.left
    else:
        # both subtrees are present
        min_key = find_min(v.right).key
        v.key = min_key
        v.right = delete_recursively(v.right, min_key)
        return v


def TreeHeight (v):
    if not v:
        return 0
    
    height = 0
    numb = TreeHeight(v.left)
    height = max(height, numb)
    numb = TreeHeight(v.right)
    height = max(height, numb)

    return height + 1


def sons_sum (v):
    if not v:
        return 0
    return TreeHeight(v.right) + TreeHeight(v.left)


def is_leaf(v):
    if not v.left and not v.right:
        return True
    return False


def back_traversal(v, max_length):
    if v is not None:
        back_traversal(v.left, int(max_length))
        back_traversal(v.right, int(max_length))

        v.sum_of_sons = sons_sum(v)

        max_length = max(max_length, v.sum_of_sons)
        left_amount = 0
        right_amount = 0
        left_height = -1
        right_height = -1
        if v.left:
            left_amount = int(v.left.amount_of_leaves)
            left_height = int(v.left.height)
        if v.right:
            right_amount = int(v.right.amount_of_leaves)
            right_height = int(v.right.height)

        v.height = int(max(left_height, right_height) + 1)

        if int(left_height) >= int(right_height):
            v.amount_of_leaves += int(left_amount)
        if int(right_height) >= int(left_height):
            v.amount_of_leaves += int(right_amount)
        if is_leaf(v):
            v.amount_of_leaves += 1

    return int(max_length)


def front_traversal(v, max_length, ans, root):
    if v:
        if v == root:
            v.a = 0
        if int(v.sum_of_sons) == int(max_length):
            first = int(1)
            sec = int(1)
            if v.left:
                first = int(v.left.amount_of_leaves)
            if v.right:
                sec = int(v.right.amount_of_leaves)
            v.b = int(first * sec)
        else:
            v.b = int(0)

        if v.left and not v.right:
            v.left.a = int(v.a) + int(v.b)
            v.left.c = int(v.left.a) + int(v.left.b)

        if v.right and not v.left:
            v.right.a = int(v.a) + int(v.b)
            v.right.c = int(v.right.a) + int(v.right.b)

        if v.left and v.right:
            if int(v.left.height) > int(v.right.height):
                v.left.a = int(v.a) + int(v.b)
                v.right.a = int(v.b)
            if int(v.right.height) > int(v.left.height):
                v.left.a = int(v.b)
                v.right.a = int(v.a) + int(v.b)
            if int(v.right.height) == int(v.left.height):
                v.left.a = int(v.b) + int(v.left.amount_of_leaves * v.a / v.amount_of_leaves)
                v.right.a = int(v.b) + int(v.right.amount_of_leaves * v.a / v.amount_of_leaves)
            v.left.c = int(v.left.a) + int(v.left.b)
            v.right.c = int(v.right.a) + int(v.right.b)
        v.c = int(v.a) + int(v.b)
        if int(v.c) % 2 == 0 and int(v.c) != 0:
            ans.append(v.key)

        front_traversal(v.left, int(max_length), ans, root)
        front_traversal(v.right, int(max_length), ans, root) 
    return ans


if __name__ == '__main__':
    fin = open('tst.in', 'r')
    fout = open('tst.out', 'w')

    tree = Tree()
    vertexes:List[int] = []
    #vertexes input
    while True:
        v = fin.readline() 
        if v == '':
            break
        vertexes.append(int(v))
    fin.close()
    
    for i in vertexes:
        tree.root = insert_recursively(tree.root, i)
    
    max_length = back_traversal(tree.root, int(0))
    tree.root.a = 0
    ans:List[int] = []
    ans = front_traversal(tree.root, max_length, [], tree.root)
    #print(ans)
    
    if len(ans) != 1:
        if len(ans) % 2 == 0:
            ShowOrder(tree.root, fout)
            fout.close()
            quit()
        ans.sort()
        tree.root = delete_recursively(tree.root, int(ans[math.floor(len(ans) / 2)]))
    else:
        tree.root = delete_recursively(tree.root, int(ans[0]))
    
    ShowOrder(tree.root, fout)
    fout.close()
