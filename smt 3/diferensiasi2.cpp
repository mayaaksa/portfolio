#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//f(x)
double f(double x) {
    return x*x * exp(x);
}

//f'(x)
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

    cout << fixed << setprecision(4);

    // Header 
    cout << "\n"
         << setw(10) << "x"
         << setw(12) << "Forward"
         << setw(12) << "GalF"
         << setw(12) << "Backward"
         << setw(12) << "GalB"
         << setw(12) << "Center"
         << setw(12) << "GalC" << "\n";

    cout << string(98, '-') << "\n";

    for (double x = b; x <= a + 1e-12; x += h) {

        double forward  = (f(x+h) - f(x)) / h;
        double backward = (f(x) - f(x-h)) / h;
        double center  = (f(x+h) - f(x-h)) / (2*h);

        double turunan = f_analytic(x);

        cout << setw(10) << x
             << setw(12) << forward
             << setw(12) << fabs(forward - turunan)
             << setw(12) << backward
             << setw(12) << fabs(backward - turunan)
             << setw(12) << center
             << setw(12) << fabs(center - turunan)
             << "\n";
    }

    return 0;
}

