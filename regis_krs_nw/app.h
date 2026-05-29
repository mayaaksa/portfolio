#ifndef APP_H
#define APP_H

#include <string>
using namespace std;

const int MAX = 100;

struct Mahasiswa {
    string npm;
    string nama;
    string kodeMatkul;
    int sks;
};

extern Mahasiswa data[MAX];
extern int jumlahData;
extern bool sudahTerurut;

void menu();
void tambahData();
void tampilData();
void hapusData();
void cariData();
void urutkanData();
void analisisData();
void dummyData();
void simpanFile();
void bacaFile();

#endif