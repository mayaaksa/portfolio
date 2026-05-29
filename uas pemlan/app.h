#ifndef APP_H
#define APP_H

#include <string>
using namespace std;

const int MAX_DATA = 100;

struct Mahasiswa {
    string npm;
    string nama;
};

// variabel global
extern Mahasiswa mhs[MAX_DATA];
extern int jumlah;

// menu & fitur utama
void runApp();
void menu();
void tambahData();
void tampilData();
void cariData();
void urutkanData();
void analisisData();
void simpanFile();

// searching
int sequentialSearch(string npm);
int binarySearch(string npm);

// sorting
void quickSort(int low, int high);
int partition(int low, int high);

void mergeSort(int l, int r);
void merge(int l, int m, int r);

void shellSort();

// rekursif
int hitungHuruf(string s, int idx);
int hitungVokal(string s, int idx);

#endif
