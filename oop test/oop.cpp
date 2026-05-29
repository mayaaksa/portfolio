#include <iostream>
#include <math.h>
using namespace std;

// 2 Dimensi
double luasPersegi(double s) {
    return s * s;
}

double luasPersegiPanjang(double p, double l) {
    return p * l;
}

double luasLingkaran(double r) {
    return M_PI * r * r;
}

// 3 Dimensi (Penampang)
double luasPenampangKubus(double s) {
    return s * s;
}

double luasPenampangBalok(double p, double l) {
    return p * l;
}

double luasPenampangTabung(double r) {
    return M_PI * r * r;
}

int main() {
    int menu;

    do {
        cout << "\n=== Program Hitung Luas ===\n";
        cout << "1. Luas 2 Dimensi\n";
        cout << "2. Luas 3 Dimensi (Penampang)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> menu;

        if(menu == 1) {
            int menu2d;
            cout << "\nBangun 2 Dimensi\n";
            cout << "1. Luas Persegi\n";
            cout << "2. Luas Persegi Panjang\n";
            cout << "3. Luas Lingkaran\n";
            cout << "Pilih: ";
            cin >> menu2d;

            double s, p, l, r;

            switch(menu2d) {
                case 1:
                    cout << "Masukkan sisi: ";
                    cin >> s;
                    cout << "Luas = " << luasPersegi(s) << "cm^2 ";
                    break;

                case 2:
                    cout << "Masukkan panjang: ";
                    cin >> p;
                    cout << "Masukkan lebar: ";
                    cin >> l;
                    cout << "Luas = " << luasPersegiPanjang(p,l) << " cm^2";
                    break;

                case 3:
                    cout << "Masukkan jari-jari: ";
                    cin >> r;
                    cout << "Luas = " << luasLingkaran(r) << " cm^2";
                    break;

                default:
                    cout << "Pilihan tidak valid!\n";
            }
        }

        else if(menu == 2) {
            int menu3d;
            cout << "\nBangun 3 Dimensi (Penampang)\n";
            cout << "1. Luas Penampang Kubus\n";
            cout << "2. Luas Penampang Balok\n";
            cout << "3. Luas Penampang Tabung\n";
            cout << "Pilih: ";
            cin >> menu3d;

            double s, p, l, r;

            switch(menu3d) {
                case 1:
                    cout << "Masukkan sisi: ";
                    cin >> s;
                    cout << "Luas Penampang = " << luasPenampangKubus(s) << " cm^2";
                    break;

                case 2:
                    cout << "Masukkan panjang: ";
                    cin >> p;
                    cout << "Masukkan lebar: ";
                    cin >> l;
                    cout << "Luas Penampang = " << luasPenampangBalok(p,l) << " cm^2";
                    break;

                case 3:
                    cout << "Masukkan jari-jari: ";
                    cin >> r;
                    cout << "Luas Penampang = " << luasPenampangTabung(r) << " cm^2";
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