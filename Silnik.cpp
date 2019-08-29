

#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include "Silnik.h"
/* predefiniowanie zmiennych x1,i*/
#define CC (x1==n && i==21) || (x1==n && i==22) || (x1==n && i==23) || (x1==n+1 && i==21) || (x1==n+1 && i==22) || (x1==n+1 && i==23) || (x1==n+2 && i==21) || (x1==n+2 && i==22) || (x1==n+2 && i==23) || (x1==n+3 && i==21) || (x1==n+3 && i==22) || (x1==n+3 && i==23) || (x1==n+4 && i==21) || (x1==n+4 && i==22) || (x1==n+4 && i==23)


using namespace std;

/* Uustawianie polozenia elementow*/
COORD coord={0,0};
 void Silnik::polozenie(int x,int y)
 {
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

Silnik::Silnik()
{
    srand(time(0));
    bonus = '$'; //znak bonusa
    n=27;
    punkty=0;
    n1=0;
    czekaj=150; //poczotkowe opoznienie
}

    /* budowanie krawedzi drogi*/
 void Silnik::kraweznik()
 {
     for(int j=1;j<=3;j+=2)
     for(int i=0;i<=24;i++)
     {
         polozenie(16*j,i);
         cout << char (178);
     }
 }

void Silnik::samojazd(int r)
 {
/* drukowanie na ekran bolidu RK*/
    n=n+r;
    polozenie(n,22);
    cout << "O   O";
    polozenie(n,23);
    cout << "| RK |";
    polozenie(n,24);
    cout << "O   O";
 }

void Silnik::czysc()
 {
 /* czyszczenie cienia samochodu*/
    polozenie(n,22);
    cout << "     ";
    polozenie(n,23);
    cout << "     ";
    polozenie(n,24);
    cout << "     ";
 }

void Silnik::przeszkoda(int r, int x2)
{
/* drukowanie na ekran przeszkod/innych_samochodow */
    polozenie(x2,r);
    cout << char(219) << "  " << char(219) ;
    polozenie(x2,1+r);
    cout << char(219) << char(219) << char(219) << char(219) ;
    polozenie(x2,2+r);
    cout << char(219) << "  " << char(219) ;
}

void Silnik::czysc_przeszkoda(int r, int x2)
{
 /* uwusanie cienia przeszkod*/
    polozenie(x2,r);
    cout << "    ";
    polozenie(x2,r+1);
    cout << "    ";
    polozenie(x2,r+2);
    cout << "    ";
}


/*sterowanie bolidek RK*/
void Silnik::ruch(char wcisniety)
{
/*jezeli wciskamy a przesuwa sie w lewo jesli d to w prawo*/
    switch(wcisniety)
    {
        case 'A':
        case 'a':
            wlewo();
            break;
        case 'D':
        case 'd':
            wprawo();
            break;
    }
}

void Silnik::wlewo()
{
        if(n<=17);
        else
        {   czysc();  samojazd(-2);    }
}

void Silnik::wprawo()
{
        if(n>=42);
        else
        {   czysc();  samojazd(+2);    }
}

/*glowna petla programu */
char Silnik::glowna_petla()
{
    for(;;)
    {
        int x1 = rand() % 30 + 17;
        int x2 = rand() % 28 + 17;
        if(x1==x2)
            x1 = rand() % 31 + 17;

    /* pojawianie sie przeszkod dodawnie punktow wpadanie na przeszkode*/
        for(int i=0;i<=23;i++)
        {
            polozenie(x1,i);
            cout << ' ';
            polozenie(x1,i+1);
            cout << bonus;
            if(i==23)
            {
                polozenie(x1,24);
                cout << ' ';
            }
            /* koniec gry gdy wpadnie na przeszkode*/
            przeszkoda(i, x2);
            Sleep(czekaj);
            for(int k=-3;k<=4;k++)
            for(int j=0;j<=3;j++)
            if((x2==n+k && i+2==21+j) || (x2==n+k && i+2==22+j) || (x2==n+k && i+2==23+j))
            {
                wcisniety=koniec_gry();
                return wcisniety;
            }
            czysc_przeszkoda(i, x2);
			if(CC)
            {
                samojazd(0);
                punkty=punkty+50;// plus 50 punktów za zlapani bonusa
                break;
            }
            punkty++;
            pokaz_punkty();
            /*sprawdza bufor wcisnietego klawisza */
            if(kbhit())
            {
                wcisniety=getch();
                if(wcisniety=='a' || wcisniety == 'A' || wcisniety=='D' || wcisniety=='d')
                {   ruch(wcisniety);  }
                else if(wcisniety=='Q' || wcisniety=='q')
                {   return wcisniety;    }
                else
                {   continue;   }
            }

            /*przyspieszanie*/
            if(punkty%100==0)
            {
                if(czekaj>25)
                czekaj-=25;
                else if(czekaj>15 && czekaj<25)
                    czekaj-=3;
				//odejmowanie	x = x - y;	x -= y;
            }
        }
    }
}
/* drukuje punkty z boku planszy*/
void Silnik::pokaz_punkty()
{
    polozenie(50, 15);
    cout << "punkty = "<< punkty;
}


/* koniec gry czy chcesz grac dalej menu*/
char Silnik::koniec_gry()
{
    polozenie(26,12);
    cout << "KONIEC GRY";
    polozenie(23,13);
    cout << "Zdoby³eœ : " << punkty<<" punktów";
    polozenie(19,15);
    cout << "Checesz zagraæ jeszcze raz? T/N: ";
    wcisniety=getche();
    if(wcisniety=='t' || wcisniety=='T')
    {
        punkty=0;
        czekaj=175;
        return wcisniety;
    }
    else if(wcisniety=='n' || wcisniety=='N')
    {   return 'q'; }
    else
    {   koniec_gry(); }

}
