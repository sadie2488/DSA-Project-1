#include "AVLTree.h"

// STUBS: these compile so the tests can run (and fail) for the check-in.
// Replace each body with your real implementation.

AVLTree::~AVLTree() {
    // TODO: free every node (e.g. a recursive post-order delete helper)
}

bool AVLTree::insert(const std::string& name, int id) {
    (void)name; (void)id;
    return false;  // TODO
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
    (void)id; (void)nameOut;
    return false;  // TODO
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
