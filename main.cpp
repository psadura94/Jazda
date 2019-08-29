
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Silnik.h"

using namespace std;
int main()
{
    Silnik a1;
    char kbh;
    do
    {
        system("cls");
        a1.kraweznik();
        a1.polozenie(20,21);
        a1.samojazd(0);
        getch();
        kbh=a1.glowna_petla();
    }
    while(kbh!='q');

    a1.polozenie(66,27);
    return 0;
}
