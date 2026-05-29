#ifndef BST_H
#define BST_H

#include "mahasiswa.h"
#include <iostream>
#include <fstream>
using namespace std;

struct BSTNode {
    Mahasiswa data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Mahasiswa m) : data(m), left(NULL), right(NULL) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, Mahasiswa m);
    BSTNode* search(BSTNode* node, string nim);
    BSTNode* remove(BSTNode* node, string nim);
    BSTNode* minValueNode(BSTNode* node);

    void inorder(BSTNode* node);
    void clear(BSTNode* node);
    
    // Statistik
    int countNodes(BSTNode* node);
    int height(BSTNode* node);
    int countLeaves(BSTNode* node);

public:
    BST();
    void insert(Mahasiswa m);
    Mahasiswa* search(string nim);
    void inorder();
    void remove(string nim);
    void clear();

    // Statistik
    int countNodes();
    int height();
    int countLeaves();

    // Export
    void exportToTxt(string filename);

    // Tabel (TAMBAHAN)
    void printTable();
};

#endif
