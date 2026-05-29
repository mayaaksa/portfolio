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
    string namaToko, alamat;

public:
    // Constructor 1
    Toko() {
        cout << "Running constructor Toko 1" << endl;
        namaToko = "Toko Maju Jaya";
        alamat = "Ngagel";
    }

    // Constructor 2
    Toko(string _nama, string _alamat) {
        cout << "Running constructor Toko 2" << endl;
        namaToko = _nama;
        alamat = _alamat;
    }

    void tampilkan() {
        cout << "\nInformasi Toko" << endl;
        cout << "Nama Toko : " << namaToko << endl;
        cout << "Alamat    : " << alamat << endl;
    }

    ~Toko() {
        cout << "Destructor Toko dipanggil" << endl;
    }
};

int main() {
    cout << "Sistem Login Admin Toko\n";

    //Constructor 1
    Admin admin1;

    //Constructor 2
    Admin admin2("maya", "999");

    string userInput, passInput;

    cout << "\nLogin\n";
    cout << "Username : ";
    cin >> userInput;
    cout << "Password : ";
    cin >> passInput;

    if (admin1.login(userInput, passInput)) {
        cout << "\nLogin Berhasil sebagai Admin 1!\n";
        Toko toko1;
        toko1.tampilkan();
    }

    else if (admin2.login(userInput, passInput)) {
        cout << "\nLogin Berhasil sebagai Admin 2!\n";
        Toko toko2("Toko Sinar Abadi", "Rungkut");
        toko2.tampilkan();
    }
    else {
        cout << "\nLogin Gagal!\n";
    }

    return 0;
}