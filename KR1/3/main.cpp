#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Vertex {
public:
    int key;
    Vertex* left;
    Vertex* right;

    explicit Vertex( int Key) : key(Key), left(nullptr), right(nullptr) {};
};

std::vector<Vertex*> all;

class Tree {
public:
    Vertex* found;
    Vertex* root;
    Vertex* max_max;

    Tree () : root(nullptr){};

    void Insert(int x) {
        Vertex** now = &root;

        while (*now) {
            Vertex& node = **now;

            if (x < node.key) {
                now = &node.left;
            } else if (x > node.key) {
                now = &node.right;
            } else {
                return;
            }
        }

        *now = new Vertex(x);
    }

    void ShowOrder (Vertex* vert, std::ofstream& out){
        if (vert->key != -1) {
            out << vert->key << "\n";
        }

        if (vert->left != nullptr){
            ShowOrder(vert->left, out);
        }

        if (vert->right != nullptr){
            ShowOrder(vert->right, out);
        }
    }

    void FindVertex (Vertex* vert, const int& x) {
        if (vert->key == x) {
            found = vert;
        }

        if (vert->left != nullptr) {
            FindVertex(vert->left, x);
        }

        if (vert->right != nullptr) {
            FindVertex(vert->right, x);
        }
    }

    Vertex* FindMin (Vertex* v) {
        if (v->left != nullptr) {
            return FindMin(v->left);
        } else {
            return v;
        }
    }

    Vertex* DeleteVertex (Vertex* v, int x) {
        if (v == nullptr) {
            return nullptr;
        }

        if (x < v->key) {
            v->left = DeleteVertex(v->left, x);
            return v;
        }
        if (x > v->key) {
            v->right = DeleteVertex(v->right, x);
            return v;
        }

        if (v->left == nullptr) {
            return v->right;
        } else if (v->right == nullptr) {
            return v->left;
        } else {
            int min_key = FindMin(v->right)->key;
            v->key = min_key;
            v->right = DeleteVertex(v->right, min_key);
            return v;
        }
    }

    Vertex* RightLeftSubtree(Vertex* v) {
        Vertex *start = v;
        int count1 = 0, count2 = 0;
        if (v->left != nullptr) {
            CountOrder(v->left, count1);
        }
        if (v->right != nullptr) {
            CountOrder(v->right, count2);
        }
        if (abs(count1 - count2) == 1) {
            return start;
        }
        return nullptr;
    }

    void CountOrder (Vertex* vert, int& count) {
        ++count;

        if (vert->left != nullptr){
            CountOrder(vert->left, count);
        }

        if (vert->right != nullptr){
            CountOrder(vert->right, count);
        }
    }

    void GetAllVertex (Vertex* v) {
        all.push_back(v);
        if (v->left != nullptr)
            return GetAllVertex(v->left);
        if (v->right != nullptr)
            return GetAllVertex(v->right);
    }
};

int main() {
    std::ifstream in ("in.txt");
    std::ofstream out ("out.txt");

    Tree tree;
    int a;
    std::vector<long long> vert;
    //std::vector<int> val;

    while (in >> a) {
        tree.Insert(a);
    }
    in.close();
    tree.GetAllVertex(tree.root);
    for (auto v : all) {
        Vertex* s = tree.RightLeftSubtree(v);
        if (s != nullptr) {
            vert.push_back(s->key);
        }
    }
    if (vert.size() > 1) {
        std::sort(vert.begin(), vert.end());
    }
    int res = vert.size()/2;
    if (res % 2 != 0) {
        tree.ShowOrder(tree.root, out);
        return 0;
    }
    tree.root= tree.DeleteVertex(tree.root, vert[res]);
    tree.ShowOrder(tree.root, out);
    return 0;
}
