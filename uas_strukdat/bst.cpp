#include "bst.h"
#include <fstream>
#include <functional> 
#include <iomanip>

BST::BST() {
    root = NULL;
}

BSTNode* BST::insert(BSTNode* node, Mahasiswa m) {
    if (!node) return new BSTNode(m);

    if (m.nim < node->data.nim)
        node->left = insert(node->left, m);
    else if (m.nim > node->data.nim)
        node->right = insert(node->right, m);
    else
        node->data = m; // replace

    return node;
}

void BST::insert(Mahasiswa m) {
    root = insert(root, m);
}

BSTNode* BST::search(BSTNode* node, string nim) {
    if (!node) return NULL;
    if (nim == node->data.nim) return node;
    if (nim < node->data.nim) return search(node->left, nim);
    return search(node->right, nim);
}

Mahasiswa* BST::search(string nim) {
    BSTNode* res = search(root, nim);
    return res ? &res->data : NULL;
}

void BST::inorder(BSTNode* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->data.nim << " - " << node->data.nama << " - " << node->data.prodi << endl;
    inorder(node->right);
}

void BST::inorder() {
    inorder(root);
}

BSTNode* BST::minValueNode(BSTNode* node) {
    BSTNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

BSTNode* BST::remove(BSTNode* node, string nim) {
    if (!node) return node;

    if (nim < node->data.nim)
        node->left = remove(node->left, nim);
    else if (nim > node->data.nim)
        node->right = remove(node->right, nim);
    else {
        if (!node->left) {
            BSTNode* t = node->right;
            delete node;
            return t;
        }
        else if (!node->right) {
            BSTNode* t = node->left;
            delete node;
            return t;
        }

        BSTNode* t = minValueNode(node->right);
        node->data = t->data;
        node->right = remove(node->right, t->data.nim);
    }
    return node;
}

void BST::remove(string nim) {
    root = remove(root, nim);
}

void BST::clear(BSTNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void BST::clear() {
    clear(root);
    root = NULL;
}

int BST::countNodes(BSTNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int BST::countNodes() {
    return countNodes(root);
}

int BST::height(BSTNode* node) {
    if (!node) return 0;
    int l = height(node->left);
    int r = height(node->right);
    return 1 + max(l, r);
}

int BST::height() {
    return height(root);
}

int BST::countLeaves(BSTNode* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}

int BST::countLeaves() {
    return countLeaves(root);
}

void BST::printTable() {
    cout << "=============================================================\n";
    cout << "                       DATA MAHASISWA (BST)                  \n";
    cout << "=============================================================\n";
    cout << left << setw(15) << "NIM"
         << setw(25) << "Nama"
         << setw(20) << "Prodi" << endl;
    cout << "-------------------------------------------------------------\n";

    function<void(BSTNode*)> in = [&](BSTNode* node) {
        if (!node) return;
        in(node->left);

        cout << left << setw(15) << node->data.nim
             << setw(25) << node->data.nama
             << setw(20) << node->data.prodi << endl;

        in(node->right);
    };

    in(root);

    cout << "=============================================================\n";
}

void BST::exportToTxt(string filename) {
    ofstream file(filename);
    if (!file) return;

    // export inorder
    file << "Export data BST:\n";

    // Lambda inorder
    function<void(BSTNode*)> in = [&](BSTNode* node) {
        if (!node) return;
        in(node->left);
        file << node->data.nim << " - " << node->data.nama << " - " << node->data.prodi << "\n";
        in(node->right);
    };

    in(root);
    file.close();
}
