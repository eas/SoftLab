#include <fstream>
#include <assert.h>
#include "2d_array.h"
#include "map.h"

#include "game.h"
#include "enemy.h"
#include "hero.h"

#include "console.h"

int Test()
{
	ns_2d::Array<int> my_array1, my_array2(5, 5), my_array3(5, 5, 10);
	my_array1.Swap(my_array2);
	const ns_2d::Array<int> my_array = my_array1;
	int x = my_array(0, 0);
	x = my_array1(0, 0);
	x = my_array[ns_2d::Coords(0,0)];
	x = my_array1[ns_2d::Coords(0,0)];
	return 0;
}

//TODO: Exit code

int main()
{
	//Test();
	//game::Map map;
	//std::fstream ifs( "my_map.txt", std::ios::in );
	//assert( !ifs.bad() );
	//ifs >> map;
	//std::fstream ofs( "my_map.buk", std::ios::out );
	//ofs << map;
	//Console::PutChar('1');
	//Console::PutChar('2');
	//Console::GotoXY(5, 5);
	//Console::PutChar('3');
	//while( !Console::IsKeyPressed() )
	//{
	//}
	//int ch = Console::GetPressedKey();
	//Console::GotoXY(6, 5);
	//Console::PutChar(ch);

	game::Game game;
	game::View view(game);
	game.LoadMap("my_map.txt");
	game.Start();

	return 0;
}