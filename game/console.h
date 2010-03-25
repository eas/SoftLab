#pragma once

class Console // has only static methods
{
public:
	static bool IsKeyPressed();
	static int GetPressedKey();
	static int GotoXY(short x, short y);
	static void PutChar(int ch);
private:
	Console();
};

namespace keys
{
	const int esc = 27;
	const int down = -77; //right = 
	const int up = -75;	//left =
	const int right = -80;
	const int left = -72;
}