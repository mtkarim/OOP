/*

 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#include "ant.hpp"
#include "doodlebug.hpp"
#include "game_board.hpp"

#include <time.h>

game_board::game_board()	//creates a null world
{
	int columns = 20;	//sets column to 20
	int rows = 20;		//sets rows to 20
	t_step = 0;			//sets time steps to 0
	starved_dbug = 0;	//sets doodlebugs that starved to 0
	dbugs_born = 0;	//sets starting doodlebug to 0
	ants_born = 0;	//sets starting ants to 0
	ants_eaten = 0;		//sets ants eaten to 0
	num_ants = 0;		//sets total ants to 0
	num_dbugs = 0;	//sets total doodlebugs to 0

	srand(time(NULL)); //used for timing/steps of game_board

	for (int a = 0; a < rows; a++)
	{
		for (int b = 0; b < columns; b++)
		{
			game_grid[a][b] = nullptr; //shown on board as a *
		}
	}

	while (num_dbugs < 5) //5 doodlebugs are added to the board
	{
		int a = (rand() % rows);
		int b = (rand() % columns);

		if(check_location(a, b) == false)	//checks to see if there isn't already an existing dbug
		{
			game_grid[a][b] = new Doodlebug(a, b, 0);
			num_dbugs++;
		}
	}

	while (num_ants < 100)	//100 ants are added to the board
	{
		int c = (rand() % rows);
		int d = (rand() % columns);

		if(check_location(c, d) == false)
		{
			game_grid[c][d] = new Ant(c, d, 0);
			num_ants++;
		}
	}
}

game_board::~game_board()		//this is used to delete the game from memory
{
	for(int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			delete game_grid[i][j];
}

void game_board::time_step()
{
	starved_dbug = 0;
	dbugs_born = 0;
	ants_born = 0;
	ants_eaten = 0;
	bool sim = false;		//used to check if critters were bred

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (check_location(i, j))
			{
				game_grid[i][j]->next_time_step();
			}
		}
	}

	for (int i = 0; i < 20; i++)		//for loop for doodlebugs
	{
		for (int j = 0; j < 20; j++)
		{
			if (check_location(i, j))
			{
				if (game_grid[i][j]->get_species() == 'X' && game_grid[i][j]->has_moved() == false)
				{
					game_grid[i][j]->move(*this);
				}
			}
		}
	}

	for (int i = 0; i < 20; i++)		//for loop for ants
	{
		for (int j = 0; j < 20; j++)
		{
			if (check_location(i, j))
			{
				if (game_grid[i][j]->get_species() == 'O' && game_grid[i][j]->has_moved() == false)
				{
					game_grid[i][j]->move(*this);
				}
			}
		}
	}

	for (int i = 0; i < 20; i++)		//for loop for breeding ants
	{
		for (int j = 0; j < 20; j++)
		{
			if (check_location(i, j))
			{
				if (game_grid[i][j]->get_species() == 'O')
				{
					sim = game_grid[i][j]->breed(*this); //checks if it has been 3 time steps
					if (sim)
					{
						num_ants++;
						ants_born++;
					}
					sim = false;
				}
			}
		}
	}

	for (int i = 0; i < 20; i++)		//for loop for breeding doodlebugs
	{
		for (int j = 0; j < 20; j++)
		{
			if (check_location(i, j))
			{
				if (game_grid[i][j]->get_species() == 'X')
				{
					sim = game_grid[i][j]->breed(*this); //checks if it has been 8 time steps
					if (sim)
					{
						num_dbugs++;
						dbugs_born++;
					}
					sim = false;
				}
			}
		}
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (check_location(i, j))
			{
				if (game_grid[i][j]->get_species() == 'X')
				{
					if (game_grid[i][j]->starve(*this))
					{
						num_dbugs--;
						starved_dbug++;
						delete game_grid[i][j];
						game_grid[i][j] = nullptr;
					}
				}
			}
		}
	}

	for (int i = 0; i < 20; i++)	//increments steps since eaten for doodlebugs
	{
		for (int j = 0; j < 20; j++)
		{
			if (check_location(i, j))
			{
				if (game_grid[i][j]->get_species() == 'X')
				{
					game_grid[i][j]->inc_eaten();
				}
			}
		}
	}
	t_step++;
}

const int game_board::game_start() const
{
	return t_step;
}

const int game_board::tot_ants() const
{
	return num_ants;
}

const int game_board::tot_dbugs() const
{
	return num_dbugs;
}

void game_board::delete_critter(int passed_x, int passed_y)	//deletes critter from location
{
	delete game_grid[passed_x][passed_y];
	game_grid[passed_x][passed_y] = nullptr;
}

const Critter* game_board::check_location(const int x, const int y) const	//nullptr returned if point on board is null otherwise critter is returned
{
	return game_grid[x][y];
}

void game_board::display_board()	//this displays the game board
{
	std::cout << std::endl;
	for(int a = 0; a < 20; a++)
	{
		for (int b = 0; b < 20; b++)
		{
			if(game_grid[a][b] != nullptr)
				std::cout << game_grid[a][b]->get_species();
			else
				std::cout << '*';
			std::cout << ' ';
		}
		std::cout << "\n";
	}
}

void game_board::display_stats()	//daily stats are displayed
{
	std::cout << "\nDay: " << t_step << "\n";
	std::cout << "Number of Ants: " << num_ants << "\n";
	std::cout << "Number of Doodlebugs: " << num_dbugs << "\n";
	std::cout << "Number of Ants born this day: " << ants_born << "\n";
	std::cout << "Number of Doodlebugs born this day: " << dbugs_born << "\n";
	std::cout << "Number of Ants eaten this day: " << ants_eaten << "\n";
	std::cout << "Number of Doodlebugs starved this day: " << starved_dbug << "\n\n";
}
