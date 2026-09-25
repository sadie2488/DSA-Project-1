#include <iostream>
#include <string>
#include "AVLTree.h"
#include "Commands.h"

using namespace std;

int main() {
	AVLTree tree;

	// first line is how many commands follow
	string firstLine;
	getline(cin, firstLine);
	int numCommands = stoi(firstLine);

	for (int i = 0; i < numCommands; i++) {
		string line;
		getline(cin, line);

		// windows line endings leave a \r at the end
		if (!line.empty() && line.back() == '\r')
			line.pop_back();

		cout << executeCommand(tree, line) << '\n';
	}


	return 0;
}