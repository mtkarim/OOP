/*
 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#include "ant.hpp"

Ant::Ant() 		//default constructor
{
	species = 'O';
}

Ant::Ant(const int passed_x, const int passed_y, const int passed_start) : Critter(passed_x, passed_y, passed_start) //the relationship between ants and critters
{
	species = 'O';
}

Ant::Ant(const Ant& passed_ant) : Critter(passed_ant)
{
	species = 'O';
}

void Ant::move(game_board& board)
{
	if(board.game_start() != 0) 			//first time step
	{
		if_moved = true;

		int direction = 1 + (rand() % 4);	//used to pick a random direction

		if(direction == 1) 					//for down direction
		{
			y--;
			if ((y >= 0) && board.check_location(x, y) == false)		//if nothing is here it returns, because of nullptr
				board.move_critters(*this, x, (y + 1));
			else
				y++;
		}

		if(direction == 2) 					//for up direction
		{
			y++;
			if ((y < 20) && (board.check_location(x, y) == false))
				board.move_critters(*this, x, (y - 1));
			else
				y--;
		}

		if(direction == 3)
		{
			x++;
			if ((x < 20) && (board.check_location(x, y) == false))
				board.move_critters(*this, (x - 1), y);
			else
				x--;
		}

		if(direction == 4)
		{
			x--;
			if ((x >= 0) && (board.check_location(x, y) == false))
				board.move_critters(*this, (x + 1), y);
			else
				x++;
		}
	}
}

bool Ant::breed(game_board& board) const
{
	int check_1 = (board.game_start() - start);
	int check_2 = ((board.game_start() - start) % 3);

	if ((check_1 != 0) && (check_2 == 0)) 
	{
		if (board.check_location(x, (y - 1)) == false)
		{
			if((y - 1) >= 0)
			{
				Ant a(x, (y - 1), board.game_start()); 	//makes new ant
				board.breed_critters(a);			  	//breeds new ant to game board
				return true;
			}
		}
		else if (board.check_location(x, (y + 1)) == false)
		{
			if((y + 1) < 20)
			{
				Ant a(x, (y + 1), board.game_start());
				board.breed_critters(a);
				return true;
			}
		}
		else if (board.check_location((x - 1), y) == false)
		{
			if(((x - 1) >= 0))
			{
				Ant a((x - 1), y, board.game_start());
				board.breed_critters(a);
				return true;
			}
		}
		else if (board.check_location((x + 1), y) == false)
		{
			if((x + 1) < 0)
			{
				Ant a((x + 1), y, board.game_start());
				board.breed_critters(a);
				return true;
			}
		}
	}
	return false; 									//false is returned if there is no breeding
}
