#include <iostream>
#include <fstream>
#include <iomanip>
#include "App.h"
#include "Utility.h"
using namespace std;

Mahasiswa data[MAX];
int jumlahData = 0;
bool sudahTerurut = false;

void menu() {
    bacaFile();
    int pilih;
    do {
        cout << "\nMENU" << endl;
        cout << "1. Tambah Data" << endl;
        cout << "2. Tampilkan Data" << endl;
        cout << "3. Hapus Data" << endl;
        cout << "4. Cari Data" << endl;
        cout << "5. Urutkan Data" << endl;
        cout << "6. Analisis Data (Rekursif)" << endl;
        cout << "7. Dummy Data" << endl;
        cout << "8. Simpan ke File" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilih: "; cin >> pilih;

        switch (pilih) {
            case 1: tambahData(); break;
            case 2: tampilData(); break;
            case 3: hapusData(); break;
            case 4: cariData(); break;
            case 5: urutkanData(); break;
            case 6: analisisData(); break;
            case 7: dummyData(); break;
            case 8: simpanFile(); break;
        }
    } while (pilih != 9);
}

void tambahData() {
    if (jumlahData >= MAX) {
        cout << "Data sudah penuh!\n";
        return;
    }

    string npm;
    cout << "Masukkan NPM: ";
    cin >> npm;

    if (findByNPM(npm) != -1) {
        cout << "NPM sudah ada!\n";
        return;
    }

    data[jumlahData].npm = npm;
    cin.ignore();
    cout << "Masukkan Nama        : ";
    getline(cin, data[jumlahData].nama);

    cout << "Masukkan Kode Matkul : ";
    cin >> data[jumlahData].kodeMatkul;

    cout << "Masukkan SKS         : ";
    cin >> data[jumlahData].sks;

    jumlahData++;
    sudahTerurut = false;
    cout << "Data berhasil ditambahkan.\n";
}

void tampilData() {
    if (jumlahData == 0) {
        cout << "Data masih kosong.\n";
        return;
    }

    cout << "\n=============================================================\n";
    cout << left
         << setw(5)  << "No"
         << setw(12) << "NPM"
         << setw(20) << "Nama"
         << setw(15) << "Kode MK"
         << setw(5)  << "SKS" << endl;
    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < jumlahData; i++) {
        cout << left
             << setw(5)  << i + 1
             << setw(12) << data[i].npm
             << setw(20) << data[i].nama
             << setw(15) << data[i].kodeMatkul
             << setw(5)  << data[i].sks << endl;
    }

    cout << "=============================================================\n";
}

void hapusData() {
    string npm;
    cout << "Masukkan NPM: ";
    cin >> npm;
    int idx = findByNPM(npm);

    if (idx == -1) {
        cout << "Data dengan NPM " << npm << " tidak ditemukan.\n";
        return;
    }

    for (int i = idx; i < jumlahData - 1; i++)
        data[i] = data[i + 1];
    jumlahData--;
    cout << "Data dengan NPM " << npm << " berhasil dihapus.\n";
}

void cariData() {
    string npm;
    int metode;

    cout << "Cari NPM: ";
    cin >> npm;

    cout << "1. Sequential\n2. Binary\nPilih: ";
    cin >> metode;

    if (metode == 2 && !sudahTerurut) {
        cout << "Data belum terurut! Silakan urutkan data terlebih dahulu.\n";
        return;
    }

    int idx;
    if (metode == 1)
        idx = sequentialSearch(npm);
    else
        idx = binarySearch(npm);

    if (idx != -1)
        cout << "Data ditemukan: " << data[idx].nama << endl;
    else
        cout << "Data tidak ditemukan\n";
}

void urutkanData() {
    if (sudahTerurut) {
        cout << "Data sudah terurut!\n";
        return;
    }

    int pilih;
    cout << "1. Quick\n2. Merge\n3. Shell\nPilih: ";
    cin >> pilih;

    if (pilih == 1)
        quickSort(0, jumlahData - 1);
    else if (pilih == 2)
        mergeSort(0, jumlahData - 1);
    else
        shellSort();

    sudahTerurut = true;
}

void analisisData() {
    cout << "Jumlah Data: " << hitungData(jumlahData) << endl;
    cout << "Jumlah Huruf: " << hitungHuruf(0, 0) << endl;
    cout << "Jumlah Vokal: " << hitungVokal(0, 0) << endl;
}

void dummyData() {
    if (jumlahData + 5 > MAX) {
        cout << "Tidak cukup ruang untuk dummy data.\n";
        return;
    }

    string npm[5]       = {"24081","25052","23093","26074","20045"};
    string nama[5]      = {"Ani","Budi","Cici","Dodi","Eka"};
    string kodeMK[5]    = {"IF101","IF202","IF303","IF404","IF505"};
    int sks[5]          = {3, 4, 3, 2, 3};

    for (int i = 0; i < 5; i++) {
        if (findByNPM(npm[i]) != -1)
            continue;

        data[jumlahData].npm        = npm[i];
        data[jumlahData].nama       = nama[i];
        data[jumlahData].kodeMatkul = kodeMK[i];
        data[jumlahData].sks        = sks[i];
        jumlahData++;
    }

    sudahTerurut = false;
    cout << "Dummy data berhasil ditambahkan.\n";
}

void simpanFile() {
    ofstream file("data.txt");
    for (int i = 0; i < jumlahData; i++)
        file << data[i].npm << "|"
            << data[i].nama << "|"
            << data[i].kodeMatkul << "|"
            << data[i].sks << endl;
    file.close();

    cout << "data.txt berhasil ditambahkan.\n";    
}

void bacaFile() {
    ifstream file("data.txt");
    if (!file.is_open()) return;

    while (getline(file, data[jumlahData].npm, '|')) {
        getline(file, data[jumlahData].nama, '|');
        getline(file, data[jumlahData].kodeMatkul, '|');
        file >> data[jumlahData].sks;
        file.ignore(); // buang newline
        jumlahData++;
    }
    file.close();
}