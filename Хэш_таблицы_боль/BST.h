#ifndef  _BST_H_
#define _BST_H_
#include "List.h";
#include "TWord.h";

using namespace std;

struct BSTNode
{
	TWord x;
	BSTNode *left, *right;

	BSTNode(BSTNode& n)
	{
		x = n.x;
		left = n.left;
		right = n.right;
	}

	BSTNode(TWord w)
	{
		x = w;
		left = NULL;
		right = NULL;
	}

	BSTNode& operator=(BSTNode& n)
	{
		x = n.x;
		left = n.left;
		right = n.right;
		return *this;
	}

};

class BinarySearchTree
{
private:
	BSTNode* root;

	BSTNode* FindWithParent(string s, BSTNode& parent)
	{
		BSTNode *current = root;
		while (current != NULL)
		{
			if (s<current->x.GetWord())// Если искомое значение меньше, идем налево.
			{

				parent = *current;
				current = current->left;
			}
			else
				if (s < current->x.GetWord())// Если искомое значение больше, идем направо.
				{
					parent = *current;
					current = current->right;
				}
				else break;
		}
		return current;
	}

public:

	BinarySearchTree()
	{
		root = NULL;
	};

	BSTNode* GetRoot()
	{
		return root;
	};

	void Insert(BSTNode* r,TWord w)
	{
		if (r == NULL)                          //Если дерево пустое, просто создаем корневой узел.
		{
			root = new BSTNode(w);
			return;
		}

		if (w.GetWord()<r->x.GetWord())        // Вставляемое значение меньше значения узла
		{
			if (r->left == NULL)               // Если нет левого поддерева, добавляем значение в левого ребенка
			{
				r->left = new BSTNode(w);
			}
			else
			{
				Insert(r->left, w);            // в противном случае повторяем для левого поддерева
			}
		}
		                                       // Вставляемое значение больше или равно значению узла.
		else
		{
			if (w.GetWord() == r->x.GetWord()) //Если слова одинаковые, то увеличиваем количество
			{
				r->x++;
				return;
			}
			if (r->right == NULL)               // Если нет правого поддерева, добавляем значение в правого ребенка
			{
				r->right = new BSTNode(w);
			}
			else
			{
				Insert(r->right, w);            // в противном случае повторяем для правого поддерева.
			}
		}
	}

	void Delete(string s)
	{
		BSTNode *current, *parent;

		// Находим удаляемый узел.
		current = FindWithParent(s, *parent);
		if (current == NULL)
		{
			return;
		}

		if (current->right == NULL)                       // Если нет детей справа, левый ребенок встает на место удаляемого.
		{
			if (parent == NULL)
			{
				root = current->left;
			}
			else
			{
				if (parent->x.GetWord()>current->x.GetWord())
				{
					// Если значение родителя больше текущего,
					// левый ребенок текущего узла становится левым ребенком родителя.
					parent->left = current->left;
				}
				else if (parent->x.GetWord()<current->x.GetWord())
				{ // Если значение родителя меньше текущего, левый ребенок текущего узла становится правым ребенком родителя. 
					parent->right = current->left;
				}
			}
		} // Если у правого ребенка нет детей слева то он занимает место удаляемого узла. 
		else if (current->right->left == NULL)
		{
			current->right->left = current->left;
			if (parent == NULL)
			{
				root = current->right;
			}
			else
			{
				if (parent->x.GetWord()>current->x.GetWord())
				{
					// Если значение родителя больше текущего,правый ребенок текущего узла становится левым ребенком родителя.
					parent->left = current->right;
				}
				else
					if (parent->x.GetWord()<current->x.GetWord())
					{ // Если значение родителя меньше текущего - правый ребенок текущего узла становится правым ребенком родителя.
						parent->right = current->right;
					}
			}
		} // Если у правого ребенка есть дети слева, крайний левый ребенок из правого поддерева заменяет удаляемый узел. 
		else {
			// Найдем крайний левый узел. 
			BSTNode* leftmost = current->right->left;
			BSTNode* leftmostParent = current->right;
			while (leftmost->left != NULL)
			{
				leftmostParent = leftmost;
				leftmost = leftmost->left;
			} // Левое поддерево родителя становится правым поддеревом крайнего левого узла. 
			leftmostParent->left = leftmost->right; // Левый и правый ребенок текущего узла становится левым и правым ребенком крайнего левого.
			leftmost->left = current->left;
			leftmost->right = current->right;
			if (parent == NULL) { root = leftmost; }
			else
			{
				if (parent>current)
				{
					// Если значение родителя больше текущего - крайний левый узел становится левым ребенком родителя.
					parent->left = leftmost;
				}
				else if (parent<current)
				{
					// Если значение родителя меньше текущего,
					// крайний левый узел становится правым ребенком родителя.
					parent->right = leftmost;
				}
			}
		}
	}

	TWord Search(BSTNode* r, string s)
	{
		BSTNode *current = r;
		while (current != NULL)
		{
			if (s<current->x.GetWord())// Если искомое значение меньше, идем налево.
			{

				return Search(current->left, s);
			}
			else
				if (s < current->x.GetWord())// Если искомое значение больше, идем направо.
				{
					return Search(current->right, s);
				}
				else break;

		}
		TWord res;
		res.SetWord("error");
		return res;
	}

	void PreOrderShow(BSTNode* node)
	{
		if (node != NULL)
		{
			cout << node->x << endl;
			PreOrderShow(node->left);
			PreOrderShow(node->right);
		}
	};

	void PostOrderShow(BSTNode *node)
	{
		if (node != NULL)
		{
			PostOrderShow(node->left);
			PostOrderShow(node->right);
			cout << node->x << endl;
		}
	};

	void InOrderShow(BSTNode *node)
	{
		if (node != NULL)
		{
			InOrderShow(node->left);

			cout << node->x << endl;

			InOrderShow(node->right);
		}
	};

	void FindMaxAmount(BSTNode *node, List& l)
	{
		if (node != NULL)
		{
			FindMaxAmount(node->left, l);

			l.SortInsert(node->x);

			FindMaxAmount(node->right, l);
		}
	};

};

#endif
