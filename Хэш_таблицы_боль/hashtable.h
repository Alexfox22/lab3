#pragma once
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include <string>
#include "TWord.h"
#include "List.h"
#include <ctime>

using namespace std;
const int len = 1000;
struct HashLink
{
	HashLink* pNext;
	int cur;
	TWord word;
};

class HashTable
{
private:
	HashLink* HTable[len];
	int HashFunc(string s)
	{
		double clock = 0;
		int count = 0;
		for (int i = 0; i < s.length(); i++)
		{
			count += s[i]*clock;
		}
		return (count % len);
	};
public:
	HashTable()
	{
		for (int i = 0; i < len; i++)
		{
			HTable[i] = new HashLink;
			HTable[i]->cur = 0;
			HTable[i]->pNext = NULL;
		}
	};

	TWord Search(string s)
	{
		int index = this->HashFunc(s);
		HashLink* tmp = HTable[index];
		if (tmp->word.GetWord() == s)
			return tmp->word;
		tmp = tmp->pNext;
		while (tmp != NULL)
		{
			if (tmp->word.GetWord() == s)
				return tmp->word;
			tmp = tmp->pNext;
		}
		TWord Error;
		Error.SetWord("error");
		return Error;
	};

	void Insert(TWord w)
	{
		int key = this->HashFunc(w.GetWord());
		if (HTable[key]->cur == 0)
		{
			HTable[key] = new HashLink;
			HTable[key]->word = w;
			HTable[key]->pNext = NULL;
			HTable[key]->cur = 1;
			return;
		}
		HashLink* tmp = HTable[key];
		if (HTable[key]->cur == 1 && tmp->word == w)
		{ tmp->word++; return; }

		while (tmp->pNext != NULL)
		{
			tmp = tmp->pNext;
			if (tmp->word == w)
			{
				tmp->word++;
				return;
			}
		}
		tmp->pNext = new HashLink;
		tmp = tmp->pNext;
		tmp->word = w;
		tmp->cur = 1;
		tmp->pNext = NULL;
	};

	void Delete(string s)
	{
		int key = this->HashFunc(s);
		if (HTable[key]->cur == 0)
			return;
		HashLink* tmp = HTable[key];
		if ((HTable[key]->word.GetWord() == s) && (HTable[key]->pNext == NULL))
		{
			delete tmp;
			HTable[key] = new HashLink;
			HTable[key]->cur = 0;
			HTable[key]->pNext = NULL;
			return;
		}
		if ((HTable[key]->word.GetWord() == s) && (HTable[key]->pNext != NULL))
		{
			HTable[key] = tmp->pNext;
			delete tmp;
			return;
		}
		HashLink* preTmp = tmp;
		tmp = tmp->pNext;
		while (tmp != NULL)
		{
			if (tmp->word.GetWord() == s)
			{
				preTmp->pNext = tmp->pNext;
				delete tmp;
				return;
			}
			preTmp = tmp;
			tmp = tmp->pNext;
		}
	};

	void ShowTable()
	{
		HashLink* tmp;
		cout << "        Hash Table" << endl;
		for (int i = 0; i < len; i++)
		{
			if (HTable[i]->cur == 1)
			{
				cout << " [ " << i << " ] " << HTable[i]->word << endl;
			}
			else
				continue;
			tmp = HTable[i];
			while (tmp->pNext != NULL)
			{
				tmp = tmp->pNext;
				cout << tmp->word << "   /n";
			}
		}
	};

	void FindMax(List& l)
	{
		HashLink* tmp;
		for (int i = 0; i < len; i++)
		{
			if (HTable[i]->cur == 1)
			{
				l.SortInsert(HTable[i]->word);
			}
			else
				continue;
			tmp = HTable[i];
			while (tmp->pNext != NULL)
			{
				tmp = tmp->pNext;
				l.SortInsert(tmp->word);
			}
		}
	};
};
#endif;