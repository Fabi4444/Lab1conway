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
#define ROUNDS 20

char findNachbarn(char x, char y, char spielfeld[][YMAX]);
void initSpielfeld(char spielfeld [][YMAX]);
void printSpielfeld(char spielfeld [][YMAX]);
int zaehlLebende(char nachbarn[][BOXSIZE]);
void pruefeRegeln(int x, int y,  int lebende, char temp[][YMAX], char spielfeld[][YMAX]);

//static const char array[XMAX][YMAX] 
const static int array[XMAX][YMAX]= {
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
};

static char spielfeld[XMAX][YMAX];
static char temp[XMAX][YMAX];
//static char nachbarn[BOXSIZE][BOXSIZE];

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

	t = clock ();
	initSpielfeld(spielfeld);
	clrscr();
	background = bgcolor(COLOR_BLACK);
	text = textcolor(COLOR_WHITE);
	printSpielfeld(spielfeld);
//	signal (int sig, __sigfunc func);


	while(round < ROUNDS && !kbhit()){
		for(y = 0; y< YMAX; y++){
			for(x = 0; x< XMAX; x++)
			{
				//cprintf("%2d %2d",x , y);
				//gehe über alle nachbarn
				signed char x0 = x - 1;
				signed char x2 = x + 1;
				signed char y0 = y - 1;
				signed char y2 = y + 1;
				char lebende = 0;

				if (x0 < 0) {
					x0 = XMAX;
				}
				if (x2 > XMAX) {
					x2 = 0;
				}
				if (y0 < 0) {
					y0 = YMAX;
				}
				if (y2 > YMAX) {
					y2 = 0;
				}



				lebende += spielfeld[x0][y0];
				lebende += spielfeld[x0][y];
				lebende += spielfeld[x0][y2];
				lebende += spielfeld[x][y0];
				//nachbarn[1][1] = spielfeld[x][y];
				lebende += spielfeld[x][y2];
				lebende += spielfeld[x2][y0];
				lebende += spielfeld[x2][y];
				lebende += spielfeld[x2][y2];
				

				//cprintf("%d",lebende /7 );
				//hier kommen meine regeln


				switch (spielfeld[x][y])
				{
				case 0:
					if (lebende == 3)
					{
						temp[x][y] = 1;
					}
					break;
				case 1:
					if (lebende == 2 || lebende == 3) {
						temp[x][y] = 1;
					}
					if (lebende < 2 || lebende > 3) {
						temp[x][y] = 0;
					}
					break;
				default:
					break;
				}
			}// for x
		}// for y

		memcpy(spielfeld,temp,XMAX*YMAX);
	
		round++;
		printSpielfeld(spielfeld);	
	}
		t = clock() - t;
	
  /* Reset screen colors */
    bgcolor (background);
    textcolor (text);
    clrscr ();

    /* Calculate stats */
    sec   = (t * 10) / CLK_TCK;
    sec10 = sec % 10;
    sec  /= 10;
    fps   = (round * (CLK_TCK * 10)) / t;
    fps10 = fps % 10;
    fps  /= 10;

    /* Output stats */
    gotoxy (0, 0); cprintf ("time  : %lu.%us", sec, sec10);
    gotoxy (0, 1); cprintf ("frames: %lu", round);
    gotoxy (0, 2); cprintf ("fps   : %lu.%u", fps, fps10);

    /* Wait for a key, then end */
    cputsxy (0, 4, "Press any key when done...");
    (void) cgetc ();

    /* Done */
    return EXIT_SUCCESS;
}



/*void pruefeRegeln(int x, int y, int lebende, char temp[][YMAX], char spielfeld[][YMAX]) {
	//hier kommen meine regeln


	switch (spielfeld[x][y])
	{
	case 0:
		if (lebende == 3)
		{
			temp[x][y] = 1;
		}
		break;
	case 1:
		if (lebende == 2 || lebende == 3) {
			temp[x][y] = 1;
		}
		if (lebende < 2 || lebende > 3) {
			temp[x][y] = 0;
		}
		break;
	default:
		break;
	}
	
}
*/






/*char findNachbarn(char x, char y, char spielfeld[][YMAX]) {
	//gehe über alle nachbarn
	signed char x0 = x-1;
	signed char x2 = x+1;
	signed char y0 = y-1;
	signed char y2 = y+1;
	char lebende = 0;
	
	if (x0 < 0) {
		x0 = XMAX;
	}
	if (x2 > XMAX) {
		x2 = 0;
	}
	if (y0 < 0) {
		y0 = YMAX;
	}
	if (y2 > YMAX) {
		y2 = 0;
	}
	
	
	
	lebende += spielfeld[x0][y0];
	lebende += spielfeld[x0][y];
	lebende += spielfeld[x0][y2];
	lebende += spielfeld[x][y0];
	//nachbarn[1][1] = spielfeld[x][y];
	lebende += spielfeld[x][y2];
	lebende += spielfeld[x2][y0];
	lebende += spielfeld[x2][y];
	lebende += spielfeld[x2][y2];
	return lebende;

}
*/




void printSpielfeld(char spielfeld [][YMAX]){
	long int x,y;
	for(y = 0; y< YMAX; y++){
		for(x = 0; x< XMAX; x++){
			if(spielfeld[x][y] == 1){
				revers(1);
			} else{
				revers(0);
			}		
 			cputcxy (x, y, 32);
		}
	}
}



void initSpielfeld(char spielfeld [][YMAX]){
	long int x,y;
	//fülle das feld mit zufallswerten und gibs aus
	for(y = 0; y< YMAX; y++){
		for(x = 0; x< XMAX; x++){
				spielfeld[x][y] = array[x][y];
		}
	}
}
