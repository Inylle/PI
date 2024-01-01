#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

double funkcja(double x) {
    return 4.0 / (1.0 + x * x);
}

double liczPiCzesc(int poczatek, int koniec, double szerokosc) {
    double suma = 0.0;
    
    for (int i = poczatek; i < koniec; ++i) {
        double x = (i + 0.5) * szerokosc;
        suma += funkcja(x);
    }

    return suma * szerokosc;
}

double liczPiZrownoleglone(int n, int liczbaWatkow) {
    double a = 0.0;
    double b = 1.0;
    double szerokosc = (b - a) / n;
    
    int punktyNaWatek = n / liczbaWatkow;
    
    vector<thread> watki;
    vector<double> wyniki(liczbaWatkow, 0.0);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < liczbaWatkow; ++i) {
        int poczatek = i * punktyNaWatek;
        int koniec = (i + 1 == liczbaWatkow) ? n : (i + 1) * punktyNaWatek;

        watki.emplace_back(liczPiCzesc, poczatek, koniec, szerokosc);
    }

    for (auto &watek : watki) {
        watek.join();
    }

    double wynik = 0.0;
    for (int i = 0; i < liczbaWatkow; ++i) {
        wynik += wyniki[i];
    }

    auto stop = chrono::high_resolution_clock::now();
    auto czas = chrono::duration_cast<chrono::milliseconds>(stop - start);

    cout << "Czas: " << czas.count() << " ms" << endl;

    return wynik;
}

int main() {
    int liczbaPodzialow;
    int liczbaWatku;

    cout << "Podaj liczbę podziałów: ";
    cin >> liczbaPodzialow;

    cout << "Podaj liczbę wątków: ";
    cin >> liczbaWatku;

    double wynik = liczPiZrownoleglone(liczbaPodzialow, liczbaWatku);

    cout << "Przybliżona wartość liczby PI: " << wynik << endl;

    return 0;
}
