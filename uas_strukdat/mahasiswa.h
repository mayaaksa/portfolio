#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <string>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    string prodi;

    Mahasiswa() {}
    Mahasiswa(string nim, string nama, string prodi)
        : nim(nim), nama(nama), prodi(prodi) {}
};

#endif
