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
    Vertex* root;
public:
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
        out << vert->key << "\n";
        if (vert->left != nullptr){
            ShowOrder(vert->left, out);
        }
        if (vert->right != nullptr){
            ShowOrder(vert->right, out);
        }
    }

private:
    static void DestroyVertex( Vertex* vertex ) {
        if (vertex){
            DestroyVertex(vertex -> left);
            DestroyVertex(vertex -> right);
            delete vertex;
        }
    }
};

int main() {
    std::ifstream in (R"(input.txt)");
    std::ofstream out (R"(output.txt)");

    int a;
    Tree tree;

    if (!in.is_open()) {
        std::cerr << "Error opening file!";
        return -1;
    }

    while (in >> a){
        tree.Insert(a);
    }
    in.close();

    tree.ShowOrder(tree.root, out);
    out.close();

    return 0;
}