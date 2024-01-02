#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <numeric>
#include <ctime>

using namespace std;

double funkcja(double x) {
    return 4.0 / (1.0 + x * x);
}

double liczPiCzesc(long long poczatek, long long koniec, double szerokosc) {
    double suma = 0.0;

    for (long long i = poczatek; i < koniec; ++i) {
        double x = (i + 0.5) * szerokosc;
        suma += funkcja(x);
    }

    return suma * szerokosc;
}

double liczPiZrownoleglone(long long n, int liczbaWatkow) {
    double a = 0.0;
    double b = 1.0;
    double szerokosc = (b - a) / n;

    long long punktyNaWatek = n / liczbaWatkow;

    vector<thread> watki;
    double wyniki[liczbaWatkow];

    auto start = clock();

    for (int i = 0; i < liczbaWatkow; ++i) {
        long long poczatek = i * punktyNaWatek;
        long long koniec = (i + 1 == liczbaWatkow) ? n : (i + 1) * punktyNaWatek;

        watki.emplace_back([poczatek, koniec, szerokosc, &wyniki, i]() {
            wyniki[i] = liczPiCzesc(poczatek, koniec, szerokosc);
        });
    }

    for (auto &watek : watki) {
        watek.join();
    }

    double wynik = accumulate(wyniki, wyniki + liczbaWatkow, 0.0);

    auto stop = clock();
    double czas = static_cast<double>(stop - start) / CLOCKS_PER_SEC;

    cout << "Czas: " << czas * 1000 << " ms" << endl;

    return wynik;
}

int main() {
    long long liczbaPodzialow;
    int liczbaWatku;

    cout << "Podaj liczbe podzialow: ";
    cin >> liczbaPodzialow;

    cout << "Podaj liczbe watkow: ";
    cin >> liczbaWatku;

    double wynik = liczPiZrownoleglone(liczbaPodzialow, liczbaWatku);

    cout << "Przyblizona wartosc liczby PI: " << wynik << endl;

    return 0;
}
