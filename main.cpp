#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
int oknoX = 1280, oknoY = 700;
int stolX = oknoX - 40, stolY = oknoY - 40;
void rysowaniestolu()
{
    //krawędzie stołu
    line(40, 40, stolX, 40);
    line(40, stolY, stolX, stolY);
    line(40, 40, 40, stolY);
    line(stolX, 40, stolX, stolY);
    
    //dziury w stole
    setcolor(5);
    circle(80, 80, 40);
    circle(80, stolY - 40, 40);
    circle(stolX - 40, 80, 40);
    circle(stolX - 40, stolY - 40,40);

}

int main()
{

    graphics(oknoX, oknoY);
    rysowaniestolu();
    double xp[10], yp[10];        // wspolrzedne pilek
    double xVp[10], yVp[10];      // skladowe predkosci pilek
    int rp = 35; // promień piłki
    wait();

    return 0;
}
