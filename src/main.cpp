#include <iostream>
#include "AVLTree.h"

using namespace std;

int main(){
	//testing
	AVLTree t;
	cout << t.levelCount() << endl;   // 0

	t.insert("A", 50000000);
	t.insert("B", 30000000);
	t.insert("C", 70000000);
	cout << t.levelCount() << endl;   // 2

	t.insert("D", 20000000);
	t.insert("E", 10000000);
	cout << t.levelCount() << endl;   // 4

	return 0;
}
