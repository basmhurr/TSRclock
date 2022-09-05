/*  TSR(terminate and stay resident) DOS example
 basim hur from Iraq 2022
 note i took this code from a site and i added the
 keep() function.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <conio.h>
#include <bios.h>


#define INTR 0X1C

#ifdef __cplusplus
#define __CPPARGS ...
#else
#define __CPPARGS
#endif



char far *scr=(char far*)0xB0008000L;

void interrupt ( *oldhandler)(__CPPARGS);

int count=0;

char hbuf[6];
char mbuf[6];
char sbuf[6];

struct  time t;



void interrupt handler(__CPPARGS)

{

      char far *p = 0;

      gettime(&t);
      hbuf[0] = '0' + t.ti_hour / 10;
      hbuf[1] = '0' + t.ti_hour % 10;
      mbuf[0] = '0' + t.ti_min / 10;
      mbuf[1] = '0' + t.ti_min % 10;
      sbuf[0] = '0' + t.ti_sec / 10;
      sbuf[1] = '0' + t.ti_sec % 10;

      p = scr;

      *p++ = hbuf[0];
      *p++ = 0x4f;
      *p++ = hbuf[1];
      *p++ = 0x4f;
      *p++ = ':';
      *p++ = 0x4f;


      *p++ = mbuf[0];
      *p++ = 0x4f;
      *p++ = mbuf[1];
      *p++ = 0x4f;
      *p++ = ':';
      *p++ = 0x4f;


      *p++ = sbuf[0];
      *p++ = 0x4f;
      *p++ = sbuf[1];
      *p++ = 0x4f;

      oldhandler();
}


int main(int argc, char *argv[])
{
      if(argc <= 1)
      {
	    printf("Syntax: Timer -I (for Install)\n");
	    printf("Syntax: Timer -U (for Uninstall)\n");
	    return 0;
      }
      if(argv[1][1] == 'I' || argv[1][1] == 'i')
      {
	    printf("Installing...\n");
	    oldhandler = getvect(INTR);
	    setvect(INTR, handler);
	    setvect(32, oldhandler);
	    printf("Done\n");
	    keep(0,0x1000);
      }
      else
      {
	    printf("Uninstalling...\n");
	    oldhandler = getvect(32);
	    setvect(INTR, oldhandler);
	    printf("Done\n");
      }
   return 0;
}
