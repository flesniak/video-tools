#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

main()
{
int hours, minutes, seconds, target, abit, vbit;
printf("Film-Spielzeit angeben [h:m:s]: ");
scanf("%d:%d:%d", &hours, &minutes, &seconds);
seconds=hours*3600+minutes*60+seconds;
printf("Zielgröße in MB: ");
scanf("%d", &target);
printf("Audio-Bitrate (kbits): ");
scanf("%d", &abit);
vbit=(target*1024*8-seconds*abit)/seconds;
printf("Videobitrate: %d kbit/s\n", vbit);
}
