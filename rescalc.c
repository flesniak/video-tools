#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "math.h"

main(int argc, char** argv)
{
char appname[256];
strncpy(appname,*argv,255);

float dar = 0, par = 0;
int source_x = 0, source_y = 0, target_x = 0, target_y = 0;
bool script = false;

if( argc < 2 ) {
  fprintf(stderr,"Usage: %s [-script] [-dar <par>] [-sdar <parx>:<pary>] [-par <par>] [-spar <parx>:<pary>] [-scale <target_x>] <source_x>x<source_y>\n",appname);
  exit(1);
  }
int nextvalue = 0;
while( argc > 1 ) {
  argv++;
  char argument[32];
  strncpy(argument,*argv,31);

  switch(nextvalue) {
      case 1 : sscanf(argument,"%f",&dar);
               nextvalue=0;
               break;
      case 2 : {
               int darx, dary;
               sscanf(argument,"%d:%d",&darx,&dary);
               if( dar != 0 )
                 fprintf(stderr,"Both DAR and separated DAR specified. Using %.3f.\n",dar);
               else
                 dar=1.0*darx/dary;
               nextvalue=0;
               break;
               }
      case 3 : sscanf(argument,"%f",&par);
               nextvalue=0;
               break;
      case 4 : {
               int parx, pary;
               sscanf(argument,"%d:%d",&parx,&pary);
               if( par != 0 )
                 fprintf(stderr,"Both PAR and separated PAR specified. Using %.3f.\n",par);
               else
                 par=1.0*parx/pary;
               nextvalue=0;
               break;
               }
      case 5 : sscanf(argument,"%d",&target_x);
               nextvalue=0;
               break;
      default : if( strcmp(argument,"-dar") == 0 )
                  nextvalue=1; else
                if( strcmp(argument,"-sdar") == 0 )
                  nextvalue=2; else
                if( strcmp(argument,"-par") == 0 )
                  nextvalue=3; else
                if( strcmp(argument,"-spar") == 0 )
                  nextvalue=4; else
                if( strcmp(argument,"-scale") == 0 )
                  nextvalue=5; else
                if( strcmp(argument,"-script") == 0 ) {
                  nextvalue=0;
                  script=true;
                  }
                else {
                  sscanf(argument,"%dx%d",&source_x,&source_y);
                  nextvalue=0;
                  }
    }
  argc--;
}

if( (dar == 0) & (par == 0) ) {
  fprintf(stderr,"Neither DAR nor PAR specified, nothing to do!\n");
  exit(1);
}

if( dar != 0 )
  fprintf(stderr,"You specified a DAR. Make sure it's the right one, keep in mind that cropping changes the DAR, but not the PAR. Maybe you would prefer using the PAR.\n");

if( (par != 0) & (dar != 0) )
  fprintf(stderr,"Both PAR and DAR specified, using PAR for calculation!\n");

if( target_x == 0)
  target_x = source_x;
float ftarget_y;
//PAR calculation, default!
if( par != 0 ) {
  ftarget_y=1.0*source_y*target_x/source_x/par;
} else {
//DAR calculation
if( dar != 0 ) {
  ftarget_y=1.0*target_x/dar;
}}
target_y=roundf(ftarget_y);
//Optimization
if( target_y%2 != 0) {
  if( ftarget_y-target_y < 0 )
    target_y-=1;
  else
    target_y+=1;
}
if( script )
  printf("%d",target_y);
else {
  printf("Source resolution: %dx%d",source_x,source_y);
  if( par != 0 )
    printf(" PAR %.3f",par);
  if( dar != 0 )
    printf(" DAR %.3f",dar);
  printf("\nTarget resolution: %dx%d DAR %f PAR 1:1 *yeha*\n",target_x,target_y,(float)target_x/target_y);
}
}
