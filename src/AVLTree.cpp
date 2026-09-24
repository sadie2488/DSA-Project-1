#include "AVLTree.h"

// STUBS: these compile so the tests can run (and fail) for the check-in.
// Replace each body with your real implementation.

AVLTree::~AVLTree() {
    // TODO: free every node (e.g. a recursive post-order delete helper)
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
    return node;
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

bool AVLTree::remove(int id) {
    (void)id;
    return false;  // TODO
}

bool AVLTree::removeInorder(int n) {
    (void)n;
    return false;  // TODO
}

bool AVLTree::searchID(int id, std::string& nameOut) const {
    Node* found = searchIDHelper(root, id);
    if (found == nullptr)
        return false;
    nameOut = found->name;
    return true;
}

std::vector<int> AVLTree::searchName(const std::string& name) const {
    (void)name;
    return {};  // TODO
}

std::vector<std::string> AVLTree::inorderNames() const { return {}; }    // TODO
std::vector<std::string> AVLTree::preorderNames() const { return {}; }   // TODO
std::vector<std::string> AVLTree::postorderNames() const { return {}; }  // TODO
std::vector<int> AVLTree::inorderIDs() const { return {}; }              // TODO
std::vector<int> AVLTree::preorderIDs() const { return {}; }             // TODO

int AVLTree::levelCount() const {
    return 0;  // TODO
}
