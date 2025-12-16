// Kwaterion.h
#ifndef KWATERION_H
#define KWATERION_H

#include <iostream>

class Kwaternion {
public:
    double skalar, x, y, z; // skalar + wektor

    // Konstruktor
    Kwaternion(double skalar = 0, double x = 0, double y = 0, double z = 0);

    // Dodawanie kwaternionów
    Kwaternion operator+(const Kwaternion& q) const;

    // Odejmowanie kwaternionów
    Kwaternion operator-(const Kwaternion& q) const;

    // Mnożenie kwaternionów
    Kwaternion operator*(const Kwaternion& q) const;

    //Dzielenie kwaternionów
    Kwaternion operator/(const Kwaternion& q) const;

    // Sprzężenie kwaternionu
    Kwaternion sprzez() const;

    // Długość kwaternionu
    double dlugosc() const;

    // Normalizacja kwaternionu
    void normalizuj();

    // Obrót punktu (wektor [px, py, pz]) za pomocą kwaternionu
    void obrocPunkt(double& px, double& py, double& pz) const;

    // Wypisywanie kwaternionu
    void wypisz() const;


};

// Funkcja do tworzenia kwaternionu rotacji wokół osi
Kwaternion kwaternionRotacji(double katStopnie, double ax, double ay, double az);

#endif // KWATERION_H