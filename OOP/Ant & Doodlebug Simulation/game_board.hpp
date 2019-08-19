/*

 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <iostream>

class Critter;	//this forward declares Critter so the board knows what type game board is

class game_board
{
public:
	game_board();	//default
	~game_board(); //destructor
	template <class TEMP>		//template used to make program more efficient
	void move_critters(const TEMP &critters_passed, const int passed_x, const int passed_y);
	template <class TEMP>
	void breed_critters(const TEMP &critters_passed); //used for breeding the critter to board
	const Critter* check_location(const int passed_x, const int passed_y) const; //used for returning the contents of location
	void delete_critter(int passed_x, int passed_y);
	const int game_start() const;
	const int tot_ants() const;
	const int tot_dbugs() const;
	void time_step(); 	//simulates next time step
	void display_board(); //outputs game board to the screen
	void display_stats(); //shows all stats for that "day"
private:
	Critter *game_grid[20][20]; //this is used to create a 2D array
	int t_step;
	int starved_dbug;
	int dbugs_born;
	int ants_born;
	int ants_eaten;
	int num_ants;
	int num_dbugs;
};

template <class TMP> //for easy assign and temp declaration defined here
void game_board::breed_critters(const TMP &critters_passed)
{
	game_grid[critters_passed.get_x()][critters_passed.get_y()] = new TMP (critters_passed);
}

template <class TMP> //for easy assign and temp declaration defined here
void game_board::move_critters(const TMP &critters_passed, const int passed_x, const int passed_y)
{
	if (check_location(critters_passed.get_x(), critters_passed.get_y()) != false)	//if dbug is not eating ant this is false
	{
		delete game_grid[critters_passed.get_x()][critters_passed.get_y()];
		num_ants--;
		ants_eaten++;
	}

	game_grid[critters_passed.get_x()][critters_passed.get_y()] = new TMP (critters_passed); 	//TMP is useful because we dont know the type

	delete_critter(passed_x, passed_y);		//critter from old location is deleted
}

#endif
