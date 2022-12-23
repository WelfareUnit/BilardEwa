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

int oknoX = 1280, oknoY = 700; //rozmiary okna
int stolX = oknoX - 40, stolY = oknoY - 40; //rozmiary stołu, oddalone od krawedzi okna o 40

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
    line(40, 70, stolX, 70);
    line(40, stolY-30, stolX, stolY-30);
    line(70, 40, 70, stolY);
    line(stolX - 30, 40, stolX - 30, stolY);

}

void losowaniepilek(double* x, double* y,double r,int N)
{
    int odl = r + 30; // odleglosc srodka wylosowanych od krawedzi
    int maX = stolX - odl;
    int miX = 40 + odl;
    int maY = stolY - odl;
    int miY = 40 + odl;
    int Lx = maX - miX + 1;
    int Ly = maY - miY + 1;
    double odlx, odly;
    srand(time(NULL)); //losowanie pozycji bil, mieszczących się na boisku http://ccfd.github.io/courses/info1_lab04.html
    for (int i = 0; i < N; i++)
    {
       
        x[i] = rand() % Lx + miX;
        y[i] = rand() % Ly + miY;
        for (int j = 0 ; j<i ; j++)
        {
            
            odlx = (x[i] - x[j]);
            odly = (y[i] - y[j]);
            printf("Sprawdzana bila %d z  %d, x1 =%.2f, x2 = %.2f, y1 = %f, y2 = %.2f, odleglosc = %.2f, %.2f \n", i, j, x[i], x[j], y[i], y[j],odlx,odly);

            if (fabs(odlx) < 2*r & fabs(odly) < 2*r)
            {
                i--; //bila będzie jeszcze raz wylosowana, jeśli jej pozycja "nachodzi" na inną bilę
                break;
               
            }

        }
    }
}

void rysowaniepilek(double* x, double* y, double r, int N)
{
    int i = 0;
    setpalette(15, WHITE);
    circle(x[0], y[0],r);
    outtextxy(x[0]-15, y[0], "biala");
    setpalette(15, BLUE);
    for ( i = 1; i < N;i++)
    {
        circle(x[i], y[i], r);
        char numer = char(i);
        outtextxy(x[i] - 15, y[i],"bila");
    }
}
int main()
{

    graphics(oknoX, oknoY);
    int N = 5; //liczba bil
    // dynamiczne alokowanie pamięci na wspolrzedne bili (bila "0" to biała)
    double* xp;
    double* yp; 
    double* xVp;
    double* yVp;
    int rp = 50; // promień piłki
    xp = (double*)malloc(N * sizeof(double));   //wspolrzedne bili
    yp = (double*)malloc(N * sizeof(double));   
    xVp = (double*)malloc(N * sizeof(double));  //predkosc bili
    yVp = (double*)malloc(N * sizeof(double));

    for (int i = 0; i < 500; i++) 
    {
        animate(1);   // jako argument funkcji wpisujemy ilość klatek na sekundę (oczekiwanie przez 10 ms)
        clear();
        losowaniepilek(xp, yp, rp, N);
        rysowaniepilek(xp, yp, rp, N);
        rysowaniestolu();
    }


    return 0;
}
