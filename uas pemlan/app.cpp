#include "App.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

Mahasiswa mhs[MAX_DATA];
int jumlah = 0;

/* ================= MENU ================= */
void menu() {
    cout << "\n=== Sistem Registrasi KRS Mahasiswa ===\n";
    cout << "1. Tambah Data\n";
    cout << "2. Tampilkan Data\n";
    cout << "3. Cari Data (Sequential / Binary)\n";
    cout << "4. Urutkan Data (Quick / Merge / Shell)\n";
    cout << "5. Analisis Data (Rekursif)\n";
    cout << "6. Simpan ke File\n";
    cout << "7. Keluar\n";
    cout << "Pilih: ";
}

/* ================= TAMBAH DATA ================= */
void tambahData() {
    cin.ignore();
    cout << "NPM  : ";
    getline(cin, mhs[jumlah].npm);
    cout << "Nama : ";
    getline(cin, mhs[jumlah].nama);
    jumlah++;
}

/* ================= TAMPIL DATA ================= */
void tampilData() {
    cout << "\n+----+------------+----------------------+\n";
    cout << "| No | NPM        | Nama                 |\n";
    cout << "+----+------------+----------------------+\n";

    for (int i = 0; i < jumlah; i++) {
        cout << "| " << setw(2) << i + 1
             << " | " << setw(10) << mhs[i].npm
             << " | " << setw(20) << mhs[i].nama << " |\n";
    }

    cout << "+----+------------+----------------------+\n";
}

/* ================= SEARCH ================= */
int sequentialSearch(string npm) {
    for (int i = 0; i < jumlah; i++) {
        cout << "Bandingkan " << mhs[i].npm << " dengan " << npm << endl;
        if (mhs[i].npm == npm)
            return i;
    }
    return -1;
}

int binarySearch(string npm) {
    int low = 0, high = jumlah - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        cout << "Bandingkan " << mhs[mid].npm << " dengan " << npm << endl;

        if (mhs[mid].npm == npm)
            return mid;
        else if (mhs[mid].npm < npm)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void cariData() {
    int pilih;
    string npm;

    cout << "\n=== Menu Pencarian ===\n";
    cout << "1. Sequential Search\n";
    cout << "2. Binary Search\n";
    cout << "Pilih: ";
    cin >> pilih;

    cin.ignore();
    cout << "Masukkan NPM: ";
    getline(cin, npm);

    int idx = -1;

    if (pilih == 1)
        idx = sequentialSearch(npm);
    else if (pilih == 2)
        idx = binarySearch(npm);
    else {
        cout << "Pilihan tidak valid\n";
        return;
    }

    if (idx != -1)
        cout << "Data ditemukan: " << mhs[idx].npm << " - " << mhs[idx].nama << endl;
    else
        cout << "Data tidak ditemukan\n";
}

/* ================= QUICK SORT ================= */
int partition(int low, int high) {
    string pivot = mhs[high].npm;
    int i = low - 1;

    cout << "Pivot: " << pivot << endl;

    for (int j = low; j < high; j++) {
        cout << "Bandingkan " << mhs[j].npm << " dengan " << pivot << endl;
        if (mhs[j].npm < pivot) {
            i++;
            swap(mhs[i], mhs[j]);
            cout << "Tukar posisi\n";
        }
    }
    swap(mhs[i + 1], mhs[high]);
    cout << "Tukar pivot\n";
    return i + 1;
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

/* ================= MERGE SORT ================= */
void merge(int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Mahasiswa L[50], R[50];

    for (int i = 0; i < n1; i++) L[i] = mhs[l + i];
    for (int j = 0; j < n2; j++) R[j] = mhs[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        cout << "Bandingkan " << L[i].npm << " dengan " << R[j].npm << endl;
        if (L[i].npm <= R[j].npm)
            mhs[k++] = L[i++];
        else
            mhs[k++] = R[j++];
    }

    while (i < n1) mhs[k++] = L[i++];
    while (j < n2) mhs[k++] = R[j++];
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

/* ================= SHELL SORT ================= */
void shellSort() {
    for (int gap = jumlah / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jumlah; i++) {
            Mahasiswa temp = mhs[i];
            int j;
            for (j = i; j >= gap && mhs[j - gap].npm > temp.npm; j -= gap) {
                cout << "Bandingkan " << mhs[j - gap].npm
                     << " dengan " << temp.npm << " → Geser\n";
                mhs[j] = mhs[j - gap];
            }
            mhs[j] = temp;
        }
    }
}

/* ================= SUBMENU SORT ================= */
void urutkanData() {
    int pilih;
    cout << "\n=== Menu Pengurutan ===\n";
    cout << "1. Quick Sort\n";
    cout << "2. Merge Sort\n";
    cout << "3. Shell Sort\n";
    cout << "Pilih: ";
    cin >> pilih;

    if (pilih == 1) quickSort(0, jumlah - 1);
    else if (pilih == 2) mergeSort(0, jumlah - 1);
    else if (pilih == 3) shellSort();
    else {
        cout << "Pilihan tidak valid\n";
        return;
    }

    cout << "Data berhasil diurutkan\n";
}

/* ================= ANALISIS (REKURSIF) ================= */
int hitungHuruf(string s, int idx) {
    if (idx == s.length()) return 0;
    return 1 + hitungHuruf(s, idx + 1);
}

int hitungVokal(string s, int idx) {
    if (idx == s.length()) return 0;
    char c = tolower(s[idx]);
    int vokal = (c=='a'||c=='i'||c=='u'||c=='e'||c=='o');
    return vokal + hitungVokal(s, idx + 1);
}

void analisisData() {
    int huruf = 0, vokal = 0;

    for (int i = 0; i < jumlah; i++) {
        huruf += hitungHuruf(mhs[i].nama, 0);
        vokal += hitungVokal(mhs[i].nama, 0);
    }

    cout << "\n=== Analisis Data ===\n";
    cout << "Jumlah mahasiswa : " << jumlah << endl;
    cout << "Total huruf nama : " << huruf << endl;
    cout << "Total huruf vokal: " << vokal << endl;
}

/* ================= FILE ================= */
void simpanFile() {
    ofstream file("krs.txt");
    for (int i = 0; i < jumlah; i++)
        file << mhs[i].npm << ";" << mhs[i].nama << endl;

    file.close();
    cout << "Data disimpan ke krs.txt\n";
}

/* ================= RUN ================= */
void runApp() {
    int pilih;
    do {
        menu();
        cin >> pilih;
        switch (pilih) {
            case 1: tambahData(); break;
            case 2: tampilData(); break;
            case 3: cariData(); break;
            case 4: urutkanData(); break;
            case 5: analisisData(); break;
            case 6: simpanFile(); break;
            case 7: cout << "Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 7);
}
