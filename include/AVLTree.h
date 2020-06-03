#pragma once
#include "Record.h"
#include <iostream>
using namespace std;

template<class Key, class Data>
class AVLTree {
protected:
	int size;
	Record<Key, Data>* head;
private:
	int height(Record<Key, Data>* rec);
	int bfactor(Record<Key, Data>* rec);
	void fixheight(Record<Key, Data>* rec);
	Record<Key, Data>* rotateright(Record<Key, Data>* rec);
	Record<Key, Data>* rotateleft(Record<Key, Data>* rec);
	Record<Key, Data>* balance(Record<Key, Data>* rec);
	Record<Key, Data>* findmin(Record<Key, Data>* rec);
	Record<Key, Data>* removemin(Record<Key, Data>* rec);
	Record<Key, Data>* insert(Record<Key, Data>* _head_, Key k, Data d);
	Record<Key, Data>* remove(Record<Key, Data>* _head_, Key k);
	Record<Key, Data>* find(Record<Key, Data>* _head_, Key k);
	void printTree(Record<Key, Data>* _head_, int p);
	void destroy(Record<Key, Data>* _head_);
public:
	AVLTree();
	void Add(Key key, Data data);
	void Delete(const Key key);
	Record<Key, Data>* Find(Key key);
	void Print();
	~AVLTree();
};

template<class Key, class Data>
AVLTree<Key, Data>::AVLTree()
{
	size = 0;
	head = nullptr;
}

template<class Key, class Data>
void AVLTree<Key, Data>::Add(Key key, Data data)
{
	Record<Key, Data>* rec = head;
	head = insert(rec, key, data);
	size++;
}

template<class Key, class Data>
void AVLTree<Key, Data>::Delete(const Key key)
{
	Record<Key, Data>* tmp = head;
	head = remove(tmp, key);
	size--;
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::Find(Key key)
{
	Record<Key, Data>* rec = head;
	Record<Key, Data>* tmp = find(rec, key);
	if (tmp->key != key)
	{
		cout << "Not find";
		return nullptr;
	}
	return find(rec, key);
}

template<class Key, class Data>
void AVLTree<Key, Data>::Print()
{
	Record<Key, Data>* tmp = head;
	printTree(tmp, 0);
}

template<class Key, class Data>
AVLTree<Key, Data>::~AVLTree() 
{
	destroy(head);
	head = nullptr;
	size = 0;
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::insert(Record<Key, Data>* _head_, Key k, Data d)
{
	if (_head_ == nullptr) return new Record<Key, Data>(k, d);
	if (k == _head_->key) _head_->data = d;
	if (k < _head_->key)
		_head_->left = insert(_head_->left, k, d);
	else
		_head_->right = insert(_head_->right, k, d);
	return balance(_head_);
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::remove(Record<Key, Data>* _head_, Key k)
{
	if (_head_ == nullptr) return 0;
	if (k < _head_->key)
		_head_->left = remove(_head_->left, k);
	else if (k > _head_->key)
		_head_->right = remove(_head_->right, k);
	else 
	{
		Record<Key, Data>* q = _head_->left;
		Record<Key, Data>* r = _head_->right;
		delete _head_;
		if (!r) return q;
		Record<Key, Data>* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(_head_);
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::find(Record<Key, Data>* _head_, Key key)
{
	if (_head_ == nullptr)
		throw "Error";
	if (key == _head_->key)
		return _head_;
	if (key < _head_->key && _head_->left != nullptr)
	{
		_head_ = find(_head_->left, key);
	}
	else
	{
		if (key > _head_->key && _head_->left != nullptr)
		{
			_head_ = find(_head_->right, key);
		}
	}
	return _head_;
}

template<class Key, class Data>
void AVLTree<Key, Data>::printTree(Record<Key, Data>* _head_, int p)
{
	int i;
	if (_head_ == nullptr) return;
	
	printTree(_head_->left, p+3);
	for (i = 0; i < p; i++)
		cout << " ";
	cout << "Key: " << _head_->key << " Data: " << _head_->data << " " << endl;
	printTree(_head_->right, p+3);
}

template<class Key, class Data>
 void AVLTree<Key, Data>::destroy(Record<Key, Data>* _head_)
{
	 if (_head_ != nullptr)
	 {
		 destroy(_head_->left);
		 destroy(_head_->right);
		 delete _head_;
	 }
}

template<class Key, class Data>
int AVLTree<Key, Data>::height(Record<Key, Data>* rec)
{
	return rec ? rec->height : 0;
}

template<class Key, class Data>
int AVLTree<Key, Data>::bfactor(Record<Key, Data>* rec)
{
	return height(rec->right) - height(rec->left);
}

template<class Key, class Data>
void AVLTree<Key, Data>::fixheight(Record<Key, Data>* rec)
{
	int hl = height(rec->left);
	int hr = height(rec->right);
	rec->height = (hl > hr ? hl : hr) + 1;
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::rotateright(Record<Key, Data>* rec)
{
	Record<Key, Data>* tmp = rec->left;
	rec->left = tmp->right;
	tmp->right = rec;
	fixheight(rec);
	fixheight(tmp);
	return tmp;
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::rotateleft(Record<Key, Data>* rec)
{
	Record<Key, Data>* tmp = rec->right;
	rec->right = tmp->left;
	tmp->left = rec;
	fixheight(rec);
	fixheight(tmp);
	return tmp;
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::balance(Record<Key, Data>* rec) 
{
	fixheight(rec);
	if (bfactor(rec) == 2)
	{
		if (bfactor(rec->right) < 0)
			rec->right = rotateright(rec->right);
		return rotateleft(rec);
	}
	if (bfactor(rec) == -2)
	{
		if (bfactor(rec->left) > 0)
			rec->left = rotateleft(rec->left);
		return rotateright(rec);
	}
	return rec; 
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::findmin(Record<Key, Data>* rec)
{
	return rec->left ? findmin(rec->left) : rec;
}

template<class Key, class Data>
Record<Key, Data>* AVLTree<Key, Data>::removemin(Record<Key, Data>* rec)
{
	if (rec->left == 0)
		return rec->right;
	rec->left = removemin(rec->left);
	return balance(rec);
}
