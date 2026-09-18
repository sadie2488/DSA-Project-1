#pragma once

#include <string>
#include "AVLTree.h"

// Parses and validates one command line (e.g. insert "Josh Smith" 12345678),
// runs it on the tree, and returns exactly what should be printed.
// Multi-line output (search NAME with duplicates) is joined with '\n'.
// No trailing newline. Invalid or misspelled commands return "unsuccessful".
//
// main.cpp then just does:  std::cout << executeCommand(tree, line) << '\n';
std::string executeCommand(AVLTree& tree, const std::string& line);
