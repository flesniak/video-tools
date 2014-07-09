//Force all sequence headers in m2v file to specified frame rate

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void usage(char *path)
{
printf("Usage: %s <fpscode> <infile> [outfile]\n\n",path);
printf("If outfile is ommitted, infile will be modified.\n");
printf("FPS codes:\n  1:23.976\n  2:24\n  3:25\n  4:29.97\n  5:30\n  6:50\nNote that these are only the most common fps codes.\nYou may specify any other number in hex (0-f). Refer to the DVD specification.\n");
exit(1);
}

int main(int argc, char* argv[])
{
char *appstr;
appstr=malloc(strlen(*argv));
strcpy(appstr,*argv);
argv++;

//Check arguments
if( (argc < 3) | (argc > 4) )
  usage(appstr);

char *fpsstr, *infilestr, *outfilestr;
fpsstr=malloc(strlen(*argv));
strcpy(fpsstr,*argv);
argv++;
infilestr=malloc(strlen(*argv));
strcpy(infilestr,*argv);
argv++;
if( argc == 4 ) {
  outfilestr=malloc(strlen(*argv));
  strcpy(outfilestr,*argv);
  }

printf("appstr: %s\n",appstr);
printf("fpsstr: %s\n",fpsstr);
printf("infilestr: %s\n",infilestr);
printf("outfilestr: %s\n",outfilestr);
bool useoutfile = (outfilestr != NULL);
putchar('\n');

//Get fps code
char fps;
fps = (char)strtol(fpsstr,NULL,16);
//sscanf(fpsstr,"%x",&fps);
if( ((fpsstr != "0") & (fps == 0)) | (fps < 0) ) { //Conversion failure test
  printf("ERROR: Unknown FPS code %s!\n",fpsstr);
  usage(appstr);
  }
printf("Changing fps code to %d...\n", fps);

//Open files
FILE *infile, *outfile;
if( useoutfile ) {
  puts("Using outfile...");
  infile = fopen(infilestr,"rb");
  outfile = fopen(outfilestr,"wb");
  }
else {
  puts("Updating infile...");
  infile = fopen(infilestr,"r+b");
}

//Check file open results
if( infile == NULL ) {
  puts(infilestr);
  printf("Failed to open file %s\n", infilestr);
  usage(appstr);
  }
if( useoutfile & (outfile == NULL) ) {
  printf("Failed to open file %s\n", outfilestr);
  usage(appstr);
  }

char token[4] = { 0x00, 0x00, 0x01, 0xB3 };
char hdr[4];
fgets(hdr,4,infile);
while( strchr(hdr,EOF) == NULL ) {
  if( hdr == token ) {
    printf("Sequence header found at %d\n", ftell(infile));
    fseek(infile,4,SEEK_CUR);
    printf("FPS code: %x\n",fgetc(infile));
    }
  fseek(infile,-2,SEEK_CUR);
  fgets(hdr,4,infile);
  }

fclose(infile);
if( useoutfile )
  fclose(outfile);
}

/*PROBLEM:char *appname;
appname=malloc(strlen(*argv));
strcpy(appname,*argv);
argv++;
printf("argv: %s\nappname: %s\n",*argv,appname);

if( (argc < 3) | (argc > 4) )
  usage(appname);

printf("argv: %s\nappname: %s\n",*argv,appname);
argv++;
printf("argv: %s\nappname: %s\n",*argv,appname);
char fps;
printf("argv: %s\nappname: %s\n",*argv,appname);
sscanf(*argv,"%x",&fps);
printf("argv: %s\nappname: %s\n",*argv,appname);
if( (*argv != "0") & (fps == 0) ) { //Conversion failure test
  printf("ERROR: Unknown FPS code!\n");
  usage(appname);
  }
printf("argv: %s\nappname: %s\n",*argv,appname);

printf("Changing fps code to %d...\n", fps);
printf("argv: %s\nappname: %s\n",*argv,appname);*/