#include <iostream>
#include <string>
#include "Stack.h"
#include <windows.h>
using namespace std;

struct Node
{
	string key;
	Node* l;
	Node* r;

	Node(string _key = 0, Node* _l = NULL, Node* _r = NULL)
		:key(_key), l(_l), r(_r)
	{}
};


void print(Node* curr)     // �������� TLR
{
	if (curr == NULL) return;
	cout << curr->key << " ";
	print(curr->l);
	print(curr->r);
}

void printItr(Node* root)  // ������������ TLR
{
	Stack<Node*>st;
	st.Push(root);
	while (!st.IsEmpty())
	{
		Node* curr = st.Top();
		st.Pop();
		cout << curr->key << " ";
		if (curr->r != NULL)
			st.Push(curr->r);
		if (curr->l != NULL)
			st.Push(curr->l);
	}
}

void deleteTree(Node* curr);

class Navigator                          // ���������
{
	Node* curr;
	Stack<Node*>path;
public:
	Navigator(Node* root)
	{
		curr = root;
	}

	Node* getCurr() { return curr; }       // �������� ������� �������� 

	string& value()
	{
		return curr->key;
	}


	bool left()                           // ������
	{
		if (curr->l == NULL) return false;
		path.Push(curr);
		curr = curr->l;
		return true;
	}
	bool right()                          // �������
	{
		if (curr->r == NULL) throw "curr->r == NULL";
		path.Push(curr);
		curr = curr->r;
		return true;
	}
	bool up()                             // �����
	{
		if (path.IsEmpty())
		{
			throw "path.IsEmpty()";
		}
		curr = path.Top();
		path.Pop();
		return true;
	}

	void addRigth(string v)                // �������� ������
	{
		Node* p = new Node(v, curr->r, NULL);
		curr->r = p;
	}

	void addLeft(string v)                 // �������� �����
	{
		Node* p = new Node(v, curr->l, NULL);
		curr->l = p;
	}

	void deleteR()                         // �������
	{
		deleteTree(curr->r);
		curr->r = NULL;
	}
};



void printText(Node* curr, int level, Node* sel)
{
	if (curr == NULL) return;
	if (curr == sel)cout << "*";
	else cout << " ";
	for (int i = 0; i < level; i++)
	{
		cout << "  ";
	}
	cout << curr->key << "\n";
	printText(curr->r, level + 1, sel);
	printText(curr->l, level, sel);
}

void deleteTree(Node* curr)
{
	if (curr == NULL) return;
	deleteTree(curr->l);
	deleteTree(curr->r);
	delete curr;
}

int main()
{

	//setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Node* p1 = new Node("����� 1");
	Node* p2 = new Node("����� 2");
	Node* p3 = new Node("����� 3");
	Node* p4 = new Node("����� 4", NULL, p1);
	Node* p5 = new Node("����� 5", p2, p4);
	Node* p6 = new Node("����� 6", p5, p3);
	Node* root = p6;

	Navigator n(root);

	bool f = true;
	int op;
	while (true)
	{
		system("cls");
		cout << "��������� �������� " << f << endl;
		cout << "������, �� ������� �� ���������� �������� ����������" << endl;
		printText(root, 0, n.getCurr());
		cout << "value " << n.value() << endl;
		cout << "1) ������ \n";
		cout << "2) ������� \n";
		cout << "3) ������ \n";
		cout << "4) ���������� �������� \n";
		cout << "5) �������� ������ \n";
		cout << "6) �������� ����� \n";
		cout << "7) ������� ������ \n";

		cin >> op;

		try
		{
			if (op == 1) f = n.left();
			if (op == 2) f = n.right();
			if (op == 3) f = n.up();
			if (op == 4)
			{
				string v;
				cin.ignore();
				getline(cin, v);
				//cin >> v;
				n.value() = v;
			}
			if (op == 5)                  // ������������� �������� ������
			{
				string v;
				cout << "Enter value:";
				cin >> v;
				n.addRigth(v);
			}
			if (op == 6)                  // ������������� �������� �����
			{
				string v;
				cout << "Enter value:";
				cin >> v;
				n.addLeft(v);
			}

			if (op == 7) n.deleteR();     // ������� �������� ������

		}
		catch (const char* str)
		{
			cout << str << endl;
			f = false;
		}

	}




	/*print(root); // �������� TLR
	cout << "\n";

	printItr(root);
	cout << "\n";*/

	return 0;
}