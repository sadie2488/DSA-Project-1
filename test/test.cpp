// Name: Sarah Spellman
// UDIF: 27793702

#include <catch2/catch_test_macros.hpp>
#include <iostream>

// uncomment and replace the following with your own headers
// #include "AVL.h"
#include <algorithm>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "AVLTree.h"
#include "Commands.h"

using namespace std;

// Inserts each ID through the command interface and requires "successful".
static void insertIDs(AVLTree& tree, const std::vector<int>& ids) {
    for (int id : ids) {
        std::string command = "insert \"Student\" " + std::to_string(id);
        REQUIRE(executeCommand(tree, command) == "successful");
    }
}

// test 1: at least five commands that print "unsuccessful"
TEST_CASE("Invalid commands print unsuccessful", "[unsuccessful]") {
    AVLTree tree;

    REQUIRE(executeCommand(tree, R"(insert "Alice" 12345678)") == "successful");

    const std::vector<std::string> badCommands = {
        R"(insert "A11y" 45679999)",   // digits in name
        R"(insert "Bob!" 45679999)",   // symbol in name
        R"(insert "Carl" 1234567)",    // ID too short (7 digits)
        R"(insert "Dana" 123456789)",  // ID too long (9 digits)
        R"(insert "Evan" 1234abcd)",   // ID not numeric
        R"(insert Frank 23456789)",    // name missing quotes
        R"(insert "Gina" 12345678)",   // duplicate ID
        R"(remove 87654321)",          // ID not in tree
        R"(search 87654321)",          // ID not in tree
        R"(search "Nobody")",          // name not in tree
        R"(removeInorder 5)",          // index out of range
        R"(insrt "Hank" 34567890)",    // misspelled command
        R"(printInorderr)"             // misspelled command
    };

    for (const std::string& command : badCommands) {
        INFO("Command: " << command);
        CHECK(executeCommand(tree, command) == "unsuccessful");
    }

    // none of the bad commands should have changed the tree
    const std::vector<int> expected = {12345678};
    CHECK(tree.inorderIDs() == expected);
}

// test 2: insert command and all four rotation cases
TEST_CASE("Insert and all four rotations", "[insert][rotations]") {
    AVLTree tree;

    SECTION("Insert matches sample output") {
        REQUIRE(executeCommand(tree, R"(insert "Brandon" 45679999)") == "successful");
        REQUIRE(executeCommand(tree, R"(insert "Brian" 35459999)") == "successful");
        REQUIRE(executeCommand(tree, R"(insert "Briana" 87879999)") == "successful");
        REQUIRE(executeCommand(tree, R"(insert "Bella" 95469999)") == "successful");
        CHECK(executeCommand(tree, "printInorder") == "Brian, Brandon, Briana, Bella");
        CHECK(executeCommand(tree, "printLevelCount") == "3");
    }

    SECTION("Left rotation (right-right case)") {
        insertIDs(tree, {10000000, 20000000, 30000000});
        const std::vector<int> expected = {20000000, 10000000, 30000000};
        CHECK(tree.preorderIDs() == expected);
        CHECK(tree.levelCount() == 2);
    }

    SECTION("Right rotation (left-left case)") {
        insertIDs(tree, {30000000, 20000000, 10000000});
        const std::vector<int> expected = {20000000, 10000000, 30000000};
        CHECK(tree.preorderIDs() == expected);
        CHECK(tree.levelCount() == 2);
    }

    SECTION("Left-right rotation (left-right case)") {
        insertIDs(tree, {30000000, 10000000, 20000000});
        const std::vector<int> expected = {20000000, 10000000, 30000000};
        CHECK(tree.preorderIDs() == expected);
        CHECK(tree.levelCount() == 2);
    }

    SECTION("Right-left rotation (right-left case)") {
        insertIDs(tree, {10000000, 30000000, 20000000});
        const std::vector<int> expected = {20000000, 10000000, 30000000};
        CHECK(tree.preorderIDs() == expected);
        CHECK(tree.levelCount() == 2);
    }

    SECTION("Rotation below the root (left-left at a subtree)") {
        insertIDs(tree, {50000000, 30000000, 70000000, 20000000, 10000000});
        const std::vector<int> expected = {50000000, 20000000, 10000000, 30000000, 70000000};
        CHECK(tree.preorderIDs() == expected);
        CHECK(tree.levelCount() == 3);
    }
}

// test 3: insert 100 nodes, remove 10 random ones, and check inorder
TEST_CASE("Insert 100 nodes, remove 10, check inorder", "[large]") {
    AVLTree tree;
    std::mt19937 rng(3530);  // fixed seed so any failure is reproducible
    std::uniform_int_distribution<int> idDist(10000000, 99999999);

    // insert 100 unique random 8-digit IDs, std::set tracks the expected order
    std::set<int> expected;
    while (expected.size() < 100) {
        int id = idDist(rng);
        if (expected.insert(id).second) {
            insertIDs(tree, {id});
        }
    }

    // verify  all 100 insertions in order
    std::vector<int> actual = tree.inorderIDs();
    REQUIRE(actual.size() == 100);
    int index = 0;
    for (int id : expected) {
        CHECK(actual[index] == id);
        index++;
    }

    // pick 10 distinct random IDs and remove them
    std::vector<int> toRemove(expected.begin(), expected.end());
    std::shuffle(toRemove.begin(), toRemove.end(), rng);
    toRemove.resize(10);
    for (int id : toRemove) {
        REQUIRE(executeCommand(tree, "remove " + std::to_string(id)) == "successful");
        expected.erase(id);
    }

    // verify the remaining 90 nodes in order
    actual = tree.inorderIDs();
    REQUIRE(actual.size() == 90);
    index = 0;
    for (int id : expected) {
        CHECK(actual[index] == id);
        index++;
    }
}
