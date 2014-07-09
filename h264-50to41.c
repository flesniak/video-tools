#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
if( argc != 2) {
  fprintf(stderr,"Usage: %s file.h264\n",*argv);
  exit(1);
  }
argv++;

FILE *f;
f = fopen(*argv,"r+");
if( f == NULL ) {
  fprintf(stderr,"Error opening file %s\n",*argv);
  exit(1);
  }

int c, n = 0;
do {
  c =fgetc(f);
  if( c == 0x32 ) {
    fseek(f,-1,SEEK_CUR);
    printf("Token 0x32 found at offset %d. Proceed? [y/N] ",n);
    char c;
    scanf("%c",&c);
    if( c == 'y' ) {
      fputc(0x29,f);
      printf("0x32 changed to 0x29. Have a nice day!\n");
      break;
      }
    }
  n++;
  } while( c != EOF );
if( c == EOF )
  printf("Token 0x32 not found. Exiting.\n");

fclose(f);
}
