#include <iostream>
#include "konversi_suhu.h"

using namespace std;

int main() {
    double suhu;
    int menu;

    cout << "Masukkan suhu: ";
    cin >> suhu;

    cout << "Pilih konversi:\n";
    cout << "1. Celsius -> Fahrenheit\n";
    cout << "2. Celsius -> Kelvin\n";
    cout << "3. Fahrenheit -> Celsius\n";
    cout << "Pilihan: ";
    cin >> menu;

    switch(menu) {
        case 1:
            cout << celsiusToFahrenheit(suhu);
            break;
        case 2:
            cout << celsiusToKelvin(suhu);
            break;
        case 3:
            cout << fahrenheitToCelsius(suhu);
            break;
        default:
            cout << "Pilihan tidak valid!";
    }

    return 0;
}
