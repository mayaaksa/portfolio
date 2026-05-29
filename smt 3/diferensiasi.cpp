#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Fungsi f(x)
double f(double x) {
    return x*x*x; // Bisa diganti sesuai kebutuhan
}

int main() {
    double a, b, h;
    int pilihan;

    cout << "==== PROGRAM DIFERENSIASI NUMERIK ====\n";
    cout << "Metode:\n";
    cout << "1. Forward Difference\n";
    cout << "2. Backward Difference\n";
    cout << "3. Central Difference\n";
    cout << "Pilih metode (1-3): ";
    cin >> pilihan;

    cout << "Masukkan rentang bawah: ";
    cin >> a;
    cout << "Masukkan rentang atas: ";
    cin >> b;
    cout << "Masukkan langkah h: ";
    cin >> h;

    cout << fixed << setprecision(4);
    cout << "\nDiketahui fungsi f(x) = x^2 + 3x + 2\n";
    cout << "Langkah h = " << h << "\n";

    // Loop melalui semua titik dalam rentang
    for (double x = a; x <= b; x += h) {
        double derivative = 0;
        cout << "\nDicari turunan di x = " << x << "\n";

        if (pilihan == 1) {
            cout << "Metode: Forward Difference\n";
            double f_x = f(x);
            double f_xh = f(x + h);
            derivative = (f_xh - f_x) / h;

            cout << "Maka kita hitung:\n";
            cout << "f(" << x << ") = " << f_x << "\n";
            cout << "f(" << x + h << ") = " << f_xh << "\n";
        }
        else if (pilihan == 2) {
            cout << "Metode: Backward Difference\n";
            double f_x = f(x);
            double f_xh = f(x - h);
            derivative = (f_x - f_xh) / h;

            cout << "Maka kita hitung:\n";
            cout << "f(" << x - h << ") = " << f_xh << "\n";
            cout << "f(" << x << ") = " << f_x << "\n";
        }
        else if (pilihan == 3) {
            cout << "Metode: Central Difference\n";
            double f_x_minus = f(x - h);
            double f_x_plus  = f(x + h);
            derivative = (f_x_plus - f_x_minus) / (2 * h);

            cout << "Maka kita hitung:\n";
            cout << "f(" << x - h << ") = " << f_x_minus << "\n";
            cout << "f(" << x + h << ") = " << f_x_plus << "\n";
        }
        else {
            cout << "Pilihan metode tidak valid!\n";
            break;
        }

        cout << "Maka turunan di x = " << x << " ≈ " << derivative << endl;
    }

    return 0;
}