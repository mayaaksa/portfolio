#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // 1. Buat file data.txt berisi 10 data
    ofstream out("data.txt");
    for (int i = 1; i <= 10; i++) {
        out << "Nama" << i << " NIM00" << i << endl;
    }
    out.close();

    // 2. Baca isi data.txt
    cout << "Isi data.txt:" << endl;
    ifstream in("data.txt");
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();

    // 3. Replace data menjadi data baru
    ofstream out2("update.txt");
    for (int i = 1; i <= 10; i++) {
        out2 << "MahasiswaBaru" << i << " NIM99" << i << endl;
    }
    out2.close();

    // 4. Baca isi update.txt
    cout << "\nIsi update.txt:" << endl;
    ifstream in2("update.txt");
    while (getline(in2, line)) {
        cout << line << endl;
    }
    in2.close();

    return 0;
}