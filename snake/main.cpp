// main.cpp
#include <iostream>
#include <conio.h>
#include <stdlib.h>  
#include <time.h> 
#include <Windows.h>

#include "snake.h"
#include "game.h"

int main()
{
	// Initialize game board
	Game game;
	game.initialize();
	game.restart();
	game.spawn_food();

	// Initialize player  
	Snake player(game.starting_position);
	player.draw(game.board);

	// Keyboard Controls
	int keyPress = 0;
	const int UP = 72;
	const int DOWN = 80;
	const int LEFT = 75;
	const int RIGHT = 77;

	// Game Loop
	while (player.alive) {
		// Input Stage
		if (_kbhit()) keyPress = _getch();
		switch (keyPress) {
		case UP:
			player.change_direction(UP);
			break;
		case RIGHT:
			player.change_direction(RIGHT);
			break;
		case DOWN:
			player.change_direction(DOWN);
			break;
		case LEFT:
			player.change_direction(LEFT);
			break;
		default:
			break;
		}
		// Update Stage
		switch (player.direction) {
		case 72:
			Sleep(200);
			break;
		case 80:
			Sleep(200);
			break;
		default:
			Sleep(100);
			break;
		}
		player.move(game.width);
		player.detect_collision(game.board, game.food, game.score);
		player.draw(game.board);
		if (!game.food) game.spawn_food();
		wsprintf(&game.board[1], L"S C O R E : %d", game.score);
		// Render Stage
		game.render();
	}
	wsprintf(&game.board[game.starting_position + game.width / 2],
		     L"G A M E  O V E R !!");
	game.render();
	while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
}

