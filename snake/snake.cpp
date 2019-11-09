// snake.cpp
#include "snake.h"

// Constructor
Snake::Snake(bool newStatus, bool foodStatus,
	         int newDirection, int newScore,
	         int snakeCoord)
{
	alive = newStatus;
	food = foodStatus;
	direction = newDirection;
	score = newScore;
	body.push_front(snakeCoord);
}

// Planned to be used by screen to draw the snake
bool Snake::is_alive()
{
	return alive;
}
bool Snake::food_active()
{
	return food;
}
bool Snake::set_direction()
{
	return direction;
}
int Snake::set_score()
{
	return score;
}

//Change snake direction based on key press.
void Snake::ChangeDirection(int keyPress)
{
	switch (keyPress)
	{
	case 72: // Up
		if ((direction == 72) ||
			(direction == 80)) break;
		direction = 72;
		break;
	case 77: // Right
		if ((direction == 77) ||
			(direction == 75)) break;
		direction = 77;
		break;
	case 80: // Down
		if ((direction == 80) ||
			(direction == 72)) break;
		direction = 80;
		break;
	case 75: // Left
		if ((direction == 75) ||
			(direction == 77)) break;
		direction = 75;
		break;
	default:
		break;
	}
}

/* Adds the coordinates of the next snake block to the start of the list */
void Snake::MoveSnake(int moveDistance)
{
	switch (direction)
	{
	case 72: // Up
		body.push_front(body.front() - moveDistance);
		break;
	case 77: // Right
		body.push_front(body.front() + 1);
		break;
	case 80: // Down
		body.push_front(body.front() + moveDistance);
		break;
	case 75: // Left
		body.push_front(body.front() - 1);
		break;
	default:
		break;
	}
}

/* Ends game if snake encounters border or itself.
	If there are no obstacles, snake will chop its tail to move forward.
	If food is encountered, snake will not chop its tail.
*/
void Snake::DetectCollision(wchar_t* screen)
{
	wchar_t obstacle = screen[body.front()];
	if ((obstacle == L'#') ||
		(obstacle == L'8')) alive = false;
	else if (obstacle == L' ')
	{
		screen[body.back()] = L' ';
		body.pop_back();
	}
	else
	{
		food = false;
		score = score + 10;
	}
}

/* Draws the head of the snake on the screen. */
void Snake::DrawSnake(wchar_t* screen)
{
	screen[body.front()] = L'8';
}

/* Drops food on any free space on the screen. */
void Snake::SpawnFood(wchar_t* screen,
	                  const int screenWidth,
	                  const int bottomBuffer)
{
	while (!food)
	{
		// Random location between top and bottom buffer
		int foodCoord = (rand() % (bottomBuffer - screenWidth)) + screenWidth * 3;
		if (screen[foodCoord] == L' ')
		{
			food = true;
			screen[foodCoord] = L'O';
		}
	}
}
