#include "Commands.h"
#include <cctype>
#include <regex>
#include <vector>

using namespace std;

// only letters and spaces + not empty
static bool isValidName(const string& name) {
    if (name.empty())
        return false;
    for (char c : name) {
        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}

// exactly 8 digits
static bool isValidID(const string& id) {
    if (id.size() != 8)
        return false;
    for (char c : id) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

// ids are stored as ints so add  any leading zeros
static string formatID(int id) {
    string s = to_string(id);
    while (s.size() < 8)
        s = "0" + s;
    return s;
}

// "a, b, c"
static string joinNames(const vector<string>& names) {
    string output;
    for (int i = 0; i < (int)names.size(); i++) {
        if (i > 0)
            output += ", ";
        output += names[i];
    }
    return output;
}

static string result(bool worked) {
    return worked ? "successful" : "unsuccessful";
}


string executeCommand(AVLTree& tree, const string& line) {
    // shape of each command (the actual name/id get checked below)
    static const regex insertPattern("insert \"(.*)\" (\\S+)");
    static const regex removePattern("remove (\\S+)");
    static const regex searchNamePattern("search \"(.*)\"");
    static const regex searchIDPattern("search (\\S+)");
    static const regex removeInorderPattern("removeInorder (\\d+)");

    smatch match;

    if (regex_match(line, match, insertPattern)) {
        string name = match[1];
        string id = match[2];
        if (!isValidName(name) || !isValidID(id))
            return result(false);
        return result(tree.insert(name, stoi(id)));
    }
    if (regex_match(line, match, removePattern)) {
        string id = match[1];
        if (!isValidID(id))
            return result(false);
        return result(tree.remove(stoi(id)));
    }

    if (regex_match(line, match, searchNamePattern)) {
        string name = match[1];
        if (!isValidName(name))
            return result(false);

        vector<int> ids = tree.searchName(name);
        if (ids.empty())
            return result(false);

        // one id per line
        string output;
        for (int i = 0; i < (int)ids.size(); i++) {
            if (i > 0)
                output += "\n";
            output += formatID(ids[i]);
        }
        return output;
    }
    if (regex_match(line, match, searchIDPattern)) {
        string id = match[1];
        string name;
        if (!isValidID(id) || !tree.searchID(stoi(id), name))
            return result(false);
        return name;
    }

    if (regex_match(line, match, removeInorderPattern)) {
        string num = match[1];
        // anything this long can't be a real index (+ would break stoi)
        if (num.size() > 9)
            return result(false);
        return result(tree.removeInorder(stoi(num)));
    }
    if (line == "printInorder")
        return joinNames(tree.inorderNames());
    if (line == "printPreorder")
        return joinNames(tree.preorderNames());
    if (line == "printPostorder")
        return joinNames(tree.postorderNames());
    if (line == "printLevelCount")
        return to_string(tree.levelCount());

    return result(false);  // unknown or bad formatted command

}