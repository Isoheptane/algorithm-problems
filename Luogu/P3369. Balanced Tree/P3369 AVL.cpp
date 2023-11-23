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

//  Both closed range
struct Range {
    int left;
    int right;
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
        return left_height - right_height;
    }
    //  Left rotate and return new root
    Node* rotate_left() {
        Node* subtree = this->right;
        Node* parent = this->parent;
        //  Transfer subtree
        this->right = subtree->left;
        if (subtree->left != nullptr)
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
        if (parent != nullptr)
            parent->update_tree();
        return subtree;
    }
    //  Right rotate and return new root
    Node* rotate_right() {
        Node* subtree = this->left;
        Node* parent = this->parent;
        //  Transfer subtree
        this->left = subtree->right;
        if (subtree->right != nullptr)
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
        if (parent != nullptr)
            parent->update_tree();
        return subtree;
    }
    //  Rebalance current tree
    Node* balance() {
        int factor = this->balance_factor();
        if (factor <= -2) {
            //  Right tree is higher than left tree
            //  Determine subtree shape
            if (this->right != nullptr && this->right->balance_factor() >= 1) {
                this->right->rotate_right();
            }
            return this->rotate_left();
        } else if (factor >= 2) {
            //  Left tree is higher than right tree
            //  Determine subtree shape
            if (this->left != nullptr && this->left->balance_factor() <= -1) {
                this->left->rotate_left();
            }
            return this->rotate_right();
        }
        return this;
    }
    //  Insert number and return balanced root
    Node* insert_number(int value) {
        if (this->value == value) {
            this->count++;
            this->update_tree();
            return this;
        }
        Node* result = nullptr;
        if (value < this->value) {
            if (this->left == nullptr)
                this->left = new Node(value, this);
            this->left->insert_number(value);
        } else if (value > this->value) {
            if (this->right == nullptr)
                this->right = new Node(value, this);
            this->right->insert_number(value);
        }
        Node* new_root = this->balance();
        new_root->update_tree();
        return new_root;
    }
    //  Delete this node without balance, return new root
    Node* delete_node() {
        Node* result = nullptr;
        while (this->left != nullptr || this->right != nullptr) {
            int left_height     = (this->left != nullptr)   ? this->left->tree_height   : 0;
            int right_height    = (this->right != nullptr)  ? this->right->tree_height  : 0;
            if (left_height < right_height) {
                Node* root = this->rotate_left();
                if (result == nullptr)
                    result = root;
            } else {
                Node* root = this->rotate_right();
                if (result == nullptr)
                    result = root;
            }
        }
        if (this->parent != nullptr)
            if (this->parent->left == this)
                this->parent->left = nullptr;
            else if (this->parent->right == this)
                this->parent->right = nullptr;
        delete this;
        return result;
    }
    //  Delete this number and return balanced root
    Node* delete_number(int value) {
        if (this->value == value) {
            this->count--;
            if (this->count == 0)
                return this->delete_node();
            this->update_tree();
            return this;
        }
        if (value < this->value) {
            if (this->left != nullptr)
                this->left->delete_number(value);
        } else {
            if (this->right != nullptr)
                this->right->delete_number(value);
        }
        Node* new_root = this->balance();
        new_root->update_tree();
        return new_root;
    }
    //  Rank in the sub tree
    Range rank_in_tree() {
        int left_size = (this->left != nullptr) ? this->left->tree_size : 0;
        return { left_size + 1, left_size + this->count };
    }
};

struct Tree {
    Node* root = nullptr;
    void insert_number(int value) {
        if (root == nullptr)
            root = new Node(value, nullptr);
        root = root->insert_number(value);
    }
    void delete_number(int value) {
        if (root == nullptr)
            return;
        root = root->delete_number(value);
    }
};

//  Find rank of given Node
Range get_rank(Node* const root) {
    if (root == nullptr)
        return Range{0, 0};
    if (root->parent == nullptr)
        return root->rank_in_tree();
    Range parent_range = get_rank(root->parent);
    if (root->parent->left == root) {
        int start = parent_range.left - root->tree_size - 1;
        Range cur_range = root->rank_in_tree();
        return { start + cur_range.left, start + cur_range.right };
    } else if (root->parent->right == root) {
        int start = parent_range.right;
        Range cur_range = root->rank_in_tree();
        return { start + cur_range.left, start + cur_range.right };
    }
    return {0, 0};
}

//  Find number by rank in the given tree
int get_number_by_rank(Node* const root, int rank) {
    Range range = root->rank_in_tree();
    if (rank < range.left)
        return get_number_by_rank(root->left, rank);
    else if (rank > range.right)
        return get_number_by_rank(root->right, rank - range.right);
    else
        return root->value;
}

//  Find node of prev (biggest number lower than value)
Node* get_prev(Node* const root, int value) {
    if (root == nullptr)
        return nullptr;
    if (root->value >= value) {
        if (root->left == nullptr)
            return nullptr;
        return get_prev(root->left, value);
    }
    if (root->right != nullptr) {
        Node* right_prev = get_prev(root->right, value);
        if (right_prev != nullptr && right_prev->value < value)
            return right_prev;
    }
    return root;
}

//  Find node of next (lowest number bigger than value)
Node* get_next(Node* const root, int value) {
    if (root == nullptr)
        return nullptr;
    if (root->value <= value) {
        if (root->right == nullptr)
            return nullptr;
        return get_next(root->right, value);
    }
    if (root->left != nullptr) {
        Node* left_next = get_next(root->left, value);
        if (left_next != nullptr && left_next->value > value)
            return left_next;
    }
    return root;
}

Tree tree;

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == Operation::Insert) {
            tree.insert_number(x);
        } else if (opt == Operation::Delete) {
            tree.delete_number(x);
        } else if (opt == Operation::GetRank) {
            printf("%d\n", get_rank(get_prev(tree.root, x)).right + 1);
        } else if (opt == Operation::GetNumberByRank) {
            printf("%d\n", get_number_by_rank(tree.root, x));
        } else if (opt == Operation::Previous) {
            printf("%d\n", get_prev(tree.root, x)->value);
        } else if (opt == Operation::Next) {
            printf("%d\n", get_next(tree.root, x)->value);
        }
    }
    return 0;
}