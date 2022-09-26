#include <iostream>
struct TNode {
    std::string key;
    unsigned long long number;
    int priority;
    TNode* left = nullptr;
    TNode* right = nullptr;
    TNode(std::string k, unsigned long long val) : key(k), number(val), priority(rand() % 100) {}
};

class Treap {
public:
    bool InsertNode(const std::string& key, const unsigned long long& value);
    TNode* SearchNode(const std::string& key);
    bool DeleteNode(const std::string& key);
    void Clear();

private:
    bool InsertNode(TNode*& localRoot, const std::string& key, const unsigned long long& value);
    TNode* SearchNode(TNode*& localRoot, const std::string& key);
    bool DeleteNode(TNode*& localRoot, const std::string& key);
    void RotateLeft(TNode*& localRoot);
    void RotateRight(TNode*& localRoot);
    TNode* root = nullptr;
};

void Treap::RotateLeft(TNode*& localRoot) {
    TNode* r = localRoot->right;
    TNode* x = localRoot->right->left;
    r->left = localRoot;
    localRoot->right = x;
    localRoot = r;
}

void Treap::RotateRight(TNode*& localRoot) {
    TNode* l = localRoot->left;
    TNode* y = localRoot->left->right;
    l->right = localRoot;
    localRoot->left = y;
    localRoot = l;
}

bool Treap::InsertNode(const std::string& key, const unsigned long long& value) {
    if (root == nullptr) {
        root = new TNode(key, value);
        return true;
    }
    if (key == root->key) {
        return false;
    }
    if (key < root->key) {
        if (InsertNode(root->left, key, value) == false) {
            return false;
        }
        if (root->left != nullptr && root->left->priority > root->priority) {
            RotateRight(root);
        }
        return true;
    }
    if (InsertNode(root->right, key, value) == false) {
        return false;
    }
    if (root->right != nullptr && root->right->priority > root->priority) {
        RotateLeft(root);
    }
    return true;
}

// Insert 
bool Treap::InsertNode(TNode*& localRoot, const std::string& key, const unsigned long long& value) {
    if (localRoot == nullptr) {
        localRoot = new TNode(key, value);
        return true;
    }
    if (key == localRoot->key) {
        return false;
    }
    if (key < localRoot->key) {
        if (InsertNode(localRoot->left, key, value) == false) {
            return false;
        }
        if (localRoot->left != nullptr && localRoot->left->priority > localRoot->priority) {
            RotateRight(localRoot);
        }
        return true;
    }
    if (InsertNode(localRoot->right, key, value) == false) {
        return false;
    }
    if (localRoot->right != nullptr && localRoot->right->priority > localRoot->priority) {
        RotateLeft(localRoot);
    }
    return true;
}

TNode* Treap::SearchNode(const std::string& key) {
    if (root == nullptr) {
        return root;
    }
    if (root->key == key) {
        return root;
    }
    if (key < root->key) {
        return SearchNode(root->left, key);
    }
    return SearchNode(root->right, key);
}

// Search additional
TNode* Treap::SearchNode(TNode*& localRoot, const std::string& key) {
    if (localRoot == nullptr) {
        return localRoot;
    }
    if (localRoot->key == key) {
        return localRoot;
    }
    if (key < localRoot->key) {
        return SearchNode(localRoot->left, key);
    }
    return SearchNode(localRoot->right, key);
}

bool Treap::DeleteNode(const std::string& key) {
    if (root == nullptr) {
        return false;
    }
    if (key < root->key) {
        return DeleteNode(root->left, key);
    }
    if (key > root->key) {
        return DeleteNode(root->right, key);
    }
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
        return true;
    }
    if (root->left && root->right) {
        if (root->left->priority < root->right->priority) {
            RotateLeft(root);
            return DeleteNode(root->left, key);
        }
        else {
            RotateRight(root);
            return DeleteNode(root->right, key);
        }
    }
    TNode* child = (root->left) ? root->left : root->right;

    TNode* curr = root;
    root = child;
    delete curr;
    return true;
}

// Delete 
bool Treap::DeleteNode(TNode*& localRoot, const std::string& key) {
    if (localRoot == nullptr) {
        return false;
    }
    if (key < localRoot->key) {
        return DeleteNode(localRoot->left, key);
    }
    if (key > localRoot->key) {
        return DeleteNode(localRoot->right, key);
    }

    if (localRoot->left == nullptr && localRoot->right == nullptr) {
        delete localRoot;
        localRoot = nullptr;
        return true;
    }
    if (localRoot->left && localRoot->right) {
        if (localRoot->left->priority < localRoot->right->priority) {
            RotateLeft(localRoot);
            return DeleteNode(localRoot->left, key);
        }
        else {
            RotateRight(localRoot);
            return DeleteNode(localRoot->right, key);
        }
    }
    TNode* child = (localRoot->left) ? localRoot->left : localRoot->right;

    TNode* curr = localRoot;
    localRoot = child;
    delete curr;
    return true;
}


int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    srand(time(0));

    unsigned long long value;
    Treap tr;
    std::string input;
    while (std::cin >> input) {
        if (input == "+") {
            std::cin >> input >> value;
            for (char& item : input) {
                item = tolower(item);
            }
            if (tr.InsertNode(input, value)) {
                std::cout << "OK" << std::endl;
            }
            else {
                std::cout << "Exist" << std::endl;
            }

        }
        else if (input == "-") {
            std::cin >> input;
            for (char& item : input) {
                item = tolower(item);
            }
            if (tr.DeleteNode(input)) {
                std::cout << "OK" << std::endl;
            }
            else {
                std::cout << "NoSuchWord" << std::endl;
            }

        }
        else if (input == "!") {
            std::cin >> input;
            std::cin >> input;
            std::cout << "OK" << std::endl;

        }
        else {
            for (char& item : input) {
                item = tolower(item);
            }
            TNode* node = tr.SearchNode(input);
            if (node != nullptr) {
                std::cout << "OK: " << node->number << std::endl;
            }
            else {
                std::cout << "NoSuchWord" << std::endl;
            }
        }
    }
    
    return 0;
}
