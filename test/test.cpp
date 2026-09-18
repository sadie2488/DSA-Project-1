// Name: Sarah Spellman
// UFID: 27793702

#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <string>
#include <vector>

#include "AVLTree.h"
#include "Commands.h"

using namespace std;

// inserts every ID in the list and checks that each insert is successful
void insertIDs(AVLTree& tree, vector<int> ids) {
    for (int i = 0; i < (int)ids.size(); i++) {
        string command = "insert \"Student\" " + to_string(ids[i]);
        REQUIRE(executeCommand(tree, command) == "successful");
    }
}

// test 1: commands that should print "unsuccessful"
TEST_CASE("Invalid commands print unsuccessful", "[unsuccessful]") {
    AVLTree tree;
    REQUIRE(executeCommand(tree, R"(insert "Alice" 12345678)") == "successful");

    vector<string> badCommands;
    badCommands.push_back(R"(insert "A11y" 45679999)");   // number in name
    badCommands.push_back(R"(insert "Bob!" 45679999)");   // symbol in name
    badCommands.push_back(R"(insert "Carl" 1234567)");    // ID too short
    badCommands.push_back(R"(insert "Dana" 123456789)");  // ID too long
    badCommands.push_back(R"(insert "Evan" 1234abcd)");   // letters in ID
    badCommands.push_back(R"(insert Frank 23456789)");    // no quotes around name
    badCommands.push_back(R"(insert "Gina" 12345678)");   // ID already used
    badCommands.push_back(R"(remove 87654321)");          // ID not in tree
    badCommands.push_back(R"(search 87654321)");          // ID not in tree
    badCommands.push_back(R"(search "Nobody")");          // name not in tree
    badCommands.push_back(R"(removeInorder 5)");          // index too big
    badCommands.push_back(R"(insrt "Hank" 34567890)");    // misspelled command
    badCommands.push_back(R"(printInorderr)");            // misspelled command

    for (int i = 0; i < (int)badCommands.size(); i++) {
        CHECK(executeCommand(tree, badCommands[i]) == "unsuccessful");
    }

    // the tree should only have Alice in it
    vector<int> expected = {12345678};
    CHECK(tree.inorderIDs() == expected);
}

// test 2: insert and the four rotation cases
TEST_CASE("Insert and all four rotations", "[insert][rotations]") {
    AVLTree tree;

    SECTION("Insert matches sample output") {
        REQUIRE(executeCommand(tree, R"(insert "Brandon" 45679999)") == "successful");
        REQUIRE(executeCommand(tree, R"(insert "Brian" 35459999)") == "successful");
        REQUIRE(executeCommand(tree, R"(insert "Briana" 87879999)") == "successful");
        REQUIRE(executeCommand(tree, R"(insert "Bella" 95469999)") == "successful");
        CHECK(executeCommand(tree, "printInorder") == "Brian, Brandon, Briana, Bella");
    }

    // after each rotation the middle value (20000000) should be the root,
    //  preorder going through should be 20000000, 10000000, 30000000

    SECTION("Left rotation (right-right case)") {
        insertIDs(tree, {10000000, 20000000, 30000000});
        vector<int> expected = {20000000, 10000000, 30000000};
        CHECK(tree.preorderIDs() == expected);
    }

    SECTION("Right rotation (left-left case)") {
        insertIDs(tree, {30000000, 20000000, 10000000});
        vector<int> expected = {20000000, 10000000, 30000000};
        CHECK(tree.preorderIDs() == expected);
    }

    SECTION("Left-right rotation (left-right case)") {
        insertIDs(tree, {30000000, 10000000, 20000000});
        vector<int> expected = {20000000, 10000000, 30000000};
        CHECK(tree.preorderIDs() == expected);
    }

    SECTION("Right-left rotation (right-left case)") {
        insertIDs(tree, {10000000, 30000000, 20000000});
        vector<int> expected = {20000000, 10000000, 30000000};
        CHECK(tree.preorderIDs() == expected);
    }
}

// test 3: insert 100 nodes, remove 10 random ones, check inorder
TEST_CASE("Insert 100 nodes, remove 10, check inorder", "[large]") {
    AVLTree tree;
    vector<int> expected;

    // insert 100 different 8-digit IDs
    for (int i = 0; i < 100; i++) {
        int id = 10000000 + i * 1000;
        string command = "insert \"Student\" " + to_string(id);
        REQUIRE(executeCommand(tree, command) == "successful");
        expected.push_back(id);
    }

    // check that all 100 IDs come out in order
    vector<int> actual = tree.inorderIDs();
    REQUIRE(actual.size() == 100);
    for (int i = 0; i < 100; i++) {
        CHECK(actual[i] == expected[i]);
    }

    // remove 10 random IDs
    srand(3530);
    for (int i = 0; i < 10; i++) {
        int index = rand() % expected.size();
        string command = "remove " + to_string(expected[index]);
        REQUIRE(executeCommand(tree, command) == "successful");
        expected.erase(expected.begin() + index);  // remove it from the expected list too
    }

    // check that the other 90 IDs are still there in order
    actual = tree.inorderIDs();
    REQUIRE(actual.size() == 90);
    for (int i = 0; i < 90; i++) {
        CHECK(actual[i] == expected[i]);
    }
}
