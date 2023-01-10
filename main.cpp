#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "winbgi2.h"
using namespace std;
/*Napisz program, który będzie symulował uproszczoną grę w bilard.
Na prostokątnej planszy wylosuj położenia kilku bil.Jedna z nich powinna być w dowolny sposób wyróżniona(ma reprezentować białą bilę).
Użytkownik ma mieć możliwość w dowolny sposób(przez wpisanie składowych z klawiatury lub obsługę myszki) zadania kierunku, w jakim rozpędzi tą bilę.
Będzie to odpowiadać uderzeniu kijem białej bili.
Następnie zasymuluj ruch bili oraz zderzenia miedzy bilami oraz ściankami.
Sprawdzaj, czy któraś z rozpędzonych bil, z odpowiednia dokładnością, trafi w róg stołu(wykrywaj takie zdarzenie – bila powinna wtedy znikać).
Odpowiednie wzory opisujące zderzenia dwóch bil znajdziesz w http://ccfd.github.io/courses/info1_lab05.html.
*/

const int oknoX = 1280, oknoY = 700; //rozmiary okna
const int stolX = oknoX - 40, stolY = oknoY - 40; //rozmiary stołu, oddalone od krawedzi okna o 40
const int dziury = 50; //rozmiar dziur na bile
const double straty = 0.9;
const int framerate = 75;
void rysowaniestolu()
{
    //krawędzie stołu
    setpalette(15, GREEN);
    line(40, 40, stolX, 40);
    line(40, stolY, stolX, stolY);
    line(40, 40, 40, stolY);
    line(stolX, 40, stolX, stolY);
    
    //dziury w stole
    setpalette(15, LIGHTRED);
    line(40, 40 + dziury, stolX, 40 + dziury);
    line(40, stolY - dziury, stolX, stolY - dziury);
    line(40 + dziury, 40, 40 + dziury, stolY);
    line(stolX - dziury, 40, stolX - dziury, stolY);

}
void strzalpilek(double* xV, double* yV)
{
    int kierunek = 0;
    double sila = 0.0;
    outtextxy(oknoX / 2, 10, "PRZEJDZ NA OKNO KONSOLI");
    while (sila > 10 || sila < 1)
    {
        printf("Podaj sile od 1-10\nSila = ");
        scanf("%lf", &sila);
    }
    printf("Wybrana sila: %lf\n", sila);
    while (kierunek > 8 || kierunek < 1)
    {
        printf("Podaj kierunek strzalu \n1 = prawo \n2 = lewo \n3= gora \n4 = dol \n5 = prawo gora\n6 = lewo gora\n7 = prawo dol\n8 = lewo dol\nKierunek = "); 
        scanf_s("%d", &kierunek);
        switch (kierunek)
        {
        case 1:
            xV[0] = 10 * sila;
        case 2:
            xV[0] = -10 * sila;
        case 3:
            yV[0] = 10 * sila;
        case 4:
            yV[0] = -10 * sila;
        case 5:
            xV[0] = 10 * sila;
            yV[0] = -10 * sila;
        case 6:
            xV[0] = -10 * sila;
            yV[0] = -10 * sila;
        case 7:
            xV[0] = -10 * sila;
            yV[0] = 10 * sila;
        case 8:
            xV[0] = -10 * sila;
            yV[0] = 10 * sila;
        default:
            break;
        }
    }
    printf("kierunek nr %d", kierunek);
}
void losowaniepilek(double* x, double* xV, double* y, double* yV, int r, int N)
{
    int odl = r + 30; // odleglosc srodka wylosowanych od krawedzi
    int maX = stolX - odl;
    int miX = 40 + odl;
    int maY = stolY - odl;
    int miY = 40 + odl;
    int Lx = maX - miX + 1;
    int Ly = maY - miY + 1;
    srand(time(NULL)); //losowanie pozycji bil, mieszczących się na boisku http://ccfd.github.io/courses/info1_lab04.html
    for (int i = 0; i < N; i++)
    {
       
        x[i] = rand() % Lx + miX;
        y[i] = rand() % Ly + miY;
        xV[i] = 0; // do testów kolizji dorzucić tutaj na początek coś
        yV[i] = 0;
        for (int j = 0 ; j<i ; j++)
        {
            odl = sqrt(pow(x[i] - x[j], 2)+ pow(y[i] - y[j], 2)); //mierzenie odległości między wylosowanymi kulkami
            if (odl< 2*r)
            {
                i--; //bila będzie jeszcze raz wylosowana, jeśli jej pozycja "nachodzi" na inną bilę
                break; //nie ma co sprawdzać z następnymi, jak tu już się nie zgadza - wracamy "do góry"
            }

        }
    }
}
void ruszpilki(double* x, double* xV, double* y, double* yV, int N)
{
    for (int i = 0; i < N; i++) 
    {
        if (x[i] == -10) continue; //dla wpadniętych kulek
        x[i] += xV[i]*10/framerate;
        y[i] += yV[i]*10 / framerate;
    }
}
void czywpadlo(double* x, double* y, double r, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (x[i] == -10) continue; //dla wpadniętych kulek
        if ((x[i] - 40 < dziury || stolX - x[i] < dziury) && (y[i] - 40 < dziury || stolY - y[i] < dziury)) //jeśli jest w którymś rogu
        {
            x[i] = -10; 
            y[i] = -100; //takie wartości, żeby się nie pokazały nigdzie i nie były potem rysowane
        }
    }
}
void kolizjazesciana(double* x, double* xV, double* y, double* yV,int r, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (x[i] == -10) continue;
        if (x[i] - 40 < r) 
        {
            x[i] = 40.0 + r + 2;
            xV[i] -= 2 * xV[i];
        }
        else if (stolX - x[i] < r)
        {
            x[i] = stolX - r - 2;
            xV[i] -= 2 * xV[i];
        }
        if (y[i] - 40. < r)
        {
            y[i] = 40. + r + 2.;
            yV[i] -= 2 * yV[i];
        }
        else if (stolY - y[i] < r)
        {
            y[i] = stolY - r - 2.;
            yV[i] -= 2 * yV[i];
        }
    }
}
void kolizjezpilkami(double* x, double* cx, double* y, double* cy, int r, int N) //https://www.meil.pw.edu.pl/za/content/download/14569/80547/file/Info1Lab052.pdf
{
    double L = 10000;
    double v1x, v1y, nx,ny,vnx,vny, v1nx, v1ny;
    for (int i = 0; i < N; i++)
    {
        if (x[i] == -10) continue; //nie liczymy wpadniętych kulek
        for (int j = 0; j < i; j++)
        {
            L = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));    //mierzenie odległości między pilkami po kolei
            if (L < 2.0 * r)                                        //jesli ta odleglosc jest mniejsza niz dwa promienie, mamy zderzenie
            {
                v1x = cx[i] - cx[j];
                v1y = cy[i] - cy[j];
                nx = (x[i] - x[j]) / L;
                ny = (y[i] - y[j]) / L;
                x[i] += nx * 2 * r / L;	                            //zmiana miejsca, zeby sie nie wywalalo
                y[i] += ny * 2 * r / L;
                vnx = (v1x * nx + v1y * ny) * nx;
                vny = (v1x * nx + v1y * ny) * ny;
                cx[i] -= vnx;
                cy[i] -= vny;
                cx[j] += vnx;
                cy[j] += vny;
            }
        }
    }
}
void rysowaniepilek(double* x, double* y, int r, int N)
{
    int i = 0;
    setpalette(15, WHITE);
    circle(x[0], y[0],r);
    outtextxy(x[0]-15, y[0], "biala");
    setpalette(15, BLUE);
    for ( i = 1; i < N;i++)
    {
        if (x[i] == -10) continue; //nie wysujemy wpadniętych kulek
        circle(x[i], y[i], r);
        char numer = char(i);
    }
}
int main()
{

    graphics(oknoX, oknoY);
    int N = 16; //liczba bil
    // dynamiczne alokowanie pamięci na wspolrzedne bili (bila "0" to biała)
    double* xp;
    double* yp; 
    double* xVp;
    double* yVp;
    int rp = dziury/4; // promień piłki
    xp = (double*)malloc(N * sizeof(double));   //wspolrzedne bili
    yp = (double*)malloc(N * sizeof(double));   
    xVp = (double*)malloc(N * sizeof(double));  //predkosc bili
    yVp = (double*)malloc(N * sizeof(double));
    losowaniepilek(xp, xVp, yp, yVp, rp, N);
    rysowaniepilek(xp, yp, rp, N);
    strzalpilek(xVp, yVp);
    for (int i = 0; i < 500*framerate; i++) 
    {
        animate(framerate);   // jako argument funkcji wpisujemy ilość klatek na sekundę (oczekiwanie przez 10 ms)
        clear();
        rysowaniestolu();
        ruszpilki(xp,xVp,yp,yVp,N);
        czywpadlo(xp, yp, rp, N);
        kolizjezpilkami(xp, xVp, yp, yVp, rp, N);
        kolizjazesciana(xp, xVp, yp, yVp, rp, N);
        rysowaniepilek(xp, yp, rp, N);
    }

    return 0;
}
