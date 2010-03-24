#pragma once

class Console // has only static methods
{
public:
	typedef int Key;
public:
	static bool IsKeyPressed();
	static Key GetPressedKey();
	static void GotoXY(unsigned x, unsigned y);
	static void Write(char ch);
private:
	Console();
};

namespace keys
{
	const Console::Key esc = 27;
	const Console::Key right = 1;
	const Console::Key left = 2;
	const Console::Key down = 3;
	const Console::Key up = 4;
}