// snake.h
#include <iostream>
#include <list>

class Snake
{
	bool alive;
	bool food;
	int direction;
	int score;
	std::list<int> body;

public:
	Snake(bool newStatus, bool foodStatus,
		  int newDirection, int newScore,
		  int snakeCoord);

	// Return various attributes of the snake object
	bool is_alive();
	bool food_active();
	bool set_direction();
	int set_score();

	//Change snake direction based on key press.
	void ChangeDirection(int keyPress);

	/* Adds the coordinates of the next snake block to the start of the list */
	void MoveSnake(int moveDistance);

	/* Ends game if snake encounters border or itself.
	   If there are no obstacles, snake will chop its tail to move forward.
	   If food is encountered, snake will not chop its tail.
	*/
	void DetectCollision(wchar_t* screen);

	/* Draws the head of the snake on the screen. */
	void DrawSnake(wchar_t* screen);

	/* Drops food on any free space on the screen. */
	void SpawnFood(wchar_t* screen,
				   const int screenWidth,
				   const int bottomBuffer);
};
