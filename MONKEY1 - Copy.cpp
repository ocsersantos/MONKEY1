// MONKEY1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <Windows.h>
#include <Winbase.h>
#include <conio.h>

// Specify characters of interest 
const char CharSet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ' " };//THERE MUST BE A SPACE
const int CharSet_N = sizeof(CharSet) / sizeof(char) - 1;	// Number of characters in set (don't count null)

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

bool OpenFile(wchar_t szFile[], int Size)
{
	OPENFILENAME ofn;

	// open a file name
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
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

int GetRand(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}

bool iswhitespace(int c)
{
	return c == ' ' || c == '\n' || c == '\t';
}

bool PreProcessFile(FILE *pFile, char Data[], int datacount)
{
	memset(Data, 0, datacount * sizeof (char));

	if (datacount < 1)
		return false;
	int Numdatachars = 0;
	bool EraseMode = false;
	// Process one line at a time
	int c = '0', last_c = '\n', orig_c;
	for (;;	last_c = orig_c)
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
			if(Numdatachars != 0 && iswhitespace(Data[Numdatachars-1]))
				continue;
		}
	
		//insert char
		if (Numdatachars == datacount-1)
		{
			printf("Data array is too small, try again with a smaller file.\n");
			return false; 
		}
		Data[Numdatachars] = c;
		(Numdatachars)++;
	}


}



void FreqCount( int Freq[], const char Data[])
{
	// Zero counts
	memset(Freq, 0, CharSet_N * sizeof(int));

	int j = 0;
	// Scan adjusted line, counting each char in CharSet (case insensitive)
	while (Data[j] != '\0')
	{
		// Look for char in set and inc its freq counter if found
		int idx = FindChar(Data[j]);
		if(idx != -1)
			Freq[idx]++;	
		// Next
		j++;
	}
}

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



bool Monkey1(FILE *pFile)
{
	int i;
	for (i = 0; true; i++)
	{
		char c = CharSet[GetRand(0, CharSet_N - 1)];
		//Sleep(50);
		printf("%c", c);
		if (fprintf(pFile, "%c", c) != 1)
		{
			printf("MONKEY RAN OUT OF PAPER\n");
			return false;
		}
		if (_kbhit())
			break;
	}
	printf("\n%d letters were printed.\n", i);
	return true;
}

bool Monkey2(FILE *pFile, const int Freq[])
{
//	char set[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ' " };

//	int freq[] = { 2043, 410, 584, 1099, 3277, 629 , 478, 1773, 1736, 34, 255, 1238, 889, 1741, 2578, 433, 27, 1593, 1856, 2557, 1014, 309, 716, 21, 783, 14, 203, 6934};

	//count total letters
	int total = 0, i;
	for ( i = 0; i < CharSet_N; i++)
		total += Freq[i];

	for (i = 0; true; i++)
	{
		int key = GetRand(0, total-1);
		//Sleep(50);
		char c = -1;
		for (int i = 0; i < CharSet_N; i++)
		{
			if (key < Freq[i])
			{
				c = CharSet[i];
				break;
			}
			key -= Freq[i];
		}

		assert(c != -1);
		printf("%c", c);
		if (fprintf(pFile, "%c", c) != 1)
		{
			printf("MONKEY RAN OUT OF PAPER\n");
			return false;
		}
		
		if (_kbhit())
			break;
	}
	printf("\n%d letters were printed.\n", i);
	return true;
} 

bool Monkey3(FILE *pFile, const int Freq[])
{

	return false;
}

bool process(int Freq[])
{
	errno_t code;
	FILE *pFile;
	int m;
	printf("\nSelect monkey 0(to quit), 1, 2, or 3: ");
	scanf_s("%d", &m);
	char Bookname[500] = "F:\\Benjamin\\Programs\\MONKEY1\\book";

	switch (m)
	{
	 default:
		return false;

	case 1:
		strcat_s(Bookname, sizeof(Bookname), "1.txt");
		break;

	case 2:
		strcat_s(Bookname, sizeof(Bookname), "2.txt");
		break;

	case 3:
		strcat_s(Bookname, sizeof(Bookname), "3.txt");
		break;
	}
	
	code = fopen_s(&pFile, Bookname, "w");
	if (code != 0)
	{
		printf("failed to open\n");
		return false;
	}

	switch (m)
	{
	case 1:
		if (!Monkey1(pFile))
		{
			fclose(pFile);
			return false;
		}
		break;

	case 2:
		if (!Monkey2(pFile, Freq))
		{
			fclose(pFile);
			return false;
		}
		break;

	case 3:
		if (Monkey3(pFile, Freq))
		{
			fclose(pFile);
			return false;
		}
		break;
	}
	
	fclose(pFile);
	return true;
}

bool LearnLanguage(int Freq[], int Freq2[CharSet_N][CharSet_N])
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
	char data[100000];
	if (!PreProcessFile(pFile, data, _countof(data)))
	{
		printf("Cannot process file");
		Sleep(2000);
		fclose(pFile);
		return false;
	}
	//printf(data);
	FreqCount(Freq, data);

	// Display results
	wprintf(L"Character frequencies for file: %s", Filename);
	printf("\n\n");
	for (int i = 0; i < CharSet_N; i++)
		printf("Char %c %i\n", CharSet[i], Freq[i]);


	Freq2Count(Freq2, data);
	// Display results
	wprintf(L"Character frequency pairs for file: %s", Filename);
	printf("\n\n");
	for (int i = 0; i < CharSet_N; i++)
	{
		for (int j = 0; j < CharSet_N; j++)
		{
			printf("%2i ", Freq2[i][j]);
		}
		printf("\n");
	}
	// Success
	fclose(pFile);
	return true;
}


int main()
{


	srand(time(NULL));


	assert(CharSet[0] != 0);

	//this is where we analyze
	int
		Freq[CharSet_N], Freq2[CharSet_N][CharSet_N];
	if (!LearnLanguage(Freq, Freq2))
		return 0;

	// this is where you pick a monkey
	while (process(Freq))
		;

	return 1;
}

