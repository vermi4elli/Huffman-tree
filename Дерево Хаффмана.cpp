#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

class Haffman_tree
{
private:
	struct node //Структура node, являющая собой узел дерева Хаффмана
	{
		node() {
			value = NULL;
			weight = NULL;
			left = NULL;
			right = NULL;
		}
		node(const char& value_t, const int& met_times) //Конструктор узла со значением элемента и частотой
		{
			value = value_t;
			weight = met_times;
			left = NULL;
			right = NULL;
		}
		node(node* x, node* y) //Конструктор узла-отца двух других узлов 
		{
			if (x->weight <= y->weight)
			{
				left = x;
				right = y;
			}
			else {
				left = y;
				right = x;
			}
			value = NULL;
			weight = x->weight + y->weight;
		}
		char value; //Значение символа
		int weight; //Кол-во встреч символа
		node *left, *right; //Указатели на левого и правого сына
	};
	node* root;
	bool filled;
	vector<node *> symbols;
public:
	Haffman_tree()
	{
		root = NULL;
		filled = 0;
	}
private:
	void infix(node* root, string &path)
	{
		if (!root)
		{
			path.pop_back();
			return;
		}
		if (root->left)
		{
			path += "0";
			infix(root->left, path);
		}
		if (root->value != NULL) {
			cout << "'" << root->value << "'" << " : " << path << endl;
		}
		if (root->right)
		{
			path += "1";
			infix(root->right, path);
		}
		if (path.size() != 0) 
		{
			path.pop_back();
			return;
		}
	}

	vector<node*> FillVector(const map<char, int>& dict) //Заполнение вектора элементов
	{
		vector<node*> result;
		for (const auto& item : dict)
		{
			node* symbol = new node(item.first, item.second);
			result.push_back(symbol);
		}
		return result;
	}

	void PrintVector(const vector<node*> x) {
		string delim = "\n==================================\n\n";
		cout << delim;
		cout << "The table of elements: \n" << endl;
		for (const auto& item : x) {
			cout << "'" << item->value << "'" << " : " << item->weight << endl;
		}
		cout << delim;
	}

public:
	void fill(const map<char, int>& dict) //Заполнение дерева Хаффмана
	{
		if (filled == 0) {
			symbols = FillVector(dict);
			sort(symbols.begin(), symbols.end(), [](node * x, node * y) {
				if (x->weight > y->weight) {
					return true;
				}
				return false;
				});
			while(symbols.size()>1)
			{
				
				node* min_1 = symbols[symbols.size()-1];						//Выбор двух
				node* min_2 = symbols[symbols.size()-2];						//наименьших элементов
				
				node* result = new node(min_1, min_2);							//Создание узла с данными двумя
				root = result;													//в качестве сыновей
				symbols.pop_back();					   
				symbols.pop_back();												//Удаление использованных элементов из вектора
				symbols.push_back(result);										//Вставка нового элемента в вектор
				sort(symbols.begin(), symbols.end(), [](node * x, node * y){	//Сортировка вектора в порядке убывания 
					if (x->weight > y->weight) {
						return true;
					}
					return false;
					});
				}
			filled = 1;
		}
		else {
			cout << "The tree is already built!" << endl;
		}
	}

	void print()
	{
		string delim = "\n==================================\n\n";
		cout << delim << "The Haffman code table:\n" << endl;
		string path = "";
		infix(root, path);
		cout << "\n" << delim;
	}
};

map<char, int> Fill(ifstream& stream)
{
	map <char, int> result;
	int counter = 0;
	string temp, buffer;
	while (stream)
	{
		stream >> temp;
		stream.ignore(1);
		buffer.append(temp);
	}
	for (const auto& x : buffer) {
		result[x]++;
	}
	return result;
}

void PrintMap(const map<char, int>& dict) {
	string delim = "\n==================================\n\n";
	cout << delim;
	cout << "The table of elements: \n" << endl;
	for (const auto& item : dict) {
		cout << "'" << item.first << "' : " << item.second << endl;
	}
	cout << delim;
}

int main(int argc, const char * argv[])
{
	ifstream stream("C:\\Users\\nikit\\Documents\\text.txt");		//Создание словаря повторяемости символов
	map<char, int> dict = Fill(stream);								// в тексте в виде : <символ>:<кол-во>
	PrintMap(dict);													//Вывод словаря на экран


	Haffman_tree tree;												//Создание и 
	tree.fill(dict);												//заполенение дерева Хаффмана
	tree.print();													//Вывод кодов для элементов в дереве Хаффмана


	system("pause");
	return 0;
}
