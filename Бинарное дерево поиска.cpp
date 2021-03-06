#include "pch.h"
#include <ctime>
#include <iostream>
using namespace std;

struct elem {
	int data;
	elem *par;
	elem *left;
	elem *right;

	elem(int value = 0) {
		par = NULL;
		left = NULL;
		right = NULL;
		data = value;
	}
};

struct binary_tree {
	elem *top;

	binary_tree() {
		top = NULL;
	}
};

void add(binary_tree& tree, const int& data) {
	elem *p = tree.top;
	if (p == NULL) {
		tree.top = new elem(data);
		return;
	}
	while(p != NULL) {
		if (p->data < data) {
			if (p->right != NULL) {
				p = p->right;
			}
			else {
				elem *node = new elem(data);
				node->par = p;
				p->right = node;
				break;
			}
		}
		else if (p->data > data) {
			if (p->left != NULL) {
				p = p->left;
			}
			else {
				elem *node = new elem(data);
				node->par = p;
				p->left = node;
				break;
			}
		}
		else if (p->data == data) {
			if (p->left != NULL) {
				p = p->left;
			}
			else {
				elem *node = new elem(data);
				node->par = p;
				p->left = node;
				break;
			}
		}
	}
	return;
}

elem *minimum(elem *root) {
	if (root->left == NULL) {
		return root;
	}
	return minimum(root->left);
}

elem *del(elem *p, const int& data) {
	if (p == NULL) {
		return p;
	}
	if (data < p->data) {
		p->left = del(p->left, data);
	}
	else if (data > p->data) {
		p->right = del(p->right, data);
	}
	else if (p->left != NULL && p->right != NULL) {
		p->data = minimum(p->right)->data;
		p->right = del(p->right, p->data);
	}
	else {
		if (p->left != NULL) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	return p;
}

elem *find(binary_tree &tree, const int& data) {
	elem *pointer = tree.top;
	while (pointer) {
		if (data < pointer->data) {
			pointer = pointer->left;
		}
		else if (data > pointer->data) {
			pointer = pointer->right;
		}
		else if (pointer->data == data) {
			return pointer;
		}
	}
	return false;
}

void fill(binary_tree &tree, const int& n) {
	int temp = 0;
	cout << "Filling..." << endl;
	tree.top = new elem(rand() % 10 + 1);
	for (int i = 0; i < n-1; i++) {
		temp = rand() % 10 + 1;
		add(tree, temp);
		cout << "Added the new element: " << temp << endl;
	}
	cout << "Ended..." << endl;
}


void print(elem *top, int& counter) {
	if (!top) {
		return;
	}
	print(top->left, counter);
	cout << counter << ": " << top->data << endl;
	++counter;
	print(top->right, counter);
}
//Is the part of the Print function

void Print(binary_tree &tree) {
	int counter = 1;
	cout << "\n=====================================================\n" << endl;
	print(tree.top, counter);
	cout << "\n=====================================================\n" << endl;
}
//Prints the elements of the tree

double Size(elem *top, double& counter) {
	if (!top) {
		return counter;
	}
	Size(top->left, counter);
	++counter;
	Size(top->right, counter);
	return counter;
}
//Finds the amount of the elements of the tree

double Sum(elem *top, double& result) {
	if (!top) {
		return result;
	}
	Sum(top->left, result);
	result += top->data;
	Sum(top->right, result);
	return result;
}

double Average(const double& sum, const double& size) {
	double result = sum / size;
	return result;
}
//Finds the average of the elements of the tree

int FindClosest(elem *top, const int& average, int& closest, int& result, int& counter) {
	if (!top) {
		return result;
	}
	FindClosest(top->left, average, closest, result, counter);
	if (counter == 0) {
		closest = abs(top->data - average);
		result = top->data;
	}
	else if (abs(top->data - average) < closest) {
		closest = abs(top->data - average);
		result = top->data;
	}
	counter++;
	FindClosest(top->right, average, closest, result, counter);
}
//Finds the closest element to the value of average

void result(binary_tree &tree) {
	double temp = 0;
	double average = Average(Sum(tree.top, temp), Size(tree.top, temp));
	cout << "The average between the elements is: " << average << endl;
	int closest = 0, result = 0, counter = 0;
	result = FindClosest(tree.top, average, closest, result, counter);
	cout << "The closest to the average top is: " << result << endl;
	elem *removed = del(tree.top, result);
	cout << "Removed the element: " << result << endl;
}

void infix(elem *top) {
	if (!top) {
		return;
	}
	infix(top->left);
	cout << top->data << " ";
	infix(top->right);
}
//Обхід у центрованому порядку

int main()
{
	srand(time(NULL));
	binary_tree tree;
	cout << "Enter the amount of elements: ";
	int n = 0;
	cin >> n;
	fill(tree, n);
	Print(tree);
	result(tree);
	Print(tree);
	return 0;
}