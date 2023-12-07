// Inserting a key on a B-tree in C++
// using the input of max nodes from user
#include<cmath>
#include <iostream>
using namespace std;

class BNode {
public:
    int* keys;
    int t;
    int tmin;
    BNode** C;
    int n;
    bool leaf;

    
    BNode(int t1, bool leaf1) {
        t = t1;
        leaf = leaf1;
        tmin = ceil((t + 1) / 2.0);
        keys = new int[t];
        for (int i = 0; i < t; i++)
        {
            keys[i] = INT16_MAX;
        }
        C = new BNode * [t+1];

        n = 0;
    }
    void splitChild(int i, BNode* y) {
        BNode* z = new BNode(y->t, y->leaf);
        z->n = tmin - 1;

        for (int j = 0; j < z->n; j++) {
            if(j+tmin < t)
            z->keys[j] = y->keys[j + tmin];
           // z->n++;
        }

        if (y->leaf == false) {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }

        y->n = tmin - 1;
        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];

        C[i + 1] = z;

        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];

        keys[i] = y->keys[tmin - 1];
        n = n + 1;
    }
    void insertNonFull(int k) {
        int i = n - 1;

        if (leaf == true) {
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k;
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
            C[i + 1]->insertNonFull(k);
            if (n > t) {
                cout << keys[3]<<endl;
                BNode* s = new BNode(t, false);

                s->C[0] = this;

                s->splitChild(0, this);

                int d = 0;
                if (s->keys[0] < keys[n])
                    d++;
                s->C[d]->insertNonFull(keys[n]);
                for (int i = 0; i < s->n; i++) {
                    this->keys[i] = s->keys[i];
                    this->C[i] = s->C[i];
                }
                this->C[n] = s->C[n];
                this->leaf = s->leaf;
                this->n = s->n;
            }
        }
    }
    void traverse();

};

class BTree {
public:
    BNode* root;
    int t;
    int tmin;

    BTree(int _t) {
        root = NULL;
        t = _t;
        tmin = ceil((t + 1) / 2.0);
    }

    void traverse() {
        if (root != NULL)
            root->traverse();
    }

    void insert(int k) {
        if (root == NULL) {
            root = new BNode(t, true);
            root->keys[0] = k;
            root->n = 1;
        }
        else {
            if (root->leaf == false) {
                root->insertNonFull(k);
            }
            else if (root->n == t) {
                BNode* s = new BNode(t, false);

                s->C[0] = root;

                s->splitChild(0, root);

                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k);

                root = s;
            }
            else
                root->insertNonFull(k);
        }
    }
};

// Traverse the nodes
void BNode::traverse() {
    int i = 0;
    while ( i < n) {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
        ++i;
    }

    if (leaf == false)
        C[i]->traverse();
}


