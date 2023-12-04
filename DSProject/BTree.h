#pragma once
template<typename T>
class BTreeNode{
	public:
	T data;

	int keys;
};
template <typename T>
class BTree {
	public:
		BTreeNode<T>* root;

};

