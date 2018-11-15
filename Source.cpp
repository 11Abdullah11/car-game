#include <stdio.h>  
#include <process.h>  
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

void gotoXY(int x, int y);
void bsort(int a[], int);
int SetFontSize(HANDLE, COORD);

int i, j;
FILE * stream;

int main(void) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(h, CONSOLE_FULLSCREEN_MODE, 0);
	char welcome[14] = "Crazy CAR !!!";
	char enter[21] = "Press Enter to start";
	COORD size;
	size.X = 0;
	size.Y = 20;
	SetFontSize(h, size);
	int highest[4] = { 0,0,0,0 }, hurdlerow1 = 0;
	// reading previous file
	fopen_s(&stream, "Highscore.txt", "r");
	if (stream) {
		for (int i = 0; i < 3; i++) {
			fscanf_s(stream, "%d", &highest[i]);
		}
	}
	fclose(stream);
	int  hurdlerow2 = 0, hurdlerow3 = 0, life = 3, mark = 0, column = 11, hurdlecolumn = 0;
	time_t begin, end;
	char c[35][30], start, quit = '0';
	double timecount = 1;

	// Game beginning
	system("color 3F");
	gotoXY(60, 14);
	for (i = 0; i < 14; i++) {
		printf("%c", welcome[i]);
		Sleep(70);
	}
	Sleep(200);
	gotoXY(55, 16);
	for (i = 0; i < 21; i++) {
		printf("%c", enter[i]);
		Sleep(70);
	}
	scanf_s("%c", &start);
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	system("color 3F");
	gotoXY(60, 15);
	printf("3");
	Sleep(1000);
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	system("color 3F");
	gotoXY(60, 15);
	printf("2");
	Sleep(1000);
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	system("color 3F");
	gotoXY(60, 15);
	printf("1");
	Sleep(1000);
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	system("color 3F");
	gotoXY(58, 15);
	printf("Start");
	gotoXY(84, 30);
	printf("Press q at anytime during game to quit");
	Sleep(1500);
	system("CLS");
	system("color 4E");
	begin = time(NULL);
	while (1) {
		for (; 1;) {

			end = time(NULL);
			timecount = difftime(end, begin);

			// Road
			for (i = 0; i < 35; i++) {
				for (j = 0; j < 30; j++) {
					if (j == 0 || j == 1 || j == 28 || j == 29) {
						c[i][j] = '|';
					}

					else
						c[i][j] = ' ';
				}
			}

			//Input
			if (_kbhit()) {
				if (GetAsyncKeyState(VK_LEFT) && column > 10) {
					column = column - 8;

				}
				if (GetAsyncKeyState(VK_RIGHT) && column < 16) {
					column = column + 8;
				}
				quit = _getch();
				if (quit == 'q') {
					break;
				}
			}

			// Hurdle 1
			if (abs(hurdlerow1 - hurdlerow3) > 7) {
				for (i = 0; i < 10; i++) {
					c[hurdlerow1][hurdlecolumn + i] = 'V';
				}				hurdlerow1++;
			}
			if (hurdlerow1 >= 26 && column == 3) {
				break;
			}

			if (hurdlerow1 == 29) {
				hurdlerow1 = hurdlerow1 - 29;
			}



			// Hurdle 2
			for (i = 11; i < 21; i++) {
				c[hurdlerow2][hurdlecolumn + i] = 'W';
			}
			c[hurdlerow2][hurdlecolumn + 21] = ' ';
			c[hurdlerow2][hurdlecolumn + 20] = ' ';
			c[hurdlerow2][hurdlecolumn + 19] = ' ';
			hurdlerow2++;
			if (hurdlerow2 >= 26 && column == 11) {
				break;
			}

			if (hurdlerow2 >= 29) {
				hurdlerow2 = hurdlerow2 - 29;
			}



			// Hurdle 3
			if (abs(hurdlerow2 - hurdlerow3) > 13) {
				for (i = 20; i < 30; i++) {
					c[hurdlerow3][hurdlecolumn + i] = 'V';
				}
				hurdlerow3++;
			}
			if (hurdlerow3 >= 26 && column == 19) {
				break;
			}
			if (hurdlerow3 >= 29) {
				hurdlerow3 = hurdlerow3 - 29;
			}



			//car

			for (i = 1; i <= 6; i++) {
				c[26][column + i] = '_';
			}
			for (i = 1; i <= 6; i++) {
				c[28][column + i] = '_';
			}
			c[25][column + 2] = '_';
			c[25][column + 3] = '_';
			c[25][column + 4] = '_';
			c[25][column + 5] = '_';
			c[26][column + 1] = '|';
			c[26][column + 6] = '|';
			c[27][column + i] = '|';
			c[28][column + i] = '|';
			c[27][column + 0] = '|';
			c[28][column + 0] = '|';


			// printing array
			for (i = 0; i < 29; i++) {
				gotoXY(50, i + 5);
				for (j = 0; j < 30; j++) {
					printf("%c", c[i][j]);
				}
			}

			//lives and score
			printf("                                Lives %d", life);
			printf("                                            Score %d\n\n\n\n\n\n\n\n", (int)timecount);

			// Speed of game
			if (timecount < 10) {
				Sleep(50);
			}
			else if (timecount < 20) {
				Sleep(30);
			}
			else if (timecount < 30) {
				Sleep(20);
			}
			else if (timecount < 40) {
				Sleep(10);
			}
			else {
				Sleep(5);
			}
		}
		if (quit == 'q') {
			break;
		}
		life = life - 1;
		if (life == 0) {
			break;
		}
		if (hurdlerow1 > 20) {
			hurdlerow1 = hurdlerow1 - 20;
		}
		if (hurdlerow2 > 20) {
			hurdlerow2 = hurdlerow2 - 20;
		}
		if (hurdlerow3 > 20) {
			hurdlerow3 = hurdlerow3 - 20;
		}
		system("CLS");
		gotoXY(45, 13);
		printf("OUT!!!");
		gotoXY(42, 17);
		printf("Press Enter to Play again:");
		scanf_s("%c", &start);
		system("CLS");
	}

	highest[3] = (int)timecount;

	// final score
	system("CLS");
	gotoXY(52, 8);
	printf("Game Over");
	gotoXY(49, 9);
	printf("Your score is %.0f", timecount);

	// Printing high score
	gotoXY(51, 10);
	printf("TOP SCORES");
	Sleep(50);
	bsort(highest, 4);
	for (int i = 0; i < 3; i++) {
		gotoXY(52, 11 + i);
		printf("%d. ", i + 1);
		Sleep(50);
		printf(":%d\n\n\n\n\n", highest[i]);
		Sleep(100);
	}

	// storing scores in file
	fopen_s(&stream, "Highscore.txt", "w");
	for (int i = 0; i < 3; i++) {
		fprintf_s(stream, "%d ", highest[i]);
	}
	printf("\n");
	fclose(stream);
	system("pause");
}


void gotoXY(int x, int y) {
	//Initialize the coordinates
	COORD coord = { x, y };
	//Set the positi
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
void bsort(int a[], int i) {
	int swap = 0;

	for (int c = 0; c < i - 1; c++) {
		for (int d = 0; d < i - c - 1; d++) {
			if (a[d] < a[d + 1])
			{
				swap = a[d];
				a[d] = a[d + 1];
				a[d + 1] = swap;
			}
		}
	}


}
int SetFontSize(HANDLE windowHandle, COORD size)
{
	CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };

	if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	font.dwFontSize = size;

	if (!SetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	return 1;
}
