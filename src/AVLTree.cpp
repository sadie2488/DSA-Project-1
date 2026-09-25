#include "AVLTree.h"
#include <algorithm>

//the destructor helper
void AVLTree::destroy(Node* node) {
    if (node == nullptr)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

AVLTree::~AVLTree() {
    destroy(root);
}

// empty spot counts as 0
int AVLTree::getHeight(Node* node) const {
    if (node == nullptr)
        return 0;
    return node->height;
}

// positive = left heavy, negative = right heavy
int AVLTree::getBalance(Node* node) const {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::updateHeight(Node* node) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

AVLTree::Node* AVLTree::insertHelper(Node* node, const std::string& name, int id, bool& added) {
    if (node == nullptr) {
        added = true;
        return new Node(name, id);
    }
    if (id < node->id)
        node->left = insertHelper(node->left, name, id, added);
    else if (id > node->id)
        node->right = insertHelper(node->right, name, id, added);
    else
        return node; // duplicate id, dont add
    return rebalance(node);
}

AVLTree::Node* AVLTree::searchIDHelper(Node* node, int id) const {
    if (node == nullptr || node->id == id)
        return node;
    if (id < node->id)
        return searchIDHelper(node->left, id);
    return searchIDHelper(node->right, id);
}

bool AVLTree::insert(const std::string& name, int id) {
    bool added = false;
    root = insertHelper(root, name, id, added);
    return added;
}

// left, node, right
void AVLTree::inorderHelper(Node* node, std::vector<Node*>& nodes) const {
    if (node == nullptr)
        return;
    inorderHelper(node->left, nodes);
    nodes.push_back(node);
    inorderHelper(node->right, nodes);
}

// node, left, right
void AVLTree::preorderHelper(Node* node, std::vector<Node*>& nodes) const {
    if (node == nullptr)
        return;
    nodes.push_back(node);
    preorderHelper(node->left, nodes);
    preorderHelper(node->right, nodes);
}

//left, right, node
void AVLTree::postorderHelper(Node* node, std::vector<Node*>& nodes) const {
    if (node == nullptr)
        return;
    postorderHelper(node->left, nodes);
    postorderHelper(node->right, nodes);
    nodes.push_back(node);
}

AVLTree::Node* AVLTree::removeHelper(Node* node, int id, bool& removed) {
    if (node == nullptr)
        return nullptr; // not found

    if (id< node->id) {
        node->left = removeHelper(node->left, id, removed);
    }
    else if (id > node->id) {
        node->right = removeHelper(node->right, id, removed);
    }
    else {
        removed = true;

        //if no kids or one kid -- just hook the kid (or null) to the parent
        if (node->left == nullptr || node->right == nullptr) {
            Node* child = (node->left != nullptr) ? node->left : node->right;
            delete node;
            return child;
        }

        // two kids: grab the inorder successor (smallest in right subtree)
        Node* successor = node->right;
        while (successor->left != nullptr)
            successor = successor->left;

        // copy its data  then delete the successor from the right side
        node->name = successor->name;
        node->id = successor->id;
        node->right = removeHelper(node->right, successor->id, removed);
    }
    return rebalance(node);
}

bool AVLTree::remove(int id) {
    bool removed = false;
    root = removeHelper(root, id, removed);
    return removed;
}

bool AVLTree::removeInorder(int n) {
    std::vector<Node*> nodes;
    inorderHelper(root, nodes);

    if (n < 0 || n >= (int)nodes.size())
        return false;

    return remove(nodes[n]->id);
}

bool AVLTree::searchID(int id, std::string& nameOut) const {
    Node* found = searchIDHelper(root, id);
    if (found == nullptr)
        return false;
    nameOut = found->name;
    return true;
}

// searchName helper
void AVLTree::searchNameHelper(Node* node, const std::string& name, std::vector<int>& ids) const {
    if (node == nullptr)
        return;
    if (node->name == name)
        ids.push_back(node->id);
    searchNameHelper(node->left, name, ids);
    searchNameHelper(node->right, name, ids);
}

std::vector<int> AVLTree::searchName(const std::string& name) const {
    std::vector<int> ids;
    searchNameHelper(root, name, ids);
    return ids;
}

// five traversal ways
//in order names
std::vector<std::string> AVLTree::inorderNames() const {
    std::vector<Node*> nodes;
    inorderHelper(root, nodes);

    std::vector<std::string> names;
    for (Node* n : nodes)
        names.push_back(n->name);
    return names;
}

//preorder names
std::vector<std::string> AVLTree::preorderNames() const {
    std::vector<Node*> nodes;
    preorderHelper(root, nodes);

    std::vector<std::string> names;
    for (Node* n : nodes)
        names.push_back(n->name);
    return names;
}

//postorder names
std::vector<std::string> AVLTree::postorderNames() const {
    std::vector<Node*> nodes;
    postorderHelper(root, nodes);

    std::vector<std::string> names;
    for (Node* n : nodes)
        names.push_back(n->name);
    return names;
}

// inorder IDs
std::vector<int> AVLTree::inorderIDs() const {
    std::vector<Node*> nodes;
    inorderHelper(root, nodes);

    std::vector<int> ids;
    for (Node* n : nodes)
        ids.push_back(n->id);
    return ids;
}

// preorder IDs
std::vector<int> AVLTree::preorderIDs() const {
    std::vector<Node*> nodes;
    preorderHelper(root, nodes);

    std::vector<int> ids;
    for (Node* n : nodes)
        ids.push_back(n->id);
    return ids;
}


// right-right case: right child comes up
AVLTree::Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    Node* moved = newRoot->left;
    newRoot->left = node;
    node->right = moved;
    updateHeight(node);  // node is lower now so do it first
    updateHeight(newRoot);
    return newRoot;
}

// left-left case: left child comes up
AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    Node* moved = newRoot->right;
    newRoot->right = node;
    node->left = moved;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

//double roations

// left-right case: fix the left child first, then it's a left-left
AVLTree::Node* AVLTree::rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// right-left case: same idea mirrored
AVLTree::Node* AVLTree::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// call on the way back up after an insert/remove
AVLTree::Node* AVLTree::rebalance(Node* node) {
    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1) {
        // left heavy
        if (getBalance(node->left) >= 0)
            return rotateRight(node);
        else
            return rotateLeftRight(node);
    }
    if (balance < -1) {
        // right heavy
        if (getBalance(node->right) <= 0)
            return rotateLeft(node);
        else
            return rotateRightLeft(node);
    }
    return node;  // already balanced
}

// root's height is the number of levels
int AVLTree::levelCount() const {
    return getHeight(root);
}
