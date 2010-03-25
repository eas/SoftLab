#include <wtypes.h>
#include <wincon.h>
#include <conio.h>

#include "console.h"

bool Console::IsKeyPressed()
{

	return 0 != _kbhit();
}

int Console::GetPressedKey()
{
	int ch = _getch();

	if (ch == 0 || ch == 224) // extended code
		return - _getch();

	return ch;}

BOOL Console::GotoXY(short x, short y)
{
	COORD pos = { x, y };

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleCursorPosition(hStdOut, pos);
}

void Console::PutChar(int ch)
{
	_putch(ch);
}