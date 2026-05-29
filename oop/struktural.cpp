#include <iostream>
#include <cmath>
using namespace std;

const float PI = 3.14;

// 2 Dimensi
float luasPersegi(float s) {
    return s * s;
}

float luasPersegiPanjang(float p, float l) {
    return p * l;
}

float luasLingkaran(float r) {
    return PI * r * r;
}

// 3 Dimensi (Penampang)
float luasKubus(float s) {
    return 6 * s * s;
}

float luasBalok(float p, float l, float t) {
    return 2 * (p + l) * (l + t) * (t + p);
}

float luasTabung(float r, float t) {
    return 2 * PI * r * r + 2 * PI * r * t;
}

int main() {
    int menu;

    do {
        cout << "\n=== Program Hitung Luas ===\n";
        cout << "1. Luas 2 Dimensi\n";
        cout << "2. Luas 3 Dimensi\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> menu;

        if(menu == 1) {
            int menu2d;
            cout << "\n-- Bangun 2 Dimensi --\n";
            cout << "1. Luas Persegi\n";
            cout << "2. Luas Persegi Panjang\n";
            cout << "3. Luas Lingkaran\n";
            cout << "Pilih: ";
            cin >> menu2d;

            float s, p, l, r;

            switch(menu2d) {
                case 1:
                    cout << "Masukkan sisi (cm): ";
                    cin >> s;
                    cout << "Luas = " << luasPersegi(s) << "cm^2\n";
                    break;

                case 2:
                    cout << "Masukkan panjang (cm): ";
                    cin >> p;
                    cout << "Masukkan lebar (cm): ";
                    cin >> l;
                    cout << "Luas = " << luasPersegiPanjang(p,l) << " cm^2\n";
                    break;

                case 3:
                    cout << "Masukkan jari-jari (cm): ";
                    cin >> r;
                    cout << "Luas = " << luasLingkaran(r) << " cm^2\n";
                    break;

                default:
                    cout << "Pilihan tidak valid!\n";
            }
        }

        else if(menu == 2) {
            int menu3d;
            cout << "\n-- Bangun 3 Dimensi --\n";
            cout << "1. Luas Kubus\n";
            cout << "2. Luas Balok\n";
            cout << "3. Luas Tabung\n";
            cout << "Pilih: ";
            cin >> menu3d;

            float s, p, l, r, t;

            switch(menu3d) {
                case 1:
                    cout << "Masukkan sisi (cm): ";
                    cin >> s;
                    cout << "Luas Penampang = " << luasKubus(s) << " cm^2\n";
                    break;

                case 2:
                    cout << "Masukkan panjang (cm): ";
                    cin >> p;
                    cout << "Masukkan lebar (cm): ";
                    cin >> l;
                    cout << "Masukkan tinggi (cm): ";
                    cin >> t;
                    cout << "Luas Penampang = " << luasBalok(p,l,t) << " cm^2\n";
                    break;

                case 3:
                    cout << "Masukkan jari-jari (cm): ";
                    cin >> r;
                    cout << "Masukkan tinggi (cm): ";
                    cin >> t;
                    cout << "Luas Penampang = " << luasTabung(r,t) << " cm^2\n";
                    break;

                default:
                    cout << "Pilihan tidak valid!\n";
            }
        }

        else if(menu == 0) {
            cout << "Terima kasih!\n";
        }

        else {
            cout << "Pilihan tidak valid!\n";
        }

    } while(menu != 0);

    return 0;
}
