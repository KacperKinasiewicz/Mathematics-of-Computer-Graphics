// main.cpp - Program testowy dla klasy Kwaternion

#include "Kwaternion.h"
#include <iostream>
#include <iomanip>

void separator() {
    std::cout << "\n" << std::string(70, '=') << "\n\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(4);

    // ========================================================================
    // ZADANIE 2: Sprawdzenie czy operacje działają prawidłowo
    // ========================================================================

    std::cout << "ZADANIE 2: SPRAWDZENIE OPERACJI NA KWATERNIONACH\n";
    separator();

    std::cout << "DODAWANIE\n";
    Kwaternion q1(1, 2, 3, 4);
    Kwaternion q2(5, 6, 7, 8);
    std::cout << "q1 = "; q1.wypisz();
    std::cout << "q2 = "; q2.wypisz();
    Kwaternion suma = q1 + q2;
    std::cout << "q1 + q2 = "; suma.wypisz();
    std::cout << "Oczekiwany wynik: (6 + 8i + 10j + 12k)\n";
    separator();

    std::cout << "ODEJMOWANIE\n";
    std::cout << "q1 = "; q1.wypisz();
    std::cout << "q2 = "; q2.wypisz();
    Kwaternion roznica = q1 - q2;
    std::cout << "q1 - q2 = "; roznica.wypisz();
    std::cout << "Oczekiwany wynik: (-4 + -4i + -4j + -4k)\n";
    separator();

    std::cout << "MNOZENIE\n";
    Kwaternion q3(2, 1, 3, 0);
    Kwaternion q4(1, 2, 0, 1);
    std::cout << "q3 = "; q3.wypisz();
    std::cout << "q4 = "; q4.wypisz();
    Kwaternion iloczyn = q3 * q4;
    std::cout << "q3 * q4 = "; iloczyn.wypisz();
    std::cout << "Oczekiwany wynik: (0 + 8i + 2j + -4k)\n";

    std::cout << "\nTest i * i = -1:\n";
    Kwaternion i(0, 1, 0, 0);
    Kwaternion i_kwadrat = i * i;
    std::cout << "i * i = "; i_kwadrat.wypisz();
    std::cout << "Oczekiwany wynik: (-1 + 0i + 0j + 0k)\n";
    separator();

    std::cout << "DZIELENIE\n";
    Kwaternion q5(2, 4, 6, 8);
    Kwaternion q6(1, 0, 0, 0);
    std::cout << "q5 = "; q5.wypisz();
    std::cout << "q6 = "; q6.wypisz();
    Kwaternion iloraz = q5 / q6;
    std::cout << "q5 / q6 = "; iloraz.wypisz();
    std::cout << "Oczekiwany wynik: (2 + 4i + 6j + 8k)\n";

    std::cout << "\nTest q / q = 1:\n";
    Kwaternion q7(3, 2, 1, 4);
    std::cout << "q7 = "; q7.wypisz();
    Kwaternion jedynka = q7 / q7;
    std::cout << "q7 / q7 = "; jedynka.wypisz();
    std::cout << "Oczekiwany wynik: (1 + 0i + 0j + 0k)\n";
    separator();

    std::cout << "SPRZEZENIE\n";
    Kwaternion q8(1, 2, 3, 4);
    std::cout << "q8 = "; q8.wypisz();
    Kwaternion q8_spr = q8.sprzez();
    std::cout << "q8* = "; q8_spr.wypisz();
    std::cout << "Oczekiwany wynik: (1 + -2i + -3j + -4k)\n";
    separator();

    std::cout << "DŁUGOŚĆ\n";
    Kwaternion q9(1, 2, 2, 0);
    std::cout << "q9 = "; q9.wypisz();
    double norma_q9 = q9.dlugosc();
    std::cout << "||q9|| = " << norma_q9 << std::endl;
    std::cout << "Oczekiwany wynik: 3 (sqrt(1 + 4 + 4 + 0) = sqrt(9) = 3)\n";
    separator();

    std::cout << "NORMALIZACJA\n";
    Kwaternion q10(3, 0, 4, 0);
    std::cout << "q10 przed normalizacja: "; q10.wypisz();
    std::cout << "||q10|| = " << q10.dlugosc() << std::endl;
    q10.normalizuj();
    std::cout << "q10 po normalizacji: "; q10.wypisz();
    std::cout << "||q10|| = " << q10.dlugosc() << std::endl;
    std::cout << "Oczekiwany wynik: długość = 1\n";
    separator();

    // ========================================================================
    // ZADANIE 3: Obrót punktu [-1,-1,-1] o 270° wokół osi X
    // ========================================================================

    std::cout << "ZADANIE 3: OBROT PUNKTU [-1,-1,-1] O 270 STOPNI WOKOL OSI X\n";
    separator();

    double px = -1.0, py = -1.0, pz = -1.0;
    std::cout << "Punkt poczatkowy: P = [" << px << ", " << py << ", " << pz << "]\n";
    std::cout << "Kat obrotu: 270 stopni\n";
    std::cout << "Os obrotu: X (wektor [1, 0, 0])\n\n";

    // Tworzymy kwaternion rotacji
    Kwaternion qRot = kwaternionRotacji(270, 1, 0, 0);
    std::cout << "Kwaternion rotacji: "; qRot.wypisz();
    std::cout << "Długość kwaternionu: " << qRot.dlugosc() << "\n\n";

    // Wykonujemy obrót
    qRot.obrocPunkt(px, py, pz);

    std::cout << "Punkt po obrocie: P' = [" << px << ", " << py << ", " << pz << "]\n";
    separator();

    // ========================================================================
    // ZADANIE 4: Brak przemienności mnożenia kwaternionów
    // ========================================================================

    std::cout << "ZADANIE 4: DOWOD BRAKU PRZEMIENNOSCI MNOZENIA KWATERNIONOW\n";
    separator();


    std::cout << "q1 = "; q1.wypisz();
    std::cout << "q2 = "; q2.wypisz();

    Kwaternion q1_razy_q2 = q1 * q2;
    Kwaternion q2_razy_q1 = q2 * q1;

    std::cout << "\nq1 * q2 = "; q1_razy_q2.wypisz();
    std::cout << "q2 * q1 = "; q2_razy_q1.wypisz();
    separator();



    return 0;
}
