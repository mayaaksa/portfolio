#include <iostream>
using namespace std;

double f(double x) {
    return x * x;  // f(x) = x^2
}

int main() {
    double a, b;
    int n;

    cout << "Masukkan x awal: ";
    cin >> a;
    cout << "Masukkan x akhir: ";
    cin >> b;
    cout << "Masukkan nilai n: ";
    cin >> n;

    double h = (b - a) / n;

    // Left Riemann
    double leftSum = 0.0;
    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        leftSum += f(x);
    }
    leftSum *= h;

    // Right Riemann
    double rightSum = 0.0;
    for (int i = 1; i <= n; i++) {
        double x = a + i * h;
        rightSum += f(x);
    }
    rightSum *= h;

    // Midpoint Riemann
    double midSum = 0.0;
    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        midSum += f(x);
    }
    midSum *= h;

    // Trapezoida
    double trap = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        trap += 2 * f(x);
    }
    trap *= (h / 2.0);

    // Simpson (hanya jika n genap)
    double simpson = 0.0;
    if (n % 2 == 0) {
        simpson = f(a) + f(b);
        double sumGanjil = 0.0, sumGenap = 0.0;

        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            if (i % 2 == 1) sumGanjil += f(x);
            else sumGenap += f(x);
        }

        simpson += 4 * sumGanjil + 2 * sumGenap;
        simpson *= (h / 3.0);
    }

    // OUTPUT
    cout << "\n=== HASIL PERHITUNGAN ===\n";
    cout << "Left Riemann     : " << leftSum << endl;
    cout << "Right Riemann    : " << rightSum << endl;
    cout << "Midpoint Riemann : " << midSum << endl;

    cout << "\n=== HASIL PERHITUNGAN ===\n";
    cout << "Trapezoida       : " << trap << endl;

    cout << "\n=== HASIL PERHITUNGAN ===\n";
    if (n % 2 == 0)
        cout << "Simpson          : " << simpson << endl;
    else
        cout << "Simpson          : (n harus genap)\n";

    return 0;
}
