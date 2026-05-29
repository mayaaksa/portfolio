#include <iostream>
#include "kalkulator.h"
using namespace std;

int main() {
    float a, b;
    int menu;

    cout << "Masukkan bilangan pertama: ";
    cin >> a;
    cout << "Masukkan bilangan kedua: ";
    cin >> b;

    cout << "\nMenu:\n";
    cout << "1. Tambah\n2. Kurang\n3. Kali\n4. Bagi\n";
    cout << "Pilih menu: ";
    cin >> menu;

    cout << "Hasil: ";
    switch(menu) {
        case 1: cout << tambah(a, b); break;
        case 2: cout << kurang(a, b); break;
        case 3: cout << kali(a, b); break;
        case 4: 
            if (b == 0) cout << "Error: pembagian nol";
            else cout << bagi(a, b);
            break;
        default:
            cout << "Pilihan tidak valid!";
    }

    cout << endl;
    return 0;
}
