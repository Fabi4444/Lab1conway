#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define P_SCREEN0 ((unsigned char *)0x2000)
#define P_COLOR0  ((unsigned char *)0x0400)

#define P_SCREEN1 ((unsigned char *)0x6000)
#define P_COLOR1  ((unsigned char *)0x4400)

//HighRes Mode 300x200px
#define XMAX 40
#define YMAX 25
#define BOXSIZE 3
#define ROUNDS 10

//char findNachbarn(char x, char y, char spielfeld[][YMAX]);
//void initSpielfeld(char spielfeld [][YMAX]);
//void printSpielfeld(char spielfeld [][YMAX]);
//int zaehlLebende(char nachbarn[][BOXSIZE]);
//oid pruefeRegeln(int x, int y,  int lebende, char temp[][YMAX], char spielfeld[][YMAX]);

//static const char array[XMAX][YMAX] 
const static char array[YMAX][XMAX] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

char* spielfeld;
//static char temp[XMAX][YMAX];
//static char nachbarn[BOXSIZE][BOXSIZE];
char* temp;
char* a;
char* charset;


int main(void)
{
  clock_t       t;
  unsigned long sec;
  unsigned      sec10;
  unsigned long fps;
  unsigned      fps10;
  unsigned char background;
  unsigned char text;
        
	char x;
	char y;
	//char lebende;
	unsigned int round = 0;
	//char x_init, y_init;
	//char x_spiel, y_spiel;

	t = clock ();
	

	// init
	//fülle das feld mit zufallswerten und gibs aus
	/*
	for (y_init = 0; y_init < YMAX; ++y_init) {
		for (x_init = 0; x_init < XMAX; ++x_init) {
			spielfeld[x_init][y_init] = array[x_init][y_init];
		}
	}
	*/
	clrscr();
	background = bgcolor(COLOR_BLACK);
	text = textcolor(COLOR_WHITE);
	

	//char *buffer = (char)0x400;
	temp = (char *)0x800;
	spielfeld = (char *)0x400;
	charset = (char*) 0x2000;
	// print
	memset(charset, 0, 8);
	memset(&charset[8], 0xFF, 8);
	//VIC.addr = (VIC.addr & 0x0F) | (1 << 4);
	VIC.addr = 0x18;
	memcpy(spielfeld, array, XMAX * YMAX);
	/*for (y_spiel = 0; y_spiel < YMAX; ++y_spiel) {
		for (x_spiel = 0; x_spiel < XMAX; ++x_spiel) {
			//spielfeld[x_spiel + y_spiel * (XMAX - 1)] = array[x_spiel][y_spiel];
			if (spielfeld[x_spiel+y_spiel * (XMAX - 1)]) {
				revers(1);
				cputcxy(x_spiel, y_spiel, 32);
			}
		}
	}*/
	//spielfeld[5] = 2;

	
	while (round < ROUNDS && !kbhit()) {

		//clrscr(); //clear screen
		for (y = 0; y < YMAX; ++y) {
			for (x = 0; x < XMAX; ++x)
			{
				//cprintf("%2d %2d",x , y);
				//gehe über alle nachbarn
				signed char x0 = x - 1;
				signed char x2 = x + 1;
				signed char y0 = y - 1;
				signed char y2 = y + 1;
				char lebende = 0;

				if (x0 < 0) {
					x0 = XMAX - 1;
				}
				if (x2 > XMAX - 1) {
					x2 = 0;
				}
				if (y0 < 0) {
					y0 = YMAX - 1;
				}
				if (y2 > YMAX - 1) {
					y2 = 0;
				}
				lebende += spielfeld[x0 + y0 * (XMAX - 1)];
				lebende += spielfeld[x0 + y * (XMAX - 1)];
				lebende += spielfeld[x0 + y2 * (XMAX - 1)];
				lebende += spielfeld[x + y0 * (XMAX - 1)];
				//nachbarn[1][1] = spielfeld[x][y];
				lebende += spielfeld[x + y2 * (XMAX - 1)];
				lebende += spielfeld[x2 + y0 * (XMAX - 1)];
				lebende += spielfeld[x + y * (XMAX - 1)];
				lebende += spielfeld[x2 + y2 * (XMAX - 1)];

				//cprintf("%d",lebende /7 );
				//hier kommen meine regeln

				switch (lebende)
				{
				case 2:
					temp[x + y * (XMAX - 1)] = spielfeld[x + y * (XMAX - 1)];
					break;

				case 3:
					temp[x + y * (XMAX - 1)] = 1;
					break;
				default:
					temp[x + y * (XMAX - 1)] = 0;
					break;
				}



				//if (spielfeld[xy]) {
				//	revers(1);
				//	cputcxy(x, y, 32);
				//}


			}// for x
		}// for y

		//memcpy(spielfeld, temp, XMAX * YMAX);
		a = spielfeld; // vertauschen der pointer
		spielfeld = temp;
		temp = a;
		VIC.addr ^= (VIC.addr & 0x0F) | (0b11 << 4);

		round++;
	}
	t = clock() - t;

	/* Reset screen colors */
	bgcolor(background);
	textcolor(text);
	clrscr();

	/* Calculate stats */
	sec = (t * 10) / CLK_TCK;
	sec10 = sec % 10;
	sec /= 10;
	fps = (round * (CLK_TCK * 10)) / t;
	fps10 = fps % 10;
	fps /= 10;

	/* Output stats */
	gotoxy(0, 0); cprintf("time  : %lu.%us", sec, sec10);
	gotoxy(0, 1); cprintf("frames: %lu", round);
	gotoxy(0, 2); cprintf("fps   : %lu.%u", fps, fps10);

	/* Wait for a key, then end */
	cputsxy(0, 4, "Press any key when done...");
    (void) cgetc ();

    /* Done */
    return EXIT_SUCCESS;
}
