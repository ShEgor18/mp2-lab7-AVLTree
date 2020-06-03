#include <iostream>
#include "AVLTree.h"

using namespace std;

int main() 
{
	AVLTree<int, int> tree;
	tree.Add(1, 10);
	tree.Add(2, 20);
	tree.Add(3, 30);
	tree.Add(4, 40);
	tree.Add(5, 50);
	tree.Add(6, 60);
	tree.Add(7, 70);
	tree.Add(8, 80);
	tree.Add(9, 90);
	tree.Add(10, 100);
	tree.Print();
	cout << "Search by key 4 -> data = " << tree.Find(4)->data << endl;
	cout << "Search by key 3 -> data = " << tree.Find(3)->data << endl;
	cout << "Search by key 2 -> data = " << tree.Find(2)->data << endl;
	cout << endl << endl;

	tree.Delete(4);
	tree.Print();
	cout << endl << endl;

	tree.Delete(5);
	tree.Print();
	cout << "Search by key 5 -> ptr " << tree.Find(5) << endl;
	cout << "Search by key 3 -> data = " << tree.Find(3)->data << endl;
	cout << "Search by key 2 -> data = " << tree.Find(2)->data << endl;
	system("pause");
	return 0;
}