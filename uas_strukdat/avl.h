#ifndef AVL_H
#define AVL_H

#include "mahasiswa.h"
#include <iostream>
#include <fstream>
using namespace std;

struct AVLNode {
    Mahasiswa data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Mahasiswa m) : data(m), left(NULL), right(NULL), height(1) {}
};

class AVL {
private:
    AVLNode* root;

    int getHeight(AVLNode* n);
    int getBalance(AVLNode* n);

    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

    AVLNode* insert(AVLNode* node, Mahasiswa m);
    AVLNode* search(AVLNode* node, string nim);
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* remove(AVLNode* node, string nim);

    void inorder(AVLNode* node);
    void clear(AVLNode* node);

    int countNodes(AVLNode* node);
    int heightTree(AVLNode* node);
    int countLeaves(AVLNode* node);

public:
    AVL();
    void insert(Mahasiswa m);
    Mahasiswa* search(string nim);
    void inorder();
    void remove(string nim);
    void clear();

    int countNodes();
    int height();
    int countLeaves();

    void exportToTxt(string filename);
    void printTable();

};

#endif
