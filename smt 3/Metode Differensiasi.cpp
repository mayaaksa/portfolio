#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// f(x) = x^2 * e^x
double f(double x) {
    return x*x * exp(x);
}

// f'(x) = e^x (2x + x^2)
double f_analytic(double x) {
    return exp(x) * (2*x + x*x);
}

int main() {
    double h, a, b;

    cout << "Masukkan h: ";
    cin >> h;
    cout << "Rentang bawah: ";
    cin >> b;
    cout << "Rentang atas: ";
    cin >> a;

    cout << fixed << setprecision(6);

    // Header 
    cout << "\n"
         << setw(8) << "x"
         << setw(15) << "Forward"
         << setw(15) << "GalF"
         << setw(15) << "Backward"
         << setw(15) << "GalB"
         << setw(15) << "Central"
         << setw(15) << "GalC" << "\n";

    cout << string(98, '-') << "\n";

    for (double x = b; x <= a + 1e-12; x += h) {

        double forward  = (f(x+h) - f(x)) / h;
        double backward = (f(x) - f(x-h)) / h;
        double central  = (f(x+h) - f(x-h)) / (2*h);

        double benar = f_analytic(x);

        cout << setw(8) << x
             << setw(15) << forward
             << setw(15) << fabs(forward - benar)
             << setw(15) << backward
             << setw(15) << fabs(backward - benar)
             << setw(15) << central
             << setw(15) << fabs(central - benar)
             << "\n";
    }

    return 0;
}

