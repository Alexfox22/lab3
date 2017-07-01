#ifndef  _TWORD_H_
#define _TWORD_H_

#include<string>
#include<iostream>

using namespace std;

class TWord
{
	string word;
	int count;
public:
	TWord()
	{
		word = " ";
		count = -1;
	};
	TWord(const TWord &w)
	{
		word = w.word;
		count = w.count;
	};

	void SetWord(string s)
	{
		word = TransformWord(s);
	};

	void SetAmount(const int &val)
	{
		count = val;
	};

	string GetWord()
	{
		return word;
	};

	int GetAmount()
	{
		return count;
	};

	string TransformWord(string s)
	{
		char c = s[0];
		char* word = new char[30];
		int i = 0;
	    int j = 0;
		while (s[i] != '\0' && ((isalpha(s[i]))||(s[i]=39)))
		{
			word[i] = tolower(s[i]);   //в строчный символ
			i++;
		}
		word[i] = '\0';
		return word;
	};

	TWord& operator =(const TWord& w)
	{
		word = w.word;
		count = w.count;
		return *this;
	};

	bool operator==(const TWord& w)
	{
		if (this->word == w.word) return true;
		else return false;
	};

	TWord operator++(int)
	{
		this->count++;
		return *this;
	};


	friend ostream& operator << (ostream &os, TWord &w)
	{
		cout << " Num of " ;
		os << w.word;
		cout << " is " << w.count;
		return os;
	}

};


#endif