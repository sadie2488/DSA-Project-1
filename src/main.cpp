#include <iostream>
#include "AVLTree.h"

using namespace std;

int main(){
	//testing
	// builds the tree from the drawing above
	AVLTree t1;
	vector<int> start = {40000000, 20000000, 60000000, 10000000, 30000000, 50000000};
	for (int id : start)
		t1.insert("X", id);

	cout << t1.remove(10000000) << endl;   // 1
	for (int id : t1.preorderIDs())
		cout << id << " ";
	cout << endl;                          // 40000000 20000000 30000000 60000000 50000000

	cout << t1.remove(99999999) << endl;   // 0 not in tree
	cout << t1.removeInorder(0) << endl;   // 1 removes the smallest
	cout << t1.removeInorder(50) << endl;  // 0 out of range
	return 0;
}
