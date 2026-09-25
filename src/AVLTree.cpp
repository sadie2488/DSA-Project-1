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




int AVLTree::levelCount() const {
    return 0;  // TODO
}
