#pragma once
bool SetConsole_simple(void);
void print_table(int row, int col, const char *pColHeader, const char *pRowHeader, const int *pTable);


/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function gets a random number betweeen a specified range.
\*==========================================================================*/

inline int GetRand(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function returns true if the specified charachter is a whitespace
|charachter.
\*==========================================================================*/

inline bool iswhitespace(int c)
{
	return c == ' ' || c == '\n' || c == '\t';
}
