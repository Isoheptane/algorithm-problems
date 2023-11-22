#include <cstdio>
#include <cmath>

enum Operation {
    Insert = 1,
    Delete = 2,
    GetRank = 3,
    GetNumberByRank = 4,
    Previous = 5,
    Next = 6
};

struct Node {
    int value;
    int count = 0;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    int tree_size = 1;
    int tree_height = 1;
    Node(int value, Node* parent): value(value), parent(parent) {}
    //  Recompute tree height and tree size by left&right tree
    void update_tree() {
        int left_size       = (this->left != nullptr)   ? this->left->tree_size     : 0;
        int right_size      = (this->right != nullptr)  ? this->right->tree_size    : 0;
        this->tree_size     = left_size + right_size + this->count;

        int left_height     = (this->left != nullptr)   ? this->left->tree_height   : 0;
        int right_height    = (this->right != nullptr)  ? this->right->tree_height  : 0;
        this->tree_height   = std::max(left_height, right_height) + 1;
    }
    //  Balence factor
    int balance_factor() {
        int left_height     = (this->left != nullptr)   ? this->left->tree_height   : 0;
        int right_height    = (this->right != nullptr)  ? this->right->tree_height  : 0;
        return left - right;
    }
    //  Left rotate and return new root
    Node* rotate_left() {
        Node* subtree = this->right;
        Node* parent = this->parent;
        //  Transfer subtree
        this->right = subtree->left;
        subtree->left->parent = this;
        //  Promote subtree
        subtree->parent = parent;
        if (parent != nullptr) {
            if (parent->left == this)
                parent->left = subtree;
            else if (parent->right == this)
                parent->right = subtree;
        }
        //  Lower self
        subtree->left = this;
        this->parent = subtree;
        //  Update tree info;
        this->update_tree();
        subtree->update_tree();
        parent->update_tree();
        return subtree;
    }
    //  Right rotate and return new root
    Node* rotate_right() {
        Node* subtree = this->left;
        Node* parent = this->parent;
        //  Transfer subtree
        this->left = subtree->right;
        subtree->right->parent = this;
        //  Promote subtree
        subtree->parent = parent;
        if (parent != nullptr) {
            if (parent->left == this)
                parent->left = subtree;
            else if (parent->right == this)
                parent->right = subtree;
        }
        //  Lower self
        subtree->right = this;
        this->parent = subtree;
        //  Update tree info;
        this->update_tree();
        subtree->update_tree();
        parent->update_tree();
        return subtree;
    }
    //  Rebalance current tree
    Node* balance() {
        if (this->balance_factor() <= -2) {
            //  Right tree is higher than left tree
            //  Determine subtree shape
            if (this->right->balance_factor() <= -1) {
                this->right->rotate_right();
            }
            return this->rotate_left();
        } else if (this->balance_factor() >= 2) {
            //  Left tree is higher than right tree
            //  Determine subtree shape
            if (this->left->balance_factor() >= 1) {
                this->left->rotate_left();
            }
            return this->rotate_right();
        }
        return this;
    }
    //  Insert node and return balanced root
    Node* insert(Node* root, int value) {
        if (root->value == value) {
            root->count++;
            root->update_tree();
            return root;
        }
        Node* result = nullptr;
        if (value > root->value) {
            if (root->right == nullptr)
                root->right = new Node(value, root);
            insert(root->right, value);
        } else {
            if (root->left == nullptr)
                root->left = new Node(value, root);
            insert(root->left, value);
        }
        return this->balance();
    }
    //  Delete this node
    void delete_node() {
        while (this->left != nullptr || this->right != nullptr) {
            if (this->left->tree_height < this->right->tree_height) {
                this->rotate_right();
            } else {
                this->rotate_left();
            }
        }
        delete this;
    }
};

struct Tree {
    Node* root;
};

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {

    }
    return 0;
}