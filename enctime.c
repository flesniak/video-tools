#include<stdlib.h>
#include<stdio.h>
main()
{
int frames, cur_frames, rem_frames, speed, rem_time, rem_seconds, rem_hours, rem_minutes, length, len_hour, len_min, minutes;
printf("This Program calculates the remaining time by video encoding (for example by transcode).\nDo you want to give\n1. The video length\n2. The count of frames\n");
//Abfrage der Länge
scanf("%d", &length);
if(length==1)
 {
 printf("Please give the Video Stream Length in hours minutes (including a blank between!)\n");
 scanf("%d %d", &len_hour, &len_min);
 minutes=len_hour*60+len_min;
 frames=minutes*1500;
 printf("So you have %d frames.\n", frames);
 }
if(length==2)
 {
 printf("Please give the summary of frames in the current video stream.\n");
 scanf("%d", &frames);
 }
printf("And How many frames do you encode in 1 second?\n");
scanf("%d", &speed);
cur_frames=0;
for(cur_frames=1;cur_frames=frames;cur_frames+1)
 {
 printf("How many frames are now encoded?\n");
 scanf("%d", &cur_frames);
 if(cur_frames==0)
  {
  printf("Thanks for using this program. Exit.\n");
  exit(0);
  }
 //Ausrechnung der verbleibenden frames & ausgabe
 rem_frames=frames-cur_frames;
 printf("OK. Now %d frames remaining.\n", rem_frames);
 //Ausrechnung verbleibende Zeit
 rem_seconds=rem_frames/speed;
 rem_time=rem_seconds/60;
 if(rem_time>59)
  {
  rem_hours=rem_time/60;
  rem_minutes=rem_time%60;
  printf("Now it will still encode for %d hours and %d minutes.\n\n", rem_hours, rem_minutes);
  }
 else
  {
  if(rem_time<=1)
   {
   printf("Now it will still encode for %d minute.\n\n", rem_time);
   }
  printf("Now it will still encode for %d minutes.\n\n", rem_time);
  }
 }
}
