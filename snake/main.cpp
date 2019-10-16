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
	HANDLE Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
											   NULL, CONSOLE_TEXTMODE_BUFFER,
											   NULL);
	SetConsoleActiveScreenBuffer(Console);
	DWORD charsWritten = 0;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	if (!GetConsoleScreenBufferInfo(Console, &csbiInfo))
	{
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
	for (int i = screenWidth; i < bottomBuffer; i++)
	{
		if ((i % screenWidth == 0) || (i % screenWidth == screenWidth - 1))
		{
			screen[i] = L'#';
		}
	}
	for (int i = bottomBuffer; i < screenSize; i++)
	{
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
	snake.DrawSnake(screen);
	snake.SpawnFood(screen, screenWidth, bottomBuffer);

	// Output game screen to console
	WriteConsoleOutputCharacter(Console, screen, 
								screenSize, { 0,0 }, 
								&charsWritten);

	// Game Loop
	while (snake.isAlive())
	{
		// Input Stage
		if (_kbhit()) keyPress = _getch();
		switch (keyPress)
		{
			case UP:
				snake.ChangeDirection(UP);
				break;
			case RIGHT:
				snake.ChangeDirection(RIGHT);
				break;
			case DOWN:
				snake.ChangeDirection(DOWN);
				break;
			case LEFT:
				snake.ChangeDirection(LEFT);
				break;
			default:
				break;
		}
		// Update Stage
		switch (snake.giveDirection())
		{
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
		snake.MoveSnake(screenWidth);
		snake.DetectCollision(screen);
		snake.DrawSnake(screen);
		if (!snake.foodActive()) snake.SpawnFood(screen, 
											     screenWidth, 
											     bottomBuffer);
		wsprintf(&screen[1], L"S C O R E : %d", snake.giveScore()); 
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

