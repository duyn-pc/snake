// game.h
#include <vector>
#include <stdlib.h>
#include <Windows.h>

class Game
{
public:
	// Board param
	int width;
	int height;
	int size;
	int top_buffer;
	int bot_buffer;
	int starting_position;
	wchar_t* board;
	// Gameplay param
	bool food;
	int score;

	// Default constructor
	void initialize();

	// Clears the screen and draws the top, side, and bottom borders
	void restart();

	/* Drops food on any free space on the board. */
	void spawn_food();

	// Displays the game on the console screen
	void render();

private:
	HANDLE console;
	DWORD chars_written;
	CONSOLE_SCREEN_BUFFER_INFO csbi_info;
};
