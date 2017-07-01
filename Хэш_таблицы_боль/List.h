#ifndef _LIST_H_
#define _LIST_H_
#include "TWord.h"

struct Node
{
	TWord data;
	Node *pNext;
};

class List
{
	Node*pHead;
	int maxSze;
	int length;
public:
	List() 
	{
		pHead = NULL;
		length = 0;
		maxSze = 0;
	}
	List(int max)
	{ 
		pHead = NULL; 
	    length = 0; 
	    maxSze = max; 
	}
	List(const List &l)
	{
		Node*p = l.pHead;
		while (p != 0)
		{
			PushBack(p->data);
			p = p->pNext;
		}
		maxSze = l.maxSze;
	}
	bool isEmpty() const
	{ return (pHead == 0); }

	~List()
	{
		Node  *p;
		while (!isEmpty())
		{
			p = pHead;
			pHead = pHead->pNext;
			delete p;
		}
	}

	Node* GetHead() { return pHead; }

	void SetMax(int max)
	{
		maxSze = max;
	}

	int GetLength() { return length; }

	void PushBack(TWord w)
	{
		Node *p = pHead;
		Node *newNode = new Node;
		newNode->data = w;
		newNode->pNext = NULL;
		// если список пуст
		if (isEmpty())
		{
			pHead = newNode;
		}
		else {
			// иначе

			while (p->pNext != NULL)
			{
				p = p->pNext;
			}
			p->pNext = newNode;
		}
		length++;
	}

	void PushFront(TWord w)
	{
		Node *newNode = new Node;
		newNode->data = w;
		newNode->pNext = pHead;
		pHead = newNode;
		length++;;
	}


	void SortInsert(TWord w)
	{
		if (isEmpty())
		{
			PushBack(w);
			return;
		}
		Node *p = pHead;
		Node *prev = NULL;
		while (p != NULL)
		{
			if (p->data.GetAmount() <w.GetAmount())
			{
				Node *newNode = new Node;
				newNode->data = w;
				newNode->pNext = p;

				if (prev != 0)
					prev->pNext = newNode;
				else
					pHead = newNode;

				length++;
				if (length > maxSze) deleteLast();
				return;
			}
			prev = p;
			p = p->pNext;

		}
		if (length<maxSze)
			PushBack(w);
	}

	void deleteLast()
	{
		int i = 0;
		Node *p, *prev;
		p = pHead;
		prev = NULL;
		while (i != maxSze)
		{
			prev = p;
			p = p->pNext;
			i++;
		}
		delete p;
		prev->pNext = NULL;
	}

	List & operator = (const List &l)
	{
		if (this == &l)
			return *this;
		Node *tmp;
		while (!isEmpty())
		{
			tmp = pHead;
			pHead = pHead->pNext;
			delete tmp;
		}
		tmp = l.pHead;
		while (tmp != 0)
		{
			PushBack(tmp->data);
			tmp = tmp->pNext;
		}
		this->maxSze = l.maxSze;
		return *this;
	}

	friend bool operator ==(const List &l1, const List &l2)
	{
		Node* p1 = l1.pHead, *p2 = l2.pHead;
		while (p1 && p2)
		{
			if (p1->data.GetWord() != p2->data.GetWord() || p1->data.GetAmount() != p2->data.GetAmount())
				return false;
			p1 = p1->pNext;
			p2 = p2->pNext;
		}
		return (p1 == 0 && p2 == 0);
	}

	friend bool operator !=(const List &l1, const List &l2)
	{
		return(!(l1 == l2));
	}

	friend ostream& operator << (ostream &os, List &l)
	{
		Node*p = l.pHead;
		while (p != NULL)
		{
			os << p->data << endl;
			p = p->pNext;
		}

		return os;
	}

};





#endif;
