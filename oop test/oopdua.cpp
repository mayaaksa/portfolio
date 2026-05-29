#include <iostream>
using namespace std;

class BangunDatar {
public:
    virtual float luas() = 0; // pure virtual
};

class Persegi : public BangunDatar {
    float sisi;
public:
    Persegi(float s) : sisi(s) {}
    float luas() {
        return sisi * sisi;
    }
};

class PersegiPanjang : public BangunDatar {
    float p, l;
public:
    PersegiPanjang(float p, float l) : p(p), l(l) {}
    float luas() {
        return p * l;
    }
};

class Lingkaran : public BangunDatar {
    float r;
public:
    Lingkaran(float r) : r(r) {}
    float luas() {
        return 3.14 * r * r;
    }
};

int main() {
    int pilih;
    cout << "1. Persegi\n2. Persegi Panjang\n3. Lingkaran\n";
    cout << "Pilih: ";
    cin >> pilih;

    BangunDatar* bangun;  // pointer ke base class

    switch(pilih) {
        case 1: {
            float s;
            cout << "Sisi: ";
            cin >> s;
            bangun = new Persegi(s);
            break;
        }
        case 2: {
            float p,l;
            cout << "Panjang: "; cin >> p;
            cout << "Lebar: "; cin >> l;
            bangun = new PersegiPanjang(p,l);
            break;
        }
        case 3: {
            float r;
            cout << "Jari-jari: ";
            cin >> r;
            bangun = new Lingkaran(r);
            break;
        }
        default:
            cout << "Pilihan salah\n";
            return 0;
    }

    cout << "Luas = " << bangun->luas() << endl;

    delete bangun;
}