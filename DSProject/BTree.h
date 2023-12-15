
#pragma once
#include<cmath>
#include "doublyLL.h"
#include <queue>
#include "BigInt.h"
#include <iostream>

using namespace std;

class BNode {
public:
    BigInt* keys;
    DoublyLinkedList<string>* listData;
    int tmax;
    int tmin;
    BNode** children;
    int n;


    bool isleaf() {
        for (int i = 0;i <= n;i++) {
            if (children[i] != nullptr) {
                return false;
            }
        }
        return true;
    }

    BNode(int t1) {
        tmax = t1;

        tmin = ceil((tmax + 1) / 2.0);
        keys = new BigInt[tmax];
        listData = new DoublyLinkedList<string>[tmax];
        for (int i = 0; i < tmax; i++) {
            keys[i] = INT16_MAX;
        }
        children = new BNode * [tmax + 1];
        for (int i = 0;i < tmax + 1;i++) {
            children[i] = nullptr;
        }

        n = 0;

    }
    void splitChild(int i, BNode* leftChild) {
        BNode* rightChild = new BNode(leftChild->tmax);
        rightChild->n = tmin - 1;
        int j = 0;
        while (j < rightChild->n) {
            if (j + tmin < tmax) {
                rightChild->keys[j] = leftChild->keys[j + tmin];
                rightChild->listData[j] = leftChild->listData[j + tmin];
            }
            // rightChild->n++;
            else
                rightChild->n--;
            j++;
        }

        j = 0;
        if (leftChild->isleaf() == false) {
            for (int j = 0; j < tmin; j++)
                rightChild->children[j] = leftChild->children[j + tmin];
        }

        leftChild->n = tmin - 1;
        for (int j = n; j >= i + 1; j--)
            children[j + 1] = children[j];

        children[i + 1] = rightChild;

        for (int j = n - 1; j >= i; j--) {
            keys[j + 1] = keys[j];
            listData[j + 1] = listData[j];
        }

        keys[i] = leftChild->keys[tmin - 1];
        listData[i] = leftChild->listData[tmin - 1];
        n = n + 1;
        for (int i = n + 1; i < tmax + 1;i++) {
            children[i] = nullptr;
        }
        for (int i = rightChild->n + 1; i < tmax + 1; i++) {
            rightChild->children[i] = nullptr;
        }
        for (int i = leftChild->n + 1;i < tmax + 1;i++) {
            leftChild->children[i] = nullptr;
        }
    }
    void insertFreeSpace(BigInt k, string dataVal) {
        int i = n - 1;

        if (isleaf() != true) {
            while (i >= 0 && keys[i] > k)
                i--;

            if (children[i + 1]->n == tmax) {
                splitChild(i + 1, children[i + 1]);

                if (keys[i + 1] < k)
                    i++;
            }
            children[i + 1]->insertFreeSpace(k, dataVal);
        }

        else {
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                listData[i + 1] = listData[i];
                i--;
            }

            keys[i + 1] = k;
            if (listData[i + 1].isEmpty())
                listData[i + 1].insert(dataVal);
            else
                listData[i + 1].getHead()->data = dataVal;
            n = n + 1;
        }
    }

    void traverse() {

        int i = 0;
        if (children[i] != nullptr) {
            children[i]->traverse();
        }

        for (i = 1; i <= n; i++) {
            cout << " " << keys[i - 1];

            if (children[i] != nullptr)
                children[i]->traverse();
        }
    }
};

class BTree {
public:
    BNode* root;
    int order;
    int tmax;
    int tmin;

    BTree() {
        root = nullptr;
        tmax = tmin = 0;
        order = 0;
    }

    BTree(int _t) {
        root = NULL;
        order = _t;
        tmax = _t - 1;
        tmin = ceil((tmax + 1) / 2.0);
    }



    void traverse_pelyvala() {
        if (root != NULL) {
            root->traverse();
        }
    }



    void insert(BigInt k, string dataValue) {
        if (root == NULL) {
            root = new BNode(tmax);
            root->keys[0] = k;
            root->listData[0].insert(dataValue);
            root->n = 1;
        }
        else {
            if (!searchForDupsInsert(root, k, dataValue)) {
                if (root->n == tmax) {
                    BNode* newRoot = new BNode(tmax);

                    newRoot->children[0] = root;

                    newRoot->splitChild(0, root);

                    int i = 0;
                    if (newRoot->keys[0] < k)
                        i++;
                    newRoot->children[i]->insertFreeSpace(k, dataValue);

                    root = newRoot;
                }
                else
                    root->insertFreeSpace(k, dataValue);
            }
        }

    }
    bool searchForDupsInsert(BNode*& r, BigInt k, string dataVal) {
        int i = 0;
        while (i < r->n && k > r->keys[i]) {
            i++;
        }
        if (i < r->n && k == r->keys[i]) {
            r->listData[i].insert(dataVal);
            return true;
        }
        if (r->isleaf()) {
            return false;
        }
        return searchForDupsInsert(r->children[i], k, dataVal);
    }
    bool  Search_forDel(BNode*& r, BigInt k) {
        int i = 0;
        while (i < r->n && k > r->keys[i]) {
            i++;
        }
        if (i < r->n && k == r->keys[i]) {
            if (r->listData[i].size == 1) {
                return false;
            }
            else {
                int choice = 0;
                r->listData[i].print();
                cout << "Choose your Data to delete: " << endl;
                cin >> choice;
                r->listData[i].deleteData(choice);
                cout << endl;
            }
            return true;
        }
        if (r->isleaf()) {
            return false;
        }
        return Search_forDel(r->children[i], k);
    }
    void delete_helper(BNode*& node, BNode*& parent, BigInt& k, int& pos, bool& found, bool& k_swaped, bool& delete_occured, BNode*& root, bool& root_Updated) {
        int i = 0;
        bool vapis_mur = true;
        while (i < node->n && k > node->keys[i]) {
            i++;
        }
        if (node->keys[i] == k && i < node->n)
            found = true;
        if (node->isleaf() && !found) {
            cout << "Key doesnt exist " << endl;
            return;
        }
        if (!found) {
            delete_helper(node->children[i], node, k, i, found, k_swaped, delete_occured, root, root_Updated);
        }
        if (!node->isleaf() && !k_swaped && !delete_occured) {
            BNode* change_k = node;
            node = node->children[i];//go left
            while (!node->isleaf()) {//and then right
                node = node->children[node->n];
            }
            //the value to be deleted is replaced with the largest value in left subtree
            BigInt temp = change_k->keys[i];
            DoublyLinkedList<string> listTemp;
            listTemp = change_k->listData[i];
            change_k->keys[i] = node->keys[node->n - 1];
            change_k->listData[i] = node->listData[node->n - 1];
            node->keys[node->n - 1] = temp;
            node->listData[node->n - 1] = listTemp;
            found = false;
            k_swaped = true;
            vapis_mur = false;
            delete_helper(change_k->children[i], change_k, k, i, found, k_swaped, delete_occured, root, root_Updated);//again deletion will be call for updated key
            node = change_k;
        }
        if (node == root && root->n == 1 && root->isleaf() && !parent) {
            root->n--;
            root = NULL;
            return;
        }
        if (!root_Updated)
            if ((vapis_mur && node->isleaf()) || (node->n < tmin - 1 && parent != nullptr)) {
                if (node->n >= tmin) {
                    while (i < node->n) {
                        node->keys[i] = node->keys[i + 1];
                        node->listData[i] = node->listData[i + 1];
                        i++;
                    }
                    node->n -= 1;
                    delete_occured = true;
                }
                else {
                    //Left sibling case
                    if (pos > 0 && parent->children[pos - 1]->n >= tmin) {
                        int idx = i;
                        while (idx > 0) {
                            node->keys[idx] = node->keys[idx - 1];
                            node->listData[idx] = node->listData[idx - 1];
                            idx--;
                        }

                        node->keys[0] = parent->keys[pos - 1];
                        node->listData[0] = parent->listData[pos - 1];
                        parent->keys[pos - 1] = parent->children[pos - 1]->keys[parent->children[pos - 1]->n - 1];
                        parent->listData[pos - 1] = parent->children[pos - 1]->listData[parent->children[pos - 1]->n - 1];
                        parent->children[pos - 1]->n--;
                        idx = node->n;
                        while (idx > 0) {
                            node->children[idx] = node->children[idx - 1];
                            idx--;
                        }
                        node->children[0] = parent->children[pos - 1]->children[parent->children[pos - 1]->n + 1];
                        parent->children[pos - 1]->children[parent->children[pos - 1]->n + 1] = nullptr;
                        delete_occured = true;
                    }
                    //RightSibling Case
                    else if (pos <= parent->n - 1 && parent->children[pos + 1]->n >= tmin) {
                        int idx = i;
                        while (idx < node->n - 1) {
                            node->keys[idx] = node->keys[idx + 1];
                            node->listData[idx] = node->listData[idx + 1];
                            idx++;
                        }
                        if (node->n == 0)
                            node->n++;
                        node->keys[node->n - 1] = parent->keys[pos];
                        node->listData[node->n - 1] = parent->listData[pos];
                        parent->keys[pos] = parent->children[pos + 1]->keys[0];
                        parent->listData[pos] = parent->children[pos + 1]->listData[0];
                        int j = 0;
                        while (j < parent->children[pos + 1]->n - 1) {
                            parent->children[pos + 1]->keys[j] = parent->children[pos + 1]->keys[j + 1];
                            j++;
                        }
                        parent->children[pos + 1]->n--;
                        node->children[node->n] = parent->children[pos + 1]->children[0];
                        idx = 0;
                        while (idx < parent->children[pos + 1]->n + 1) {
                            parent->children[pos + 1]->children[idx] = parent->children[pos + 1]->children[idx + 1];
                            idx++;
                        }
                        delete_occured = true;
                    }
                    //Merge Case
                    else {
                        //Case left siblng merge
                        if (pos > 0) {
                            int idx = i;
                            if (!delete_occured) {
                                while (idx < node->n - 1) {
                                    node->keys[idx] = node->keys[idx + 1];
                                    node->listData[idx] = node->listData[idx + 1];
                                    idx++;
                                }
                                node->n--;
                            }
                            parent->children[pos - 1]->keys[parent->children[pos - 1]->n] = parent->keys[pos - 1];
                            parent->children[pos - 1]->listData[parent->children[pos - 1]->n] = parent->listData[pos - 1];
                            parent->children[pos - 1]->n++;
                            int inc_n = 0;
                            idx = 0;
                            while (idx < node->n) {
                                parent->children[pos - 1]->keys[idx + parent->children[pos - 1]->n] = node->keys[idx];
                                parent->children[pos - 1]->listData[idx + parent->children[pos - 1]->n] = node->listData[idx];
                                inc_n++;
                                idx++;
                            }
                            idx = 0;
                            while (idx < node->n + 1) {
                                parent->children[pos - 1]->children[idx + parent->children[pos - 1]->n] = node->children[idx];/////////////////////////////////
                                idx++;
                            }
                            parent->children[pos - 1]->n += inc_n;
                            idx = pos - 1;
                            while (idx < parent->n - 1) {
                                parent->keys[idx] = parent->keys[idx + 1];
                                parent->listData[idx] = parent->listData[idx + 1];
                                idx++;
                            }
                            idx = pos;
                            while (idx < parent->n + 1) {
                                parent->children[idx] = parent->children[idx + 1];
                                idx++;
                            }
                            parent->n--;
                            if (root->n == 0) {
                                root = node;
                                root_Updated = true;
                            }
                            delete_occured = true;
                        }
                        //case right sibling merge
                        else {
                            int idx = i;
                            int inc_n = 0;
                            if (!delete_occured) {
                                while (idx < node->n - 1) {
                                    node->keys[idx] = node->keys[idx + 1];
                                    node->listData[idx] = node->listData[idx + 1];
                                    idx++;
                                }
                                node->keys[node->n - 1] = parent->keys[pos];
                                node->listData[node->n - 1] = parent->listData[pos];
                            }
                            else {
                                node->keys[node->n] = parent->keys[pos];
                                node->listData[node->n] = parent->listData[pos];
                                node->n++;
                            }
                            idx = 0;
                            while (idx < parent->children[pos + 1]->n) {
                                node->keys[node->n + idx] = parent->children[pos + 1]->keys[idx];
                                node->listData[node->n + idx] = parent->children[pos + 1]->listData[idx];
                                idx++;
                                inc_n++;
                            }
                            idx = 0;
                            while (idx < parent->children[pos + 1]->n + 1) {
                                node->children[node->n + idx] = parent->children[pos + 1]->children[idx];///////////////////////////////////////
                                idx++;
                            }
                            idx--;
                            node->n += idx;
                            idx = pos;
                            while (idx < parent->n - 1) {
                                parent->keys[idx] = parent->keys[idx + 1];
                                parent->listData[idx] = parent->listData[idx + 1];
                                idx++;
                            }
                            idx = pos + 1;
                            while (idx < parent->n + 1) {
                                parent->children[idx] = parent->children[idx + 1];
                                idx++;
                            }
                            parent->n--;
                            if (root->n == 0) {
                                root = node;
                                root_Updated = true;
                            }
                            delete_occured = true;
                        }
                    }
                }
            }

    }

    void deletion(BigInt k) {
        bool found = false;
        bool k_swaped = false;
        bool delete_occured = false;
        bool root_Updated = false;
        BNode* temp = nullptr;
        int pos = 0;
        if (!Search_forDel(root, k))
            delete_helper(root, temp, k, pos, found, k_swaped, delete_occured, root, root_Updated);
    }

    void levelOrderTraversal() const {
        if (!root) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        std::queue<BNode*> q;
        q.push(root);
        int lvl = 1;
        while (!q.empty()) {
            cout << "Level : " << lvl << " : ";
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                BNode* current = q.front();
                q.pop();

                for (int j = 0; j < current->n; ++j) {
                    std::cout << current->keys[j] << " ";
                }
                cout << "\t";
                if (!current->isleaf()) {
                    for (int j = 0; j <= current->n; ++j) {
                        if (current->children[j]) {
                            q.push(current->children[j]);
                        }
                    }
                }
            }
            lvl++;
            std::cout << std::endl;
        }
    }    
};
    void split(BNode* root ,BTree& A, BTree& B, BigInt Threshold) {
        int i = 0;
        if (root->children[i] != nullptr) {
            split(root->children[i], A, B, Threshold);
        }
        for (i = 1; i <= root->n;i++) {
            ///SPlit
            if (root->keys[i] <= Threshold){
                DoublyNode<string>* curr = root->listData[i].head;
                while (curr) {
                    A.insert(root->keys[i], curr->data);
                    curr = curr->next;
                }
            }
            else {
                DoublyNode<string>* curr = root->listData[i].head;
                while (curr) {
                    B.insert(root->keys[i], curr->data);
                    curr = curr->next;
                }
            }

            if (root->children[i] != nullptr)
                split(root->children[i], A, B, Threshold);
        }
    }

    void merge_traversal(BNode* ARoot, BTree& NewTree) {

    }

    void merge(BNode* ARoot, BNode* BRoot, BTree& NewTree) {

    }

