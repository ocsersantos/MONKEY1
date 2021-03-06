// MONKEY1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <Windows.h>
#include <Winbase.h>
#include <conio.h>
#include "Utils.h"

//#include "../../Dad/Console.h"

// Specify characters of interest 
const char CharSet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ' " };//THERE MUST BE A SPACE
const int CharSet_N = sizeof(CharSet) / sizeof(char) - 1;	// Number of characters in set (don't count null)

bool sfx = true;



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function returns to index of the charachter or -1 if not found.
\*==========================================================================*/

int FindChar(char c)
{
	// Look for char in set and inc its freq counter if found
	for (int i = 0; i < CharSet_N; i++)
	{
		if (toupper(c) == CharSet[i])
			return i;
	}
	return -1;
}



/*==========================================================================*\
|Date Created: 2017 DEC 11
|Date Revised:
|
|This function brings up a dialog box that lets me pick a file. If it returns
|File contians the file name.
\*==========================================================================*/

bool OpenFile(wchar_t File[], int Size)
{
	OPENFILENAME ofn;

	// open a file name
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = File;
	//ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = Size;
	ofn.lpstrTitle = L"Select file to base letter sequence on.";
	ofn.lpstrFilter = L"Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	return GetOpenFileName(&ofn);
}


/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function removed new lines, extra spaces, and lines with "*". Returns true
| if it is succesful at reaching the end of the file.
\*==========================================================================*/

bool PreProcessFile(FILE *pFile, char Data[], int datacount)
{
	memset(Data, 0, datacount * sizeof(char));

	if (datacount < 1)
		return false;
	int Numdatachars = 0;
	bool EraseMode = false;
	// Process one line at a time
	int c = '0', last_c = '\n', orig_c;
	for (;; last_c = orig_c)
	{
		c = fgetc(pFile);
		orig_c = c;
		if (c == EOF)
			return feof(pFile) != 0;

		if (EraseMode)
		{
			if (c == '\n')
				EraseMode = false;
			continue;
		}

		// Ignore empty lines and lines starting with the '*' char
		if (c == '*'&& last_c == '\n')
		{
			EraseMode = true;
			continue;
		}

		//Convert new lines to spaces.
		if (FindChar(c) == -1)
			c = ' ';

		//Removes extra spaces.
		if (iswhitespace(c))
		{
			if (Numdatachars != 0 && iswhitespace(Data[Numdatachars - 1]))
				continue;
		}

		//insert char
		if (Numdatachars == datacount - 1)
		{
			printf("Data array is too small, try again with a smaller file.\n");
			return false;
		}
		Data[Numdatachars] = c;
		(Numdatachars)++;
	}
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function counts the frequency of each charachter.
\*==========================================================================*/

void FreqCount(int Freq[], const char Data[])
{
	// Zero counts
	memset(Freq, 0, CharSet_N * sizeof(int));

	int j = 0;
	// Scan adjusted line, counting each char in CharSet (case insensitive)
	while (Data[j] != '\0')
	{
		// Look for char in set and inc its freq counter if found
		int idx = FindChar(Data[j]);
		if (idx != -1)
			Freq[idx]++;
		// Next
		j++;
	}
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function counts the freuency of charachter pairs.
\*==========================================================================*/

void Freq2Count(int Freq2[CharSet_N][CharSet_N], const char Data[])
{
	// Zero counts
	memset(Freq2, 0, CharSet_N * CharSet_N * sizeof(int));

	int j = 0;
	// Scan adjusted line, counting each char in CharSet (case insensitive)
	while (Data[j] != '\0')
	{
		int idx = FindChar(Data[j]);
		if (idx != -1)
		{
			int idx2 = FindChar(Data[j + 1]);
			if (idx2 != -1)
				Freq2[idx][idx2]++;
		}
		// Next
		j++;
	}
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function counts the freuency of charachter triads.
\*==========================================================================*/

void Freq3Count(int Freq3[CharSet_N][CharSet_N][CharSet_N], const char Data[])
{
	// Zero counts
	memset(Freq3, 0, CharSet_N * CharSet_N * CharSet_N * sizeof(int));

	int j = 0;
	// Scan adjusted line, counting each char in CharSet (case insensitive)
	while (Data[j] != '\0' && Data[j + 1] != '\0')
	{
		int idx = FindChar(Data[j]);
		if (idx != -1)
		{
			int idx2 = FindChar(Data[j + 1]);
			if (idx2 != -1)
			{
				int idx3 = FindChar(Data[j + 2]);
				if (idx3 != -1)
					Freq3[idx][idx2][idx3]++;
			}
		}
		// Next
		j++;
	}
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function counts the freuency of charachter quads.
\*==========================================================================*/

void Freq4Count(int Freq4[CharSet_N][CharSet_N][CharSet_N][CharSet_N], const char Data[])
{
	// Zero counts
	memset(Freq4, 0, CharSet_N * CharSet_N * CharSet_N * CharSet_N * sizeof(int));

	int j = 0;
	// Scan adjusted line, counting each char in CharSet (case insensitive)
	while (Data[j] != '\0' && Data[j + 1] != '\0' && Data[j+2] != '\0')
	{
		int idx = FindChar(Data[j]);
		if (idx != -1)
		{
			int idx2 = FindChar(Data[j + 1]);
			if (idx2 != -1)
			{
				int idx3 = FindChar(Data[j + 2]);
				if (idx3 != -1)
				{
					int idx4 = FindChar(Data[j + 3]);
					if (idx4 != -1)
						Freq4[idx][idx2][idx3][idx4]++;
				}
			}
		}
		// Next
		j++;
	}
}

/*==========================================================================*\
| Date Created: 2017 DEC 15
| Date Revised:
|
| This function randomly selects a key from the frequency distribution.
\*==========================================================================*/

int GetRandomKeyIdx(int total, const int Freq[])
{
	int key = GetRand(0, total - 1);
	char c = -1;
	for (int i = 0; i < CharSet_N; i++)
	{
		if (key < Freq[i])
			return i;
		key -= Freq[i];
	}
	assert(0);
	return -1;
}


bool monkeyout_print(FILE *pFile, char c)
{

	//Playsound plays a noise if you get the right combination of tags at the end and even then it might not work.
	//PlaySound(TEXT("F:\\Benjamin\\Programs\\MONKEY1\\A1-0001_Keypress.wav"),NULL, SND_NODEFAULT | SND_ASYNC);
	if (c != ' ')
	{
		if (sfx)
			PlaySound(TEXT("F:\\Benjamin\\Programs\\MONKEY1\\typesound2"), NULL, SND_NODEFAULT);
	}
	Sleep(GetRand(0,50));
	printf("%c", c);
	

	if (fprintf(pFile, "%c", c) != 1)
	{
		printf("MONKEY RAN OUT OF PAPER\n");
		return false;
	}
	return true;
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function
\*==========================================================================*/

bool monkeyout(FILE *pFile, char c)
{
	c = tolower(c);
	static int n = 0, y = 0;
	char holder;
	static char nextc = ' ', lastc = ' ';
	holder = c;
	c = nextc;
	nextc = holder;

	if (lastc == ' ' && c == 'i' && nextc == ' ')
		c = 'I';

	if (c == ' ')
		n++;

	if (n == 7 || n == 8)
	{
		n++;
		c = toupper(c);
		if (n == 8)
			if (!monkeyout_print(pFile, '.'))
				return false;
	}

	if (n == 9)
		n = 0;
	if (!monkeyout_print(pFile, c))
		return false;
	lastc = c;
	return !_kbhit();
}


/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function randomly prints letters. Returns true if the keyboard is hit.
\*==========================================================================*/

bool Monkey0(FILE *pFile)
{
	int i;
	for (i = 0; true; i++)
	{
		char c = CharSet[GetRand(0, CharSet_N - 1)];
		if (!monkeyout(pFile, c))
			break;

	}
	printf("\n%d letters were printed.\n", i);
	return true;
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function randomly prints letters but is weighted with the
|frequency information. It returns true on a sucess, otherwise false.
\*==========================================================================*/



bool Monkey1(FILE *pFile, const int Freq[])
{
	//	char set[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ' " };

	//	int freq[] = { 2043, 410, 584, 1099, 3277, 629 , 478, 1773, 1736, 34, 255, 1238, 889, 1741, 2578, 433, 27, 1593, 1856, 2557, 1014, 309, 716, 21, 783, 14, 203, 6934};

		//count total letters
	int total = 0, i;
	for (i = 0; i < CharSet_N; i++)
		total += Freq[i];

	for (i = 0; true; i++)
	{
		char c = CharSet[GetRandomKeyIdx(total, Freq)];
		if (!monkeyout(pFile, c))
			break;
	}
	printf("\n%d letters were printed.\n", i);
	return true;
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function randomly prints letters but is weighted with the
|frequency pair information. It returns true on a sucess, otherwise false.
\*==========================================================================*/

bool Monkey2(FILE *pFile, const int Freq2[CharSet_N][CharSet_N])
{
	// generate totals
	int total[CharSet_N], i;
	memset(total, 0, sizeof(total));
	for (i = 0; i < CharSet_N; i++)
	{
		for (int j = 0; j < CharSet_N; j++)
			total[i] += Freq2[i][j];
	}

	//prime
	bool done = false;
	int row;
	for (row = -1; !done && row < CharSet_N;)
	{
		row++;
		done = total[row] != 0;
	}
	printf("Priming with %c\n\n\n", CharSet[row]);

	//run 
	int NumKeys;
	for (NumKeys = 0; true; NumKeys++)
	{
		int Idx = GetRandomKeyIdx(total[row], Freq2[row]);
		char c = CharSet[Idx];
		row = Idx;

		if (!monkeyout(pFile, c))
			break;
	}
	printf("\n%d letters were printed.\n", NumKeys);
	return true;
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function This function randomly prints letters but is weighted with the
|frequency pair information. It returns true on a sucess, otherwise false.
\*==========================================================================*/

bool Monkey3(FILE *pFile, const int Freq3[CharSet_N][CharSet_N][CharSet_N])
{
	// generate totals
	int total[CharSet_N][CharSet_N], i;
	memset(total, 0, sizeof(total));
	for (i = 0; i < CharSet_N; i++)
	{
		for (int j = 0; j < CharSet_N; j++)
		{
			for (int k = 0; k < CharSet_N; k++)
				total[i][j] += Freq3[i][j][k];
		}
	}
	//print_table(CharSet_N, CharSet_N, &CharSet[0], &CharSet[0], &total[0][0]);

	//prime
	bool done = false;
	int row, col;
	for (row = -1; !done && row < CharSet_N;)
	{
		row++;
		for (col = -1; !done && col < CharSet_N;)
		{
			col++;
			done = total[row][col] != 0;
		}
	}
	printf("Priming with %c%c\n\n\n", CharSet[row], CharSet[col]);

	//run
	int NumKeys;
	for (NumKeys = 0; true; NumKeys++)
	{
		assert(total[row][col] != 0);
		int Idx = GetRandomKeyIdx(total[row][col], Freq3[row][col]);
		char c = CharSet[Idx];
		row = col;
		col = Idx;

		if (!monkeyout(pFile, c))
			break;
	}
	printf("\n%d letters were printed.\n", NumKeys);
	return true;
}



bool Monkey4(FILE *pFile, const int Freq4[CharSet_N][CharSet_N][CharSet_N][CharSet_N])
{
	// generate totals
	int total[CharSet_N][CharSet_N][CharSet_N], i;
	memset(total, 0, sizeof(total));
	for (i = 0; i < CharSet_N; i++)
		for (int j = 0; j < CharSet_N; j++)
			for (int k = 0; k < CharSet_N; k++)
				for (int l = 0; l < CharSet_N; l++)
					total[i][j][k] += Freq4[i][j][k][l];

	//prime
	bool done = false;
	int d1, d2, d3;
	for (d1 = -1; !done && d1 < CharSet_N;)
	{
		d1++;
		for (d2 = -1; !done && d2 < CharSet_N;)
		{
			d2++;
			for (d3 = -1; !done && d3 < CharSet_N;)
			{
				d3++;
				done = total[d1][d2][d3] != 0;
			}
		}
	}
	printf("Priming with %c%c%c\n\n\n", CharSet[d1], CharSet[d2], CharSet[d3]);

	//run
	int NumKeys;
	for (NumKeys = 0; true; NumKeys++)
	{
		assert(total[d1][d2] != 0);
		int Idx = GetRandomKeyIdx(total[d1][d2][d3], Freq4[d1][d2][d3]);
		char c = CharSet[Idx];
		d1 = d2;
		d2 = d3;
		d3 = Idx;

		if (!monkeyout(pFile, c))
			break;
	}
	printf("\n%d letters were printed.\n", NumKeys);
	return true;
}

/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function processes the users input. It returns false when the user
| wants to stop, otherwise it returns true.
\*==========================================================================*/

bool process(int Freq[], int Freq2[CharSet_N][CharSet_N], int Freq3[CharSet_N][CharSet_N][CharSet_N],
	int Freq4[CharSet_N][CharSet_N][CharSet_N][CharSet_N])
{
	errno_t code;
	FILE *pFile;
	char m;
	printf("\nSelect monkey 0, 1, 2, 3, or 4(any other char to quit), or type an S to toggle sfx on/off: ");
	m = _getch();
	printf("\n");
	m = tolower(m);
	if (!(m == 's' || (m >= '0' && m <= '4')))
		return false;
	if (m == 's')
	{
		sfx = !sfx;
		return true;
	}
	char Bookname[500];

	sprintf_s(Bookname, sizeof (Bookname),"F:\\Benjamin\\Programs\\MONKEY1\\book%c.txt", m);

	code = fopen_s(&pFile, Bookname, "w");
	if (code != 0)
	{
		printf("failed to open\n");
		return false;
	}

	bool ok = true;
	switch (m)
	{
	case '0':
		ok = Monkey0(pFile);
		break;

	case '1':
		ok = Monkey1(pFile, Freq);
		break;

	case '2':
		ok = Monkey2(pFile,Freq2);
		break;

	case '3':
		ok = Monkey3(pFile, Freq3);
		break;

	case '4':
		ok = Monkey4(pFile, Freq4);
		break;

	}

	fclose(pFile);
	return ok;
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function looks at a file and gathers infomation on the letter
|distribution. It returns true on a sucess, otherwise false.
\*==========================================================================*/

bool LearnLanguage(int Freq[], int Freq2[CharSet_N][CharSet_N], int Freq3[CharSet_N][CharSet_N][CharSet_N],
	int Freq4[CharSet_N][CharSet_N][CharSet_N][CharSet_N])
{
	errno_t code;
	FILE *pFile;


	// Specify file containing text to analyze
	//char
	//	*pFilename = "F:\\Benjamin\\Programs\\MONKEY1\\Hamlet, Act III.txt";
	//	*pFilename = "F:\\Benjamin\\Programs\\MONKEY1\\Hamlet.txt";
	wchar_t Filename[1000] = L"F:\\Benjamin\\Programs\\MONKEY1\\Hamlet, Act III.txt";
	if (!OpenFile(Filename, _countof(Filename)))
		return false;


	// Open file
	code = _wfopen_s(&pFile, Filename, L"r");
	if (code != 0)
	{
		wprintf(L"Cannot open file: %s", Filename);
		Sleep(2000);
		return false;
	}

	// Process file
	char data[500000];
	if (!PreProcessFile(pFile, data, _countof(data)))
	{
		printf("Cannot process file");
		Sleep(2000);
		fclose(pFile);
		return false;
	}
	//printf(data);
	FreqCount(Freq, data);

	// Generate char freq
	wprintf(L"Character frequencies for file: %s", Filename);
	printf("\n\n");
	for (int i = 0; i < CharSet_N; i++)
		printf("Char %c %i\n", CharSet[i], Freq[i]);

	//generate pairs
	Freq2Count(Freq2, data);
	wprintf(L"Character frequency pairs for file: %s\n\n ", Filename);
	print_table(CharSet_N, CharSet_N, &CharSet[0], &CharSet[0], &Freq2[0][0]);

	//generate triads
	Freq3Count(Freq3, data);
	//	print_table(CharSet_N, CharSet_N, &CharSet[0], &CharSet[0], &Freq3[14][0][0]);

	Freq4Count(Freq4, data);
		// Success
	fclose(pFile);
	return true;
}



/*==========================================================================*\
| Date Created: 2017 DEC 12
| Date Revised:
|
| This function descibes the program to the user, then asks them if they wish
| to go on.
\*==========================================================================*/

bool welcome()
{
	printf("This program is designed to randomly print letters in an attempt to generate\n"
		"meaningful text. There are three different monkeys, each\n"
		"one being more sophisticated than the prior.\n\n"
		"Monkey 1 simply takes %i characters and prints them, each having an equal chance.\n\n"
		"Monkey 2 takes a file that it will base the distribution of letters off of.\n\n"
		"Monkey 3 looks at all %i possible combinations of letter pairs and uses that to base the print off of.\n\n"
		"Monkey 4 looks at all %i possible combinations of letter triads and uses that to base the print off of.\n"
		"\n\nThe program is crrently configured to use\nthe following charachter set: ", CharSet_N, CharSet_N * CharSet_N, CharSet_N * CharSet_N * CharSet_N);
	printf(CharSet);
	printf("\n\nPress Enter to continue or any other key to exit.\n");
	int key;
	key = getchar();
	if (key == '\n')
		return true;
	return false;
}


/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function is the main.
\*==========================================================================*/

int main()
{
	PlaySound(TEXT("C:\\Windows\\Media\\Windows Logon Sound.wav"),NULL, SND_NODEFAULT | SND_ASYNC);

	if (!SetConsole_simple())
		printf("Console size couldnt not be set.\n");

	srand(time(NULL));

	assert(CharSet[0] != 0);

	if (!welcome())
		return 0;

	//this is where we analyze
    static int
		Freq[CharSet_N],
		Freq2[CharSet_N][CharSet_N],
		Freq3[CharSet_N][CharSet_N][CharSet_N],
		Freq4[CharSet_N][CharSet_N][CharSet_N][CharSet_N];
	if (!LearnLanguage(Freq, Freq2, Freq3, Freq4))
		return 0;

	// this is where you pick a monkey
	while (process(Freq, Freq2, Freq3, Freq4))
		;

	return 1;
}


