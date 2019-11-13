// snake.cpp
#include "snake.h"

Snake::Snake(int starting_coord)
{
	alive = true;
	direction = 77; //Right
	body.push_front(starting_coord);
	srand(time(NULL)); // Randomized seed for food spawn position
}

//Change snake direction based on key press.
void Snake::change_direction(int key_press)
{
	switch (key_press)
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
void Snake::move(int move_distance)
{
	switch (direction)
	{
	case 72: // Up
		body.push_front(body.front() - move_distance);
		break;
	case 77: // Right
		body.push_front(body.front() + 1);
		break;
	case 80: // Down
		body.push_front(body.front() + move_distance);
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
void Snake::detect_collision(wchar_t* board, bool food, int score)
{
	wchar_t obstacle = board[body.front()];
	if ((obstacle == L'#') ||
		(obstacle == L'8')) alive = false;
	else if (obstacle == L' ')
	{
		board[body.back()] = L' ';
		body.pop_back();
	}
	else
	{
		food = false;
		score += 10;
	}
}

/* Draws the head of the snake on the board. */
void Snake::draw(wchar_t* board)
{
	board[body.front()] = L'8';
}

