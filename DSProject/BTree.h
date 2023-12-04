#pragma once
template<typename T>
class BTreeNode{
	public:
	T data;


};
template <typename T>
class BTree {
	public:
		BTreeNode<T>* root;
};

