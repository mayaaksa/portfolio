#include "avl.h"
#include <fstream>
#include <functional>
#include <iomanip>

AVL::AVL() { root = NULL; }

int AVL::getHeight(AVLNode* n) {
    return n ? n->height : 0;
}

int AVL::getBalance(AVLNode* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

AVLNode* AVL::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* AVL::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* AVL::insert(AVLNode* node, Mahasiswa m) {
    if (!node) return new AVLNode(m);

    if (m.nim < node->data.nim)
        node->left = insert(node->left, m);
    else if (m.nim > node->data.nim)
        node->right = insert(node->right, m);
    else {
        node->data = m;
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && m.nim < node->left->data.nim)
        return rightRotate(node);

    if (balance < -1 && m.nim > node->right->data.nim)
        return leftRotate(node);

    if (balance > 1 && m.nim > node->left->data.nim) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && m.nim < node->right->data.nim) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVL::insert(Mahasiswa m) {
    root = insert(root, m);
}

AVLNode* AVL::search(AVLNode* node, string nim) {
    if (!node) return NULL;
    if (nim == node->data.nim) return node;
    if (nim < node->data.nim) return search(node->left, nim);
    return search(node->right, nim);
}

Mahasiswa* AVL::search(string nim) {
    AVLNode* res = search(root, nim);
    return res ? &res->data : NULL;
}


// ==================== TABEL OUTPUT ====================

void AVL::inorder(AVLNode* node) {
    if (!node) return;
    inorder(node->left);

    cout << "| "
         << setw(10) << left << node->data.nim << " | "
         << setw(10) << left << node->data.nama << " | "
         << setw(12) << left << node->data.prodi << " |\n";

    inorder(node->right);
}

void AVL::inorder() {
    cout << "+------------+------------+--------------+\n";
    cout << "| NIM        | Nama       | Prodi        |\n";
    cout << "+------------+------------+--------------+\n";

    inorder(root);

    cout << "+------------+------------+--------------+\n";
}

// ======================================================


AVLNode* AVL::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVLNode* AVL::remove(AVLNode* node, string nim) {
    if (!node) return node;

    if (nim < node->data.nim)
        node->left = remove(node->left, nim);
    else if (nim > node->data.nim)
        node->right = remove(node->right, nim);
    else {
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = NULL;
            } else
                *node = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data.nim);
        }
    }

    if (!node) return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVL::remove(string nim) {
    root = remove(root, nim);
}

void AVL::clear(AVLNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void AVL::clear() {
    clear(root);
    root = NULL;
}

int AVL::countNodes(AVLNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int AVL::countNodes() {
    return countNodes(root);
}

int AVL::heightTree(AVLNode* node) {
    if (!node) return 0;
    return 1 + max(heightTree(node->left), heightTree(node->right));
}

int AVL::height() {
    return heightTree(root);
}

int AVL::countLeaves(AVLNode* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}

int AVL::countLeaves() {
    return countLeaves(root);
}

void AVL::printTable() {
    cout << "=============================================================\n";
    cout << "| NIM        | Nama                     | Prodi             |\n";
    cout << "=============================================================\n";

    function<void(AVLNode*)> in = [&](AVLNode* node) {
        if (!node) return;

        in(node->left);

        cout << "| " << node->data.nim
             << string(12 - node->data.nim.length(), ' ')
             << "| " << node->data.nama
             << string(25 - node->data.nama.length(), ' ')
             << "| " << node->data.prodi
             << string(18 - node->data.prodi.length(), ' ')
             << "|\n";

        in(node->right);
    };

    in(root);

    cout << "=============================================================\n";
}

void AVL::exportToTxt(string filename) {
    ofstream file(filename);
    if (!file) return;

    file << "Export data AVL:\n";

    function<void(AVLNode*)> in = [&](AVLNode* node) {
        if (!node) return;
        in(node->left);
        file << node->data.nim << " - " << node->data.nama << " - " << node->data.prodi << "\n";
        in(node->right);
    };

    in(root);
    file.close();
}
