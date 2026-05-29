#ifndef COMPARE_H
#define COMPARE_H

#include "bst.h"
#include "avl.h"
#include <iostream>
using namespace std;

class Compare {
public:
    static void showBSTStats(BST &t) {
        cout << "\n=== Statistik BST ===\n";
        cout << "Jumlah Node : " << t.countNodes() << endl;
        cout << "Tinggi Tree : " << t.height() << endl;
        cout << "Jumlah Daun : " << t.countLeaves() << endl;
    }

    static void showAVLStats(AVL &t) {
        cout << "\n=== Statistik AVL ===\n";
        cout << "Jumlah Node : " << t.countNodes() << endl;
        cout << "Tinggi Tree : " << t.height() << endl;
        cout << "Jumlah Daun : " << t.countLeaves() << endl;
    }
};

#endif
