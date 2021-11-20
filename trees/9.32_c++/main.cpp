#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

class Node{
public:
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    int sum_of_sons = 0;
    int height = 0;
    int amount_of_leaves = 0;
    int a = 0, b = 0, c = 0;

    Node(int _key){
        key = _key;
    }
};

class Tree{
private:
    static void DestroyTree(Node* vert){
        if (vert != nullptr) {
            DestroyTree(vert->left);
            DestroyTree(vert->right);
            delete vert;
        }
    }
public:
    Node* root;
    Tree() : root(0){}
    ~Tree() {
        DestroyTree(root);
    }

    void Insert(int x) {
        Node** cur = &root;
        while (*cur) {
            Node& node = **cur;
            if (x < node.key) {
                cur = &node.left;
            } else if (x > node.key) {
                cur = &node.right;
            } else {
                return;
            }
        }
        *cur = new Node(x);
    }

    void ShowOrder(Node* v, std::ofstream& out){
        out << v->key << '\n';
        if (v->left) {
            ShowOrder(v->left, out);
        }
        if (v->right){
            ShowOrder(v->right, out);
        }
    }

    Node* FindMin(Node* v){
        if (v->left != nullptr) {
            return FindMin(v->left);
        } else {
            return v;
        }
    }

    Node* Delete(Node* v, int x){
        if (v == nullptr){
            return nullptr;
        }

        if (x < v->key){
            v->left = Delete(v->left, x);
            return v;
        } else if (x > v->key) {
            v->right = Delete(v->right, x);
            return v;
        }
        if (v->left == nullptr)
            return v->right;
        else if (v->right == nullptr)
            return v->left;
        else {
            int min_key = FindMin(v->right)->key;
            v->key = min_key;
            v->right = Delete(v->right, min_key);
            return v;
        }
    }

    int TreeHeight(Node* v) {
        if (v == nullptr) {
            return 0;
        }

        int height = 0;
        int numb = TreeHeight(v->left);
        height = std::max(height, numb);
        numb = TreeHeight(v->right);
        height = std::max(height, numb);

        return height + 1;
    }

    int SonsSum (Node* v){
        if (v == nullptr){
            return 0;
        }
        return TreeHeight(v->right) + TreeHeight(v->left);
    }

    bool IsLeaf(Node* v){
        if (v->left == nullptr && v->right == nullptr) {
            return true;
        }
        return false;
    }

    int BackTraversal (Node* v, int max_length) {
        if (v != nullptr) {
            BackTraversal(v->left, max_length);
            BackTraversal(v->right, max_length);

            v->sum_of_sons = SonsSum(v);

            max_length = std::max (max_length, v->sum_of_sons);
            int left_am = 0;
            int right_am = 0;
            int left_h = -1;
            int right_h = -1;
            if (v->left) {
                left_am = v->left->amount_of_leaves;
                left_h = v->left->height;
            }
            if (v->right) {
                right_am = v->right->amount_of_leaves;
                right_h = v->right->height;
            }

            v->height = std::max(left_h, right_h) + 1;

            if (left_h >= right_h)
                v->amount_of_leaves += left_am;
            if (right_h >= left_h)
                v->amount_of_leaves += right_am;
            if (IsLeaf(v))
                ++v->amount_of_leaves;
        }
        return max_length;
    }

    void FrontTraversal (Node* v, int max_length, std::vector<int>& ans, Node* root) {
        if (v) {
            if (v == root) {
                v->a = 0;
            }
            if (v->sum_of_sons == max_length) {
                int first = 1;
                int sec = 1;
                if (v->left)
                    first = v->left->amount_of_leaves;
                if (v->right)
                    sec = v->right->amount_of_leaves;
                v->b = first * sec;
            } else {
                v->b = 0;
            }

            if (v->left && !v->right) {
                v->left->a = v->a + v->b;
                v->left->c = v->left->a + v->left->b;
            }
            if (!v->left && v->right) {
                v->right->a = v->a + v->b;
                v->right->c = v->right->a + v->right->b;
            }

            if (v->left && v->right) {
                if (v->left->height > v->right->height) {
                    v->left->a = v->a + v->b;
                    v->right->a = v->b;
                }
                if (v->right->height > v->left->height) {
                    v->left->a = v->b;
                    v->right->a = v->a + v->b;
                }
                if (v->right->height == v->left->height) {
                    v->left->a = v->b + (v->left->amount_of_leaves * v->a / v->amount_of_leaves);
                    v->right->a = v->b + (v->right->amount_of_leaves * v->a / v->amount_of_leaves);
                }
                v->left->c = v->left->a + v->left->b;
                v->right->c = v->right->a + v->right->b;
            }
            v->c = v->a + v->b;
            if (v->c % 2 == 0 && v->c != 0) {
                ans.push_back(v->key);
            }
            FrontTraversal(v->left, max_length, ans, root);
            FrontTraversal(v->right, max_length, ans, root);
        }
    }
};

int main(){
    std::ifstream in ("tst.in");
    std::ofstream out ("tst.out");

    Tree tree;
    int t;
    while (in >> t) {
        tree.Insert(t);
    }
    in.close();
    int max_length = tree.BackTraversal(tree.root, 0);
    tree.root->a = 0;
    std::vector <int> ans;
    tree.FrontTraversal(tree.root, max_length, ans, tree.root);

    if (ans.size() != 1) {
        if (ans.size() % 2 == 0){
            tree.ShowOrder(tree.root, out);
            out.close();
            return 0;
        }
        std::sort(ans.begin(), ans.end());
        tree.root = tree.Delete(tree.root, ans[ans.size() / 2]);
    } else {
        tree.root = tree.Delete(tree.root, ans[0]);
    }

    tree.ShowOrder(tree.root, out);
    out.close();
    return 0;
}