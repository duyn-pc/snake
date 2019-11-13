// game.cpp
#include "game.h"

// Default constructor
void Game::initialize()
{
	// Board param init
	chars_written = 0;
	console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
		NULL, CONSOLE_TEXTMODE_BUFFER,
		NULL);
	SetConsoleActiveScreenBuffer(console);
	if (!GetConsoleScreenBufferInfo(console, &csbi_info)) {
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
		exit(EXIT_FAILURE);
	}
	width = csbi_info.dwSize.X;
	height = csbi_info.dwSize.Y;
	size = width * height;
	top_buffer = width * 2;
	bot_buffer = size - width;
	board = new wchar_t[size * 2];
	starting_position = size / 2 + 1;

	// Gameplay param init
	food = false;
	score = 0;
}

// Clears the screen and draws the top, side, and bottom borders
void Game::restart()
{
	for (int i = 0; i < size; i++) board[i] = L' ';
	for (int i = width; i < top_buffer; i++) board[i] = L'#';
	for (int i = width; i < bot_buffer; i++) {
		if ((i % width == 0) || (i % width == width - 1)) board[i] = L'#';
	}
	for (int i = bot_buffer; i < size; i++) board[i] = L'#';
}

/* Drops food on any free space on the board. */
void Game::spawn_food()
{
	while (!food)
	{
		// Random location between top and bottom buffer
		int food_coord = (rand() % (bot_buffer - width)) + width * 3;
		if (board[food_coord] == L' ')
		{
			food = true;
			board[food_coord] = L'O';
		}
	}
}

// Displays the game on the console screen
void Game::render()
{
	WriteConsoleOutputCharacter(console, board,
								size, { 0,0 },
								&chars_written);
}