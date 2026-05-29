#include <iostream>
#include <iomanip>
using namespace std;

class Produk {
private:
    string nama;
    double harga;

public:
    Produk(string n, double h) {
        nama = n;
        harga = h;
        cout << "Produk \"" << nama << "\" berhasil dibuat.\n";
    }

    Produk(const Produk &p) {
        nama = p.nama;
        harga = p.harga;
        cout << "Produk \"" << nama << "\" berhasil disalin.\n";
    }

    ~Produk() {
        cout << "Produk \"" << nama << "\" telah dihapus.\n";
    }

    void updateHarga(double h) {
        harga = h;
        cout << "Harga " << nama << " berhasil diubah menjadi: " << harga << endl;
    }

    void updateHarga(double h, double diskon) {
        harga = h - (h * diskon / 100);
        cout << "Harga " << nama << " setelah diskon "
             << diskon << "% menjadi: " << harga << endl;
    }

    void tampilkan() {
        cout << fixed << setprecision(0);
        cout << "------------------------\n";
        cout << "Nama Produk : " << nama << endl;
        cout << "Harga       : " << harga << endl;
        cout << "------------------------\n";
    }
};

int main() {
    string nama;
    double hargaAwal, hargaBaru, diskon;
    char pilihan;

    cout << "\n==== INPUT DATA PRODUK ====\n";
    cout << "Masukkan nama produk  : ";
    getline(cin, nama);

    cout << "Masukkan harga produk : ";
    cin >> hargaAwal;

    Produk p1(nama, hargaAwal);

    cout << "\n==== DATA PRODUK ====\n";
    p1.tampilkan();

    cout << "\nUpdate harga produk: ";
    cin >> hargaBaru;
    p1.updateHarga(hargaBaru);

    cout << "\nApakah Anda ingin menerapkan diskon? [y/n]: ";
    cin >> pilihan;

    if (pilihan == 'y' || pilihan == 'Y') {
        cout << "Masukkan diskon (%): ";
        cin >> diskon;

        p1.updateHarga(hargaBaru, diskon);
    } 
    else if (pilihan == 'n' || pilihan == 'N') {
        cout << "Tidak menggunakan diskon.\n";
    } 
    else {
        cout << "Input tidak valid!\n";
    }

    Produk p2 = p1;

    cout << "\n==== DATA PRODUK ====\n";
    cout << "Produk 1:\n";
    p1.tampilkan();

    cout << "Produk 2 (copy):\n";
    p2.tampilkan();

    return 0;
}