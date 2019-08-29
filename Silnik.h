#ifndef Silnik_H
#define Silnik_H

/* plik naglowkowy dla klasy silnik*/
class Silnik
{
    private:
        int czekaj;
        int punkty;
        int n, n1;
        char bonus, wcisniety;
    public:
        Silnik();
        void polozenie(int x, int y);
        void kraweznik();
        void samojazd(int r);
        void czysc();
        void ruch(char wcisniety);
        void wlewo();
        void wprawo();
        char glowna_petla();
        void pokaz_punkty();
        void przeszkoda(int r, int x2);
        void czysc_przeszkoda(int r, int x2);
        char koniec_gry();
};

#endif // Silnik_H
