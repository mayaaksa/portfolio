#include <iostream>
#include <iomanip> // Diperlukan untuk setprecision
using namespace std;

// Fungsi yang akan diintegralkan
double f(double x) {
    return x*x; // Ganti jika perlu
}

int main() {
    double a, b;
    int n;

    cout << "Masukkan x awal (a): ";
    cin >> a;
    cout << "Masukkan x akhir (b): ";
    cin >> b;
    cout << "Masukkan jumlah pembagian (n): ";
    cin >> n;

    if (n <= 0) {
        cout << "Jumlah pembagian harus > 0!" << endl;
        return 1;
    }

    double h = (b - a) / n;

    // ================== RIEMANN SUM ==================
    double riemann_left = 0, riemann_middle = 0, riemann_right = 0;

    for (int i = 0; i < n; i++) {
        double x_left   = a + i * h;
        double x_middle = a + (i + 0.5) * h;
        double x_right  = a + (i + 1) * h;

        riemann_left   += f(x_left);
        riemann_middle += f(x_middle);
        riemann_right  += f(x_right);
    }

    riemann_left   *= h;
    riemann_middle *= h;
    riemann_right  *= h;

    // ================== TRAPEZOIDAL ==================
    double trapezoid = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        trapezoid += 2 * f(a + i * h);
    }
    trapezoid *= (h / 2);

    // ================== SIMPSON 1/3 ==================
    if (n % 2 != 0) {
        cout << "\nSimpson 1/3 membutuhkan n genap. Secara otomatis n = n+1\n";
        n += 1;
        h = (b - a) / n;
    }

    double simpson = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0)
            simpson += 2 * f(a + i * h);
        else
            simpson += 4 * f(a + i * h);
    }
    simpson *= (h / 3);

    // ================== OUTPUT ==================
    cout << fixed << setprecision(6);

    cout << "\n==================== Riemann Sum ====================\n";
    cout << "Left Riemann   : " << riemann_left << endl;
    cout << "Middle Riemann : " << riemann_middle << endl;
    cout << "Right Riemann  : " << riemann_right << endl;

    cout << "\n==================== Trapezoidal ====================\n";
    cout << "Trapezoid Integral : " << trapezoid << endl;

    cout << "\n==================== Simpson 1/3 ====================\n";
    cout << "Simpson 1/3 Integral : " << simpson << endl;

    return 0;
}
