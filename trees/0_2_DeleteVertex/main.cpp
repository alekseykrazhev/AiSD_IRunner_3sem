#include <iostream>
#include <fstream>

class Vertex {
public:
    int key;
    Vertex* left;
    Vertex* right;

    explicit Vertex( int Key) : key(Key), left(nullptr), right(nullptr) {};
};

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

    void FindMax (Vertex* vert, int& max) {
        if (max >= vert->key) {
            max = vert->key;
            max_max = vert;
            if (vert->left != nullptr) {
                FindMax(vert->left, max);
            }
        }
    }

    Vertex* FindMin (Vertex* v) {
        if (v->left != nullptr) {
            return FindMin(v->left);
        } else {
            return v;
        }
    }
public:
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
};

int main() {
    std::ifstream in (R"(input.txt)");
    std::ofstream out (R"(output.txt)");

    int a, del;
    Tree tree;

    if (!in.is_open()) {
        std::cerr << "Error opening file!";
        return -1;
    }

    in >> del;
    in.ignore();

    while (in >> a){
        tree.Insert(a);
    }
    in.close();

    tree.root = tree.DeleteVertex(tree.root, del);
    tree.ShowOrder(tree.root, out);
    return 0;
}