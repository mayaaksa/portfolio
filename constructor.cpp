#include <iostream>
using namespace std;

class Employees {
    string id, nama, telp;
public:
    Employees() {
        cout << "running constructor 1" << endl;
        id = "001";
        nama = "Tono";
    }

    Employees(string _nama) {
        cout << "running constructor 2" << endl;
        id = "001";
        nama = _nama;
    }

    string get_nama() {
        return nama;
    }

    void tampilkan() {
        cout << "Nama: " << nama;
    }

    void tampilkan(string _nama) {
        cout << "Nama: " << nama;
    }

    void _nama(string _nama) {
        nama = _nama;
    }
    
    string _nama() {
        return nama;
    }

    bool _telp(string _telp) {
        
    }
};

int main() {
    Employees e;
    cout << e.get_nama() << endl;
    Employees e2("Amir");
    cout << e2.get_nama() << endl;
    return 0;
}
   