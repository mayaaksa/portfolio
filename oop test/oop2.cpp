#include <iostream>
#include <cmath>
using namespace std;

const float PI = 3.14;

class Bangun {
public:
    virtual float hitungLuas() = 0;
};

// 2  Dimensi

class Persegi : public Bangun {
    float s;
public:
    Persegi(float s) : s(s) {}
    float hitungLuas() {
        return s * s;
    }
};

class PersegiPanjang : public Bangun {
    float p, l;
public:
    PersegiPanjang(float p, float l) : p(p), l(l) {}
    float hitungLuas() {
        return p * l;
    }
};

class Lingkaran : public Bangun {
    float r;
public:
    Lingkaran(float r) : r(r) {}
    float hitungLuas() {
        return PI * r * r;
    }
};

// 3 Dimensi (Penampang)

class Kubus : public Bangun {
    float s;
public:
    Kubus(float s) : s(s) {}
    float hitungLuas() {
        return s * s;
    }
};

class Balok : public Bangun {
    float p, l;
public:
    Balok(float p, float l) : p(p), l(l) {}
    float hitungLuas() {
        return p * l;
    }
};

class Tabung : public Bangun {
    float r;
public:
    Tabung(float r) : r(r) {}
    float hitungLuas() {
        return PI * r * r;
    }
};

int main() {

    int menu, pilih;

    do {
        cout << "\n=== Program Hitung Luas ===\n";
        cout << "1. Luas 2 Dimensi\n";
        cout << "2. Luas 3 Dimensi\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> menu;

        Bangun* bangun = nullptr;

        if(menu == 1) {
            int menu2d;
            cout << "\n-- Bangun 2D --\n";
            cout << "1. Persegi\n";
            cout << "2. Persegi Panjang\n";
            cout << "3. Lingkaran\n";
            cout << "Pilih: ";
            cin >> menu2d;

            switch(menu2d) {
                case 1: {
                    float s;
                    cout << "Masukkan sisi: ";
                    cin >> s;
                    bangun = new Persegi(s);
                    break;
                }
                case 2: {
                    float p,l;
                    cout << "Masukkan panjang: ";
                    cin >> p;
                    cout << "Masukkan lebar: ";
                    cin >> l;
                    bangun = new PersegiPanjang(p,l);
                    break;
                }
                case 3: {
                    float r;
                    cout << "Masukkan jari-jari: ";
                    cin >> r;
                    bangun = new Lingkaran(r);
                    break;
                }
                default:
                    cout << "Pilihan tidak valid!\n";
                    continue;
            }

            cout << "Luas = " << bangun->hitungLuas() << " cm^2\n";
        }

        else if(menu == 2) {
            int menu3d;
            cout << "\n 3 Dimensi (Penampang)\n";
            cout << "1. Kubus\n";
            cout << "2. Balok\n";
            cout << "3. Tabung\n";
            cout << "Pilih: ";
            cin >> menu3d;

            switch(menu3d) {
                case 1: {
                    float s;
                    cout << "Masukkan sisi: ";
                    cin >> s;
                    bangun = new Kubus(s);
                    break;
                }
                case 2: {
                    float p,l;
                    cout << "Masukkan panjang: ";
                    cin >> p;
                    cout << "Masukkan lebar: ";
                    cin >> l;
                    bangun = new Balok(p,l);
                    break;
                }
                case 3: {
                    float r;
                    cout << "Masukkan jari-jari: ";
                    cin >> r;
                    bangun = new Tabung(r);
                    break;
                }

                default:
                    cout << "Pilihan tidak valid!\n";
                    continue;
            }

            cout << "Luas Penampang = " << bangun->hitungLuas() << " cm^2\n";
        }

        
        else if (menu == 0) {
        cout << "Terima kasih!" << endl;
        }

        else {
            cout << "Pilihan tidak valid!\n";
            continue;
        }

    } while(menu != 0);

    cout << "\nProgram selesai.\n";
    return 0;
}
