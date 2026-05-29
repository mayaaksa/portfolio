#include <iostream>
using namespace std;

class Admin {
    string username, password;

public:
    Admin() {
        cout << "Running constructor Admin 1" << endl;
        username = "admin";
        password = "123";
    }

    Admin(string _username, string _password) {
        cout << "Running constructor Admin 2" << endl;
        username = _username;
        password = _password;
    }

    bool login(string _username, string _password) {
        if (_username == username && _password == password) {
            return true;
        }
        return false;
    }

    ~Admin() {
        cout << "Destructor Admin dipanggil" << endl;
    }
};

class Toko {
    string nama, alamat;

public:
    Toko() {
        cout << "Running constructor Toko 1" << endl;
        nama = "Toko Maju Jaya";
        alamat = "Ngagel";
    }

    Toko(string _nama, string _alamat) {
        cout << "Running constructor Toko 2" << endl;
        nama = _nama;
        alamat = _alamat;
    }

    void tampilkan() {
        cout << "Nama Toko : " << nama << endl;
        cout << "   Alamat    : " << alamat << endl;
    }

    string get_nama() {
        return nama;
    }

    ~Toko() {
        cout << "Destructor Toko dipanggil" << endl;
    }
};

int main() {
    char ulang;
    do{

        cout << "=== Sistem Absensi Karyawan Toko ===\n";

        Admin adm1;
        Admin adm2("maya", "221");

        string userInput, passInput;

        cout << "\nLogin\n";
        cout << "Username : ";
        cin >> userInput;
        cout << "Password : ";
        cin >> passInput;

        if (adm1.login(userInput, passInput) || adm2.login(userInput, passInput)) {

            cout << "\nLogin berhasil!\n";

            Toko t1;
            Toko t2("Toko Sinar Abadi", "Rungkut");

            int pilih;

            cout << "\nPilih Cabang Toko\n";
            cout << "1. "; t1.tampilkan();
            cout << "2. "; t2.tampilkan();
            cout << endl;

            cout << "Masukkan pilihan : ";
            cin >> pilih;

            if (pilih == 1) {
                cout << "\nBerhasil melakukan absensi di " << t1.get_nama() << "\n\n";
            }
            else if (pilih == 2) {
                cout << "\nBerhasil melakukan absensi di " << t2.get_nama() << "\n\n";
            }
            else {
                cout << "\nPilihan tidak valid\n";
            }
        }
        
        else {
        cout << "\nLogin gagal!\n";
    }
        cout << "Keluar? (y/t): ";
        cin >> ulang;
        cout << endl;
    }
    
    while (ulang == 't' || ulang == 'T');
    cout << "Program selesai.\n";
    
    return 0;
}