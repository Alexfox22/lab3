#include "TWord.h"
#include "List.h"
#include "AVL.h"
#include "BST.h"
#include "hashtable.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>


using namespace std;

int main()
{
	HashTable HTable;
	BinarySearchTree BSTree;
	AVLTree AVLTr;

	ifstream fin; //для чтения из файла
	int i = 0;
	int qwerty;

	double clockHT = 0, clockBS = 0, clockAVL = 0;
	double start, finish;

	string txt;
	TWord word;
	cout << "Do you want to enter the text? (1-yes, 0-no) " << endl;
	cin >> qwerty;

	if (qwerty == 1)
	{
		char c[999];
		ofstream fout;
		fout.open("text.txt");
		if (!fout)
		{
			cout << "Error" << endl;
			return 0;
		}
		else cout << "Opened" << endl;
		cin >> c;
		fout << c;
		cin.getline(c, 999);
		fout << c;
		fout.close();
	}

	fin.open("text.txt");
	if (!fin)
	{
		cout << "Error" << endl;
		return 0;
	}
	cout << "Top of words" << endl;

	while (!fin.eof())
	{
		fin >> txt;
		word.SetWord(txt);
		word.SetAmount(1);
		HTable.Insert(word);
		BSTree.Insert(BSTree.GetRoot(), word);
		AVLTr.Insert(AVLTr.GetRoot(), word);

	}


	List topH(10);
	List resultForBin(10);
	List resultForAVL(10);

	start = clock();
	HTable.FindMax(topH);
	finish = clock();
	clockHT += finish - start;

	start = clock();
	BSTree.FindMaxAmount(BSTree.GetRoot(), resultForBin);
	finish = clock();
	clockBS += finish - start;

	start = clock();
	AVLTr.FindMaxAmount(AVLTr.GetRoot(), resultForAVL);
	finish = clock();
	clockAVL += finish - start;

	cout << topH;

    /*
    cout << "//////////////////////////////////////////////////////////////" << endl;
	cout << resultForBin;
	cout << "//////////////////////////////////////////////////////////////" << endl;
	cout << resultForAVL;
	*/

	
	cout << "Time for HT   " << clockHT << "ms" << endl;

	cout << "Time for BS tree  " << clockBS << "ms" << endl;

	cout << "Time for AVL tree  " << clockAVL << "ms" << endl;

	return 0;
}