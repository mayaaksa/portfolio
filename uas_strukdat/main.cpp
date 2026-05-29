#include <iostream>
#include "bst.h"
#include "avl.h"
#include "compare.h"
using namespace std;

void menuBST(BST &tree);
void menuAVL(AVL &tree);

int main() {
    BST bst;
    AVL avl;

    while (true) {
        cout << "\n=== MENU AWAL ===\n";
        cout << "1. Gunakan BST\n";
        cout << "2. Gunakan AVL\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";

        int pil;
        cin >> pil;

        if (pil == 1) menuBST(bst);
        else if (pil == 2) menuAVL(avl);
        else if (pil == 0) break;
        else cout << "Pilihan salah!\n";
    }
}

Mahasiswa inputMhs() {
    string nim, nama, prodi;
    cout << "NIM   : "; cin >> nim;
    cout << "Nama  : "; cin >> nama;
    cout << "Prodi : "; cin >> prodi;
    return Mahasiswa(nim, nama, prodi);
}

void menuBST(BST &tree) {
    while (true) {
        cout << "\n=== MENU BST ===\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Tampilkan\n";
        cout << "4. Hapus\n";
        cout << "5. Statistik\n";
        cout << "6. Export ke TXT\n";
        cout << "7. Clear Tree\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";

        int pil;
        cin >> pil;

        if (pil == 1) {
            tree.insert(inputMhs());
        }
        else if (pil == 2) {
            string nim; 
            cout << "Cari NIM: "; 
            cin >> nim;
            auto m = tree.search(nim);

            tree.printTable();

            if (m) 
                cout << "\nDitemukan: " << m->nim << " " << m->nama << " " << m->prodi << endl;
            else 
                cout << "\nTidak ditemukan!\n";
        }
        else if (pil == 3) {
            tree.printTable();
        }
        else if (pil == 4) {
            string nim; 
            cout << "Hapus NIM: "; 
            cin >> nim;
            tree.remove(nim);
        }
        else if (pil == 5) Compare::showBSTStats(tree);
        else if (pil == 6) {
            tree.exportToTxt("export_bst.txt");
            tree.printTable();
        }
        else if (pil == 7) tree.clear();
        else if (pil == 0) break;
    }
}

void menuAVL(AVL &tree) {
    while (true) {
        cout << "\n=== MENU AVL ===\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Tampilkan\n";
        cout << "4. Hapus\n";
        cout << "5. Statistik\n";
        cout << "6. Export ke TXT\n";
        cout << "7. Clear Tree\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";

        int pil;
        cin >> pil;

        if (pil == 1) {
            tree.insert(inputMhs());
        }
        else if (pil == 2) {
            string nim; 
            cout << "Cari NIM: "; 
            cin >> nim;
            auto m = tree.search(nim);

            tree.printTable();

            if (m) 
                cout << "\nDitemukan: " << m->nim << " " << m->nama << " " << m->prodi << endl;
            else 
                cout << "\nTidak ditemukan!\n";
        }
        else if (pil == 3) {
            tree.printTable();
        }
        else if (pil == 4) {
            string nim; 
            cout << "Hapus NIM: "; 
            cin >> nim;
            tree.remove(nim);
        }
        else if (pil == 5) Compare::showAVLStats(tree);
        else if (pil == 6) {
            tree.exportToTxt("export_avl.txt");
            tree.printTable();
        }
        else if (pil == 7) tree.clear();
        else if (pil == 0) break;
    }
}
