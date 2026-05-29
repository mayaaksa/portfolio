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
        return 6 * s * s;
    }
};

class Balok : public Bangun {
    float p, l, t;
public:
    Balok(float p, float l, float t) : p(p), l(l), t(t) {}
    float hitungLuas() {
        return 2 * (p + l) * (l + t) * (t + p);
    }
};

class Tabung : public Bangun {
    float r, t;
public:
    Tabung(float r, float t) : r(r), t(t) {}
    float hitungLuas() {
        return 2 * PI * r * r + 2 * PI * r * t;
;
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
            cout << "\n-- Luas Bangun 2 Dimensi  --\n";
            cout << "1. Luas Persegi\n";
            cout << "2. Luas Persegi Panjang\n";
            cout << "3. Luas Lingkaran\n";
            cout << "Pilih: ";
            cin >> menu2d;

            switch(menu2d) {
                case 1: {
                    float s;
                    cout << "Masukkan sisi (cm): ";
                    cin >> s;
                    bangun = new Persegi(s);
                    break;
                }
                case 2: {
                    float p,l;
                    cout << "Masukkan panjang (cm): ";
                    cin >> p;
                    cout << "Masukkan lebar (cm): ";
                    cin >> l;
                    bangun = new PersegiPanjang(p,l);
                    break;
                }
                case 3: {
                    float r;
                    cout << "Masukkan jari-jari (cm): ";
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
            cout << "\n-- Luas Bangun 3 Dimensi --\n";
            cout << "1. Luas Kubus\n";
            cout << "2. Luas Balok\n";
            cout << "3. Luas Tabung\n";
            cout << "Pilih: ";
            cin >> menu3d;

            switch(menu3d) {
                case 1: {
                    float s;
                    cout << "Masukkan sisi (cm): ";
                    cin >> s;
                    bangun = new Kubus(s);
                    break;
                }
                case 2: {
                    float p,l,t;
                    cout << "Masukkan panjang (cm): ";
                    cin >> p;
                    cout << "Masukkan lebar (cm): ";
                    cin >> l;
                    cout << "Masukkan tinggi (cm): ";
                    cin >> t;
                    bangun = new Balok(p,l,t);
                    break;
                }
                case 3: {
                    float r,t;
                    cout << "Masukkan jari-jari (cm): ";
                    cin >> r;
                    cout << "Masukkan tinggi (cm): ";
                    cin >> t;
                    bangun = new Tabung(r,t);
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

    return 0;
}
