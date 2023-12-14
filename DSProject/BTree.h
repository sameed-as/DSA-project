// Inserting a key on a B-tree in C++
// using the input of max nodes from user
#pragma once
#include<cmath>
#include "doublyLL.h"
#include <queue>
#include <iostream>

using namespace std;

class BNode {
public:
    int* keys;
    DoublyLinkedList<string>* listData;
    int t;
    int tmin;
    BNode** C;
    int n;
    bool leaf;
    bool isleaf() {
        for (int i = 0;i <= n;i++) {
            if (C[i] != nullptr) {
                return false;
            }
        }
        return true;
    }

    BNode(int t1, bool leaf1) {
        t = t1;
        leaf = leaf1;

        tmin = ceil((t + 1) / 2.0);
        keys = new int[t];
        listData = new DoublyLinkedList<string>[t];
        for (int i = 0; i < t; i++) {
            keys[i] = INT16_MAX;
        }
        C = new BNode * [t + 1];
        for (int i = 0;i < t + 1;i++) {
            C[i] = nullptr;
        }

        n = 0;

    }
    void splitChild(int i, BNode* y) {
        BNode* z = new BNode(y->t, y->isleaf());
        z->n = tmin - 1;

        for (int j = 0; j < z->n; j++) {
            if (j + tmin < t) {
                z->keys[j] = y->keys[j + tmin];
                z->listData[j] = y->listData[j + tmin];
            }
            // z->n++;
            else
                z->n--;
        }

        if (y->isleaf() == false) {
            for (int j = 0; j < tmin; j++)
                z->C[j] = y->C[j + tmin];
        }

        y->n = tmin - 1;
        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];

        C[i + 1] = z;

        for (int j = n - 1; j >= i; j--) {
            keys[j + 1] = keys[j];
            listData[j + 1] = listData[j];
        }

        keys[i] = y->keys[tmin - 1];
        listData[i] = y->listData[tmin - 1];
        n = n + 1;
        for (int i = n + 1; i < t + 1;i++) {
            C[i] = nullptr;
        }
        for (int i = z->n + 1; i < t + 1; i++) {
            z->C[i] = nullptr;
        }
        for (int i = y->n + 1;i < t + 1;i++) {
            y->C[i] = nullptr;
        }
    }
    void insertNonFull(int k, string dataVal) {
        int i = n - 1;

        if (isleaf() == true) {
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
        else {
            while (i >= 0 && keys[i] > k)
                i--;

            if (C[i + 1]->n == t) {
                splitChild(i + 1, C[i + 1]);

                if (keys[i + 1] < k)
                    i++;
            }
            C[i + 1]->insertNonFull(k, dataVal);
        }
    }

    void traverse();

};

class BTree {
public:
    BNode* root;
    int t;
    int tmin;

    BTree() {
        root = nullptr;
        t = tmin = 0;
    }

    BTree(int _t) {
        root = NULL;
        t = _t;
        tmin = ceil((t + 1) / 2.0);
    }

    void helperTraverse(BNode*& root, queue<BNode*>& que) {
        for (int i = 0; i <= root->n; i++) {
            if (root->C[i]) {
                helperTraverse(root->C[i], que);
                que.push(root->C[i]);
            }
        }
    }

    void traverse_pelyvala() {
        if (root != NULL) {
            root->traverse();
        }
    }
    void traverse() {
        if (root != NULL) {
            queue <BNode*> que;
            helperTraverse(root, que);
        }
    }

    void insert(int k, string dataValue) {
        if (root == NULL) {
            root = new BNode(t, true);
            root->keys[0] = k;
            root->listData[0].insert(dataValue);
            root->n = 1;
        }
        else {
            if (!Search(root, k, dataValue)) {
                if (root->n == t) {
                    BNode* s = new BNode(t, false);

                    s->C[0] = root;

                    s->splitChild(0, root);

                    int i = 0;
                    if (s->keys[0] < k)
                        i++;
                    s->C[i]->insertNonFull(k, dataValue);

                    root = s;
                }
                else
                    root->insertNonFull(k, dataValue);
            }
        }

    }
    bool Search(BNode*& r, int k, string dataVal) {
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
        return Search(r->C[i], k, dataVal);
    }
    bool  Search_forDel(BNode*& r, int k) {
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
            }
            return true;
        }
        if (r->isleaf()) {
            return false;
        }
        return Search_forDel(r->C[i], k);
    }
    void delete_helper(BNode*& node, BNode*& parent, int& k, int& pos, bool& found, bool& k_swaped, bool& delete_occured, BNode*& root, bool& root_Updated) {
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
            delete_helper(node->C[i], node, k, i, found, k_swaped, delete_occured, root, root_Updated);
        }
        if (!node->isleaf() && !k_swaped && !delete_occured) {
            BNode* change_k = node;
            node = node->C[i];//go left
            while (!node->isleaf()) {//and then right
                node = node->C[node->n];
            }
            //the value to be deleted is replaced with the largest value in left subtree
            int temp = change_k->keys[i];
            change_k->keys[i] = node->keys[node->n - 1];
            node->keys[node->n - 1] = temp;
            found = false;
            k_swaped = true;
            vapis_mur = false;
            delete_helper(change_k->C[i], change_k, k, i, found, k_swaped, delete_occured, root, root_Updated);//again deletion will be call for updated key
            node = change_k;
        }
        if (node == root && root->n == 1 && root->isleaf()) {
            root->n--;
            root = NULL;
            return;
        }
        if (!root_Updated)
            if ((vapis_mur && node->isleaf()) || (node->n < tmin - 1 && parent != nullptr)) {
                if (node->n >= tmin) {
                    while (i < node->n) {
                        node->keys[i] = node->keys[i + 1];
                        i++;
                    }
                    node->n -= 1;
                    delete_occured = true;
                }
                else {
                    //Left sibling case
                    if (pos > 0 && parent->C[pos - 1]->n >= tmin) {
                        int idx = i;
                        while (idx > 0) {
                            node->keys[idx] = node->keys[idx - 1];
                            idx--;
                        }

                        node->keys[0] = parent->keys[pos - 1];
                        parent->keys[pos - 1] = parent->C[pos - 1]->keys[parent->C[pos - 1]->n - 1];
                        parent->C[pos - 1]->n--;
                        idx = node->n;
                        while (idx > 0) {
                            node->C[idx] = node->C[idx - 1];
                            idx--;
                        }
                        node->C[0] = parent->C[pos - 1]->C[parent->C[pos - 1]->n + 1];
                        parent->C[pos - 1]->C[parent->C[pos - 1]->n + 1] = nullptr;
                        delete_occured = true;
                    }
                    //RightSibling Case
                    else if (pos <= parent->n - 1 && parent->C[pos + 1]->n >= tmin) {
                        int idx = i;
                        while (idx < node->n - 1) {
                            node->keys[idx] = node->keys[idx + 1];
                            idx++;
                        }
                        if (node->n == 0)
                            node->n++;
                        node->keys[node->n - 1] = parent->keys[pos];
                        parent->keys[pos] = parent->C[pos + 1]->keys[0];
                        int j = 0;
                        while (j < parent->C[pos + 1]->n - 1) {
                            parent->C[pos + 1]->keys[j] = parent->C[pos + 1]->keys[j + 1];
                            j++;
                        }
                        parent->C[pos + 1]->n--;
                        node->C[node->n] = parent->C[pos + 1]->C[0];
                        idx = 0;
                        while (idx < parent->C[pos + 1]->n + 1) {
                            parent->C[pos + 1]->C[idx] = parent->C[pos + 1]->C[idx + 1];
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
                                    idx++;
                                }
                                node->n--;
                            }
                            parent->C[pos - 1]->keys[parent->C[pos - 1]->n] = parent->keys[pos - 1];
                            parent->C[pos - 1]->n++;
                            int inc_n = 0;
                            idx = 0;
                            while (idx < node->n) {
                                parent->C[pos - 1]->keys[idx + parent->C[pos - 1]->n] = node->keys[idx];
                                inc_n++;
                                idx++;
                            }
                            idx = 0;
                            while (idx < node->n + 1) {
                                parent->C[pos - 1]->C[idx + parent->C[pos - 1]->n] = node->C[idx];/////////////////////////////////
                                idx++;
                            }
                            parent->C[pos - 1]->n += inc_n;
                            idx = pos - 1;
                            while (idx < parent->n - 1) {
                                parent->keys[idx] = parent->keys[idx + 1];
                                idx++;
                            }
                            idx = pos;
                            while (idx < parent->n + 1) {
                                parent->C[idx] = parent->C[idx + 1];
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
                                    idx++;
                                }
                                node->keys[node->n - 1] = parent->keys[pos];

                            }
                            else {
                                node->keys[node->n] = parent->keys[pos];
                                node->n++;
                            }
                            idx = 0;
                            while (idx < parent->C[pos + 1]->n) {
                                node->keys[node->n + idx] = parent->C[pos + 1]->keys[idx];
                                idx++;
                                inc_n++;
                            }
                            idx = 0;
                            while (idx < parent->C[pos + 1]->n + 1) {
                                node->C[node->n + idx] = parent->C[pos + 1]->C[idx];///////////////////////////////////////
                                idx++;
                            }
                            idx--;
                            node->n += idx;
                            idx = pos;
                            while (idx < parent->n - 1) {
                                parent->keys[idx] = parent->keys[idx + 1];
                                idx++;
                            }
                            idx = pos + 1;
                            while (idx < parent->n + 1) {
                                parent->C[idx] = parent->C[idx + 1];
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

    void deletion(int k) {
        bool found = false;
        bool k_swaped = false;
        bool delete_occured = false;
        bool root_Updated = false;
        BNode* temp = nullptr;
        int pos = 0;
        if (!Search_forDel(root, k))
            delete_helper(root, temp, k, pos, found, k_swaped, delete_occured, root, root_Updated);
    }
};

// Traverse the nodes

void BNode::traverse() {

    int i = 0;
    if (C[i] != nullptr) {
        C[i]->traverse();
    }

    for (i = 1; i <= n; i++) {
        cout << " " << keys[i - 1];

        if (C[i] != nullptr)
            C[i]->traverse();
    }
}


