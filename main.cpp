#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"

/*Napisz program, który będzie symulował uproszczoną grę w bilard.
Na prostokątnej planszy wylosuj położenia kilku bil.Jedna z nich powinna być w dowolny sposób wyróżniona(ma reprezentować białą bilę).
Użytkownik ma mieć możliwość w dowolny sposób(przez wpisanie składowych z klawiatury lub obsługę myszki) zadania kierunku, w jakim rozpędzi tą bilę.
Będzie to odpowiadać uderzeniu kijem białej bili.
Następnie zasymuluj ruch bili oraz zderzenia miedzy bilami oraz ściankami.
Sprawdzaj, czy któraś z rozpędzonych bil, z odpowiednia dokładnością, trafi w róg stołu(wykrywaj takie zdarzenie – bila powinna wtedy znikać).
Odpowiednie wzory opisujące zderzenia dwóch bil znajdziesz w http://ccfd.github.io/courses/info1_lab05.html.
*/

int oknoX = 1280, oknoY = 700; //rozmiary okna
int stolX = oknoX - 40, stolY = oknoY - 40; //rozmiary stołu

void rysowaniestolu()
{
    //krawędzie stołu
    line(40, 40, stolX, 40);
    line(40, stolY, stolX, stolY);
    line(40, 40, 40, stolY);
    line(stolX, 40, stolX, stolY);
    
    //dziury w stole
    setcolor(50);
    line(40, 70, stolX, 70);
    line(40, stolY-30, stolX, stolY-30);
    line(70, 40, 70, stolY);
    line(stolX - 30, 40, stolX - 30, stolY);

}

int main()
{

    graphics(oknoX, oknoY);
    rysowaniestolu();
    double xp[10], yp[10];        // wspolrzedne pilek
    double xVp[10], yVp[10];      // skladowe predkosci pilek
    int rp = 35; // promień piłki
    getch();

    return 0;
}
