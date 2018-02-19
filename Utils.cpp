#include "stdafx.h"
#include "math.h"
#include <Windows.h>
#include <Winbase.h>



/*==========================================================================*\
| Date Created: 2017 DEC 11
| Date Revised:
|
| This function sets the size of the console window to be big enough to display
|everything.
\*==========================================================================*/

bool SetConsole_simple(void)
{
	HANDLE
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE || h == NULL)
		return false;

	CONSOLE_SCREEN_BUFFER_INFO
		CSBI;
	if (GetConsoleScreenBufferInfo(h, &CSBI) == 0)
		return false;// _T( "Could not obtain console screen buffer information." );

					 // Increase the number of lines to 5000
	COORD
		bSize;
	bSize.X = 200;
	bSize.Y = 5000;
	if (!SetConsoleScreenBufferSize(h, bSize))
		return false; //AfxMessageBox( _T( "Could not change the size of the consols's screen buffer." ) );
	if (GetConsoleScreenBufferInfo(h, &CSBI) == 0)
		return false;
	// Set window size
	SMALL_RECT
		Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = CSBI.dwMaximumWindowSize.Y * 8 / 10;	// 80 % of maximum vertical
	Rect.Right = CSBI.dwMaximumWindowSize.X * 999 / 1000;
	if (!SetConsoleWindowInfo(h, TRUE, &Rect))
		return false; //AfxMessageBox( _T( "Could not change the console window size" ) );

					  /*	HWND
					  hWnd = GetConsoleHWND();
					  if( hWnd != NULL )
					  {
					  // Disable the close button (if left enabled, the entire application will close if selected).
					  HMENU
					  hMenu = ::GetSystemMenu( hWnd, FALSE );
					  EnableMenuItem( hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED );

					  // Position the window
					  CRect
					  CurrentRect;
					  if( GetWindowRect( hWnd, &CurrentRect ) )
					  {
					  // Move to top right
					  int
					  screenWidth = ::GetSystemMetrics( SM_CXSCREEN ),
					  screenHeight = ::GetSystemMetrics( SM_CYSCREEN ),
					  x = screenWidth - CurrentRect.Width(),
					  y = 0;
					  if( !SetWindowPos( hWnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER ) )
					  {
					  AfxMessageBox( _T( "Could not set window position." ) );
					  }
					  }
					  else
					  {
					  AfxMessageBox( _T( "Could not get window position." ) );
					  }
					  }
					  */
	return true;
}

void print_table(int row, int col, const char *pColHeader, const char *pRowHeader, const int *pTable)
{
	// Display results
	for (int j = 0; j < col; j++)
		printf("%4c ", *(pColHeader + j));
	printf("\n");
	for (int i = 0; i < row; i++)
	{
		int total = 0;
		printf("%c", *(pRowHeader + i));
		for (int j = 0; j < col; j++)
		{
			int val = *(pTable + i * row + j);
			printf("%4i ", val);
			total += val;
		}
		printf("%i\n", total);
	}
}