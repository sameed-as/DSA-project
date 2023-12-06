#pragma once
template<typename T>
class BTreeNode{ //A node which can hold mupltiple data values
	public:
	T* data;	//the data will be used to store the paths
	int order;	//Shows the number of children one node can hold
	BTreeNode** p_child; //Pointers for multiple childern of node  
	int* keys;	//keys for the hash values of the data 
	int no_of_keys;
	bool leaf;


	BTreeNode(int m  = 5  , bool is_leaf = true) {
		order = m;
		data = new T[order-1];
		p_child = new BTreeNode * [order];
		for (int i = 0; i < order; i++) {
			p_child[i] = nullptr;
		}
		keys = new int[order];
		leaf = is_leaf;
		no_of_keys = 0;
	}
	void splitChild(int index, BTreeNode<T>* root) {
		BTreeNode<T>* newChild = new BTreeNode(root->order, root->leaf);
		int min = ceil(order / 2);
		newChild->no_of_keys = min - 1;

		for (int j = 0; j < min - 1; j++)
			newChild->keys[j] = root->keys[j + min];

		if (root->leaf == false) {
			for (int j = 0; j < min; j++)
				newChild->p_child[j] = root->p_child[j + min];
		}

		root->no_of_keys = min - 1;
		for (int j = no_of_keys; j >= index + 1; j--)
			p_child[j + 1] = p_child[j];

		p_child[index + 1] = newChild;

		for (int j = no_of_keys - 1; j >= index; j--)
			keys[j + 1] = keys[j];

		keys[index] = root->keys[min - 1];
		no_of_keys = no_of_keys + 1;
	}
	void insertNonFull(int key) {
		int idx = no_of_keys - 1;

		if (leaf == true) {
			while (idx >= 0 && keys[idx] > key) {
				keys[idx + 1] = keys[idx];
				idx--;
			}

			keys[idx + 1] = key;
			no_of_keys = no_of_keys + 1;
		}
		else {
			while (idx >= 0 && keys[idx] > key)
				idx--;

			if (p_child[idx + 1]->no_of_keys == order - 1) {
				splitChild(idx + 1, p_child[idx + 1]);

				if (keys[idx + 1] < key)
					idx++;
			}
			p_child[idx + 1]->insertNonFull(key);
		}
	}

	~BTreeNode() {
		for (int i = 0; i < order; i++) {
			delete[] p_child[i];
		}
		delete[] p_child;
		delete[] keys;
		delete[] data;
	}
	
};
template <typename T>
class BTree {
	public:
		int order;	//Shows the number of children one node can hold
		BTreeNode<T>* root;
		BTree(int given_order) {
			root = nullptr;
			order = given_order;
		}
		void insert(int key) {
			if (root == nullptr) {
				root = new BTreeNode<T>(order, true);
				root->keys[0] = key;
				root->no_of_keys++;
			}
			else if (root->no_of_keys == order - 1) {
				BTreeNode<T>* s = new BTreeNode<T>(order, false);

				s->p_child[0] = root;

				s->splitChild(0, root);

				int i = 0;
				if (s->keys[0] < key)
					i++;
				s->p_child[i]->insertNonFull(key);

				root = s;
			}
			else {
				root->insertNonFull(key);
			}
			for (int i = 0; i < root->no_of_keys;i++) {
				std::cout << root->keys[i] << "   ";
			}
		}
};

