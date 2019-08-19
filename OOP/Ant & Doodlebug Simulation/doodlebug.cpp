/*

 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#include "doodlebug.hpp"

Doodlebug::Doodlebug() : Critter()
{
	species = 'X';
	since_eaten = 0;
}

Doodlebug::Doodlebug(const int passed_x, const int passed_y, const int passed_start) : Critter(passed_x, passed_y, passed_start) //dbug to Critter equivalence relation
{
	species = 'X';
	since_eaten = passed_start;
}

Doodlebug::Doodlebug(const Doodlebug& dbug) : Critter(dbug)
{
	species = 'X';
	since_eaten = dbug.get_eaten();
}

const int Doodlebug::get_eaten() const
{
	return since_eaten;
}

void Doodlebug::move(game_board& board)
{
	if_moved = true; //1 move per step

	if ((x - 1) >= 0 && board.check_location((x - 1), y) && since_eaten != 0)		//eats ant if it is nearby and one at a time
	{
		if (board.check_location((x - 1), y)->get_species() == 'O') //if the nearby critter is a ant it is eaten
		{
			x--;
			since_eaten = 0; 	//eaten
			board.move_critters(*this, (x + 1), y); //send critter and previous location to move_critters
		}
	}

	if ((x + 1) < 20 && board.check_location((x + 1), y) && since_eaten != 0)
	{
		if (board.check_location((x + 1), y)->get_species() == 'O')
		{
			x++;
			since_eaten = 0;
			board.move_critters(*this, (x - 1), y);
		}
	}

	if ((y - 1) >= 0 && board.check_location(x, (y - 1)) && since_eaten != 0)
	{
		if (board.check_location(x, (y - 1))->get_species() == 'O')
		{
			y--;
			since_eaten = 0;
			board.move_critters(*this, x, (y + 1)); //pass the old location of dbug to board to have it removed from board
		}
	}

	if ((y + 1) < 20 && board.check_location(x, (y + 1)) && since_eaten != 0)
	{
		if (board.check_location(x, (y + 1))->get_species() == 'O')
		{
			y++;
			since_eaten = 0;
			board.move_critters(*this, x, (y - 1));
		}
	}

	if(since_eaten != 0)		//doodlebug doesn't move if it's already eaten
	{
		int direction = 1 + (rand() % 4);

		if(direction == 1) //down
		{
			y--;	//possible y position
			if((y >= 0) && board.check_location(x, y) == false)
				board.move_critters(*this, x, (y + 1));	//move the dbug to location
			else
				y++;
		}

		if(direction == 2) //up
		{
			y++;
			if ((y < 20) && board.check_location(x, y) == false)
				board.move_critters(*this, x, (y - 1));
			else
				y--;

		}

		if(direction == 3) //left
		{
			x++;
			if ((x < 20) && board.check_location(x, y) == false)
				board.move_critters(*this, (x - 1), y);
			else
				x--;

		}

		if(direction == 4) //right
		{
			x--;
			if ((x >= 0) && board.check_location(x, y) == false)
				board.move_critters(*this, (x + 1), y);
			else
				x++;
		}
	}
}

bool Doodlebug::breed(game_board& board) const
{
	if (((board.game_start() - start) != 0) && (((board.game_start() - start) % 8) == 0)) //breed if it's 8
	{
		if(((y - 1) >= 0) && (board.check_location(x, (y - 1)) == false))
		{
			Doodlebug dbug(x, (y - 1), 0);
			board.breed_critters(dbug);	//breed new dbug to the board
			return true;
		}
		else if(((y + 1) < 20) && (board.check_location(x, (y + 1)) == false))
		{
			Doodlebug dbug(x, (y + 1), 0);
			board.breed_critters(dbug);
			return true;
		}
		else if(((x - 1) >= 0) && (board.check_location((x - 1), y) == false))
		{
			Doodlebug dbug((x - 1), y, 0);
			board.breed_critters(dbug);
			return true;
		}
		else if (((x + 1) < 0) && (board.check_location((x + 1), y) == false))
		{
			Doodlebug dbug((x + 1), y, 0);
			board.breed_critters(dbug);
			return true;
		}
	}

	return false; 
}

const bool Doodlebug::starve(const game_board& board) const	//returns if dbug starves and made virtual because the type the game_grid uses is unknown and could be any critter
{
	return (since_eaten >= 3);
}

void Doodlebug::inc_eaten()	//exclusive use for doodlebug class
{
	since_eaten++;
}
