#pragma once

#include <string>
#include <vector>

// AVL tree of students, sorted by numeric GatorID (least to greatest).
// Data validation (name characters, 8-digit IDs) happens in the command
// parser, so these methods assume their inputs are already valid.
class AVLTree {
public:
    AVLTree() = default;
    ~AVLTree();
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    // Returns false if the ID is already in the tree.
    bool insert(const std::string& name, int id);

    // Returns false if the ID is not in the tree.
    // Two-children case replaces the node with its inorder successor.
    bool remove(int id);

    // Removes the Nth node of the inorder traversal (N = 0 is the first).
    // Returns false if N is out of range.
    bool removeInorder(int n);

    // Returns true and fills nameOut if the ID is found.
    bool searchID(int id, std::string& nameOut) const;

    // All IDs with this name, in preorder order. Empty if none.
    std::vector<int> searchName(const std::string& name) const;

    std::vector<std::string> inorderNames() const;
    std::vector<std::string> preorderNames() const;
    std::vector<std::string> postorderNames() const;

    // ID traversals, used by the unit tests to check tree shape.
    std::vector<int> inorderIDs() const;
    std::vector<int> preorderIDs() const;

    // Number of levels; 0 for an empty tree.
    int levelCount() const;

private:
    struct Node {
        std::string name;
        int id;
        int height = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(const std::string& n, int i) : name(n), id(i) {}
    };

    Node* root = nullptr;

    // TODO: add private recursive helpers here (rotations, height updates,
    Node* insertHelper(Node* node, const std::string& name, int id, bool& added);
    Node* searchIDHelper(Node* node, int id) const;

    void inorderHelper(Node* node, std::vector<Node*>& nodes) const;
    void preorderHelper(Node* node, std::vector<Node*>& nodes) const;
    void postorderHelper(Node* node, std::vector<Node*>& nodes) const;
    void searchNameHelper(Node* node, const std::string& name, std::vector<int>& ids) const;
    void destroy(Node* node);

    // traversal helpers, cleanup, etc.)
};
