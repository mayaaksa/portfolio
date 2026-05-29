#include <iostream>
#include "Utility.h"
using namespace std;

int findByNPM(string key) {
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].npm == key)
            return i;
    }
    return -1;
}

int sequentialSearch(string key) {
    for (int i = 0; i < jumlahData; i++) {
        cout << "Bandingkan " << key << " dengan " << data[i].npm << endl;
        if (data[i].npm == key) return i;
    }
    return -1;
}

int binarySearch(string key) {
    int l = 0;
    int r = jumlahData - 1;
    int step = 1;

    while (l <= r) {
        int m = (l + r) / 2;

        cout << "\nStep " << step++ << endl;
        cout << "Left index  : " << l << " (" << data[l].npm << ")" << endl;
        cout << "Mid index   : " << m << " (" << data[m].npm << ")" << endl;
        cout << "Right index : " << r << " (" << data[r].npm << ")" << endl;

        cout << "Bandingkan " << key << " dengan " << data[m].npm << endl;

        if (data[m].npm == key) {
            cout << "Data ditemukan pada index " << m << endl;
            return m;
        }
        else if (data[m].npm < key) {
            cout << "Karena " << data[m].npm << " < " << key
                 << ", geser ke kanan\n";
            l = m + 1;
        }
        else {
            cout << "Karena " << data[m].npm << " > " << key
                 << ", geser ke kiri\n";
            r = m - 1;
        }
    }

    cout << "Data tidak ditemukan\n";
    return -1;
}

int partition(int low, int high) {
    string pivot = data[high].npm;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        cout << "Bandingkan " << data[j].npm << " dengan pivot " << pivot << endl;
        if (data[j].npm < pivot) {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void merge(int l, int m, int r) {
    Mahasiswa temp[MAX];
    int i = l, j = m + 1, k = l;

    cout << "\nMerge dari index " << l << " sampai " << r << endl;

    while (i <= m && j <= r) {
        cout << "Bandingkan " << data[i].npm
             << " dengan " << data[j].npm << endl;

        if (data[i].npm < data[j].npm)
            temp[k++] = data[i++];
        else
            temp[k++] = data[j++];
    }

    while (i <= m) temp[k++] = data[i++];
    while (j <= r) temp[k++] = data[j++];

    for (int x = l; x <= r; x++)
        data[x] = temp[x];

    cout << "Hasil sementara: ";
    for (int x = l; x <= r; x++)
        cout << data[x].npm << " ";
    cout << endl;
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void shellSort() {
    for (int gap = jumlahData / 2; gap > 0; gap /= 2) {
        cout << "\nGap = " << gap << endl;

        for (int i = gap; i < jumlahData; i++) {
            Mahasiswa temp = data[i];
            int j = i;

            while (j >= gap && data[j - gap].npm > temp.npm) {
                cout << "Geser " << data[j - gap].npm
                     << " ke posisi " << j << endl;

                data[j] = data[j - gap];
                j -= gap;
            }

            data[j] = temp;

            cout << "Array sementara: ";
            for (int k = 0; k < jumlahData; k++)
                cout << data[k].npm << " ";
            cout << endl;
        }
    }
}

int hitungData(int n) {
    if (n == 0) return 0;
    return 1 + hitungData(n - 1);
}

int hitungHuruf(int i, int j) {
    if (i == jumlahData) return 0;
    if (j == data[i].nama.length()) return hitungHuruf(i + 1, 0);
    return 1 + hitungHuruf(i, j + 1);
}

bool isVokal(char c) {
    c = tolower(c);
    return c=='a'||c=='i'||c=='u'||c=='e'||c=='o';
}

int hitungVokal(int i, int j) {
    if (i == jumlahData) return 0;
    if (j == data[i].nama.length()) return hitungVokal(i + 1, 0);
    return (isVokal(data[i].nama[j]) ? 1 : 0) + hitungVokal(i, j + 1);
}