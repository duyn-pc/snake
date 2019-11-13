// snake.h
#include <iostream>
#include <list>
#include <time.h> 

class Snake
{
public:
	bool alive;
	int direction;

	// Constructor
	Snake(int starting_coord);

	//Change snake direction based on key press.
	void change_direction(int key_press);

	/* Adds the coordinates of the next snake block to the start of the list */
	void move(int move_distance);

	/* Ends game if snake encounters border or itself.
	   If there are no obstacles, snake will chop its tail to move forward.
	   If food is encountered, snake will not chop its tail.
	*/
	void detect_collision(wchar_t* board, bool food, int score);

	/* Draws the head of the snake on the board. */
	void draw(wchar_t* board);

private:
	std::list<int> body;
};
