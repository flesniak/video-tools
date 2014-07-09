#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define version 8

main()
{
// Welcome
printf("***********************************\n");
printf("*   Willkommen zu ASR-Calc V.%d   *\n", version);
printf("*mit adaptiver Beschnittberechnung*\n");
printf("***********************************\n");

// Variablen-Initialisierung
float xorigf, yorigf, xresf;
int xres, yres, cuto, cutr, cutu, cutl, a, b, sum;

// Original-Auflösung lesen und strecken
printf("Original-Auflösung, encoded at? [XxY@a:b] ");
scanf("%fx%f@%d:%d", &xorigf, &yorigf, &a, &b);
xorigf=yorigf/b*a;
printf("Skalierte Auflösung ist demnach %gx%g.\n", xorigf, yorigf);

// Beschnitt einlesen
printf("Beschnitt [o,r,u,l]? ");
scanf("%d,%d,%d,%d", &cuto, &cutr, &cutu, &cutl);

// Ziel-Auflösungen bestimmen bzw berechnen
printf("Gewünschte x-Auflösung? ");
scanf("%f", &xresf);

// Auflösungen und Beschnitt runden; es müssen nur unten+oben bzw rechts+links %8=0 sein
// Oben + Unten
if(cuto%8!=0 && cutu%8==0)
 cuto=makemodeight(cuto);
if(cuto%8==0 && cutu%8!=0)
 cutu=makemodeight(cutu);
if(cuto%8!=0 && cutu%8!=0)
 for(;;)
  {
  sum=cuto+cutu;
  if((sum%8)==0) break;
  cutu++;
  sum=cuto+cutu;
  if((sum%8)==0) break;
  cuto++;
  }

//Rechts + Links
if(cutr%8!=0 && cutl%8==0)
 cutr=makemodeight(cutr);
if(cutr%8==0 && cutu%8!=0)
 cutl=makemodeight(cutl);
if(cutr%8!=0 && cutl%8!=0)
 for(;;)
  {
  sum=cutr+cutl;
  if((sum%8)==0) break;
  cutr++;
  sum=cutr+cutl;
  if((sum%8)==0) break;
  cutl++;
  }

/* Alte Berechnungsmethode
cuto=makemodeight(cuto);
cutr=makemodeight(cutr);
cutu=makemodeight(cutu);
cutl=makemodeight(cutl); */

xres=rintf((xorigf-cutr-cutl)*xresf/xorigf);
yres=rintf((yorigf-cuto-cutu)*xresf/xorigf);

// Original-Auflösung ausgeben
printf("Genaue gewünschte Auflösung: %dx%d\n", xres, yres);

// Auflösungen durch 8 teilbar machen
xres=makemodeight(xres);
yres=makemodeight(yres);

// Angepasste Auflösung angeben
printf("Gewünschte angepasste Auflösung: %dx%d\n", xres, yres);
printf("Optionen bei transcode: -Z %dx%d,fast -j %d,%d,%d,%d\n", xres, yres, cuto, cutr, cutu, cutl);
}

// Funktion zur Teilbarkeit durch 8
makemodeight(int x)
{
for(;x%8<5 && x>0;x--);
for(;x%8>4 && x>0;x++);
return(x);
}
