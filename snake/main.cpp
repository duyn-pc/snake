// main.cpp
#include <iostream>
#include <conio.h>
#include <stdlib.h>  
#include <time.h> 
#include <Windows.h>

#include "snake.h"

int main()
{
	// Windows Console Setup
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	DWORD charsWritten = 0;
	HANDLE Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
											   NULL, CONSOLE_TEXTMODE_BUFFER,
											   NULL);
	SetConsoleActiveScreenBuffer(Console);
	if (!GetConsoleScreenBufferInfo(Console, &csbiInfo)) {
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
		return 0;
	}

	// Game screen setup, csbiInfo is the size of the current console window
	const int screenWidth = csbiInfo.dwSize.X;
	const int screenHeight = csbiInfo.dwSize.Y;
	const int screenSize = screenWidth * screenHeight;
	const int topBuffer = screenWidth * 2;
	const int bottomBuffer = screenSize - screenWidth;
	wchar_t* screen = new wchar_t[screenSize * 2];

	// Drawing the borders. Make class of this later
	for (int i = 0; i < screenSize; i++) screen[i] = L' ';
	for (int i = screenWidth; i < topBuffer; i++) screen[i] = L'#';
	for (int i = screenWidth; i < bottomBuffer; i++) {
		if ((i % screenWidth == 0) || (i % screenWidth == screenWidth - 1)) {
			screen[i] = L'#';
		}
	}
	for (int i = bottomBuffer; i < screenSize; i++) {
		screen[i] = L'#';
	}
	wsprintf(&screen[topBuffer + 1], L"S N A K E");

	// Keyboard Controls
	int keyPress = 0;
	const int UP = 72;
	const int DOWN = 80;
	const int LEFT = 75;
	const int RIGHT = 77;

	// Initialize Snake  
	srand(time(NULL));
	Snake snake(true, false, RIGHT, 0, (screenSize / 2) + 4);
	snake.draw(screen);
	snake.spawn_food(screen, screenWidth, bottomBuffer);

	// Output game screen to console
	WriteConsoleOutputCharacter(Console, screen, 
								screenSize, { 0,0 }, 
								&charsWritten);

	// Game Loop
	while (snake.is_alive()) {
		// Input Stage
		if (_kbhit()) keyPress = _getch();
		switch (keyPress) {
			case UP:
				snake.change_direction(UP);
				break;
			case RIGHT:
				snake.change_direction(RIGHT);
				break;
			case DOWN:
				snake.change_direction(DOWN);
				break;
			case LEFT:
				snake.change_direction(LEFT);
				break;
			default:
				break;
		}
		// Update Stage
		switch (snake.set_direction()) {
		case 72:
			Sleep(500); 
			break;
		case 80:
			Sleep(500); 
			break;
		default:
			Sleep(100);
			break;
		}
		snake.move(screenWidth);
		snake.detect_collision(screen);
		snake.draw(screen);
		if (!snake.food_active()) snake.spawn_food(screen, 
											       screenWidth, 
											       bottomBuffer);
		wsprintf(&screen[1], L"S C O R E : %d", snake.set_score()); 
		// Render Stage
		WriteConsoleOutputCharacter(Console, screen,
									screenSize, { 0,0 },
									&charsWritten);
	}
	wsprintf(&screen[topBuffer + 1], L"G A M E  O V E R !!");
	WriteConsoleOutputCharacter(Console, screen,
								screenSize, { 0,0 },
								& charsWritten);
	while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
}

