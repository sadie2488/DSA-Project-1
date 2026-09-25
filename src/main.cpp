#include <iostream>
#include "AVLTree.h"

using namespace std;

int main(){
	//testing
	AVLTree tree;
	cout << tree.insert("Brandon", 45679999) << endl; // 1
	cout << tree.insert("Brian", 35459999) << endl; // 1
	cout << tree.insert("Copy", 45679999) << endl; // 0 bc duplicate
	tree.insert("Briana", 87879999);
	tree.insert("Brian", 11111111);   // same name - different ID


	string name;
	if (tree.searchID(35459999, name))
		cout << "found " << name << endl; // found brain
	if (!tree.searchID(11111111, name))
		cout << "not found" << endl; // not found

	for (const string& n : tree.inorderNames())
		cout << n << " ";
	cout << endl;

	for (const string& n : tree.preorderNames())
		cout << n << " ";
	cout << endl;

	for (int id : tree.searchName("Brian"))
		cout << id << endl;

	return 0;
}
