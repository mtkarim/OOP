/*

 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#include "critter.hpp"
#include "game_board.hpp"

Critter::Critter()
{
	x = 0;
	y = 0;
	start = 0;
	if_moved = false;
}

Critter::Critter(int passed_x, int passed_y, int passed_start)
{
	x = passed_x;
	y = passed_y;
	start = passed_start;
	if_moved = false;
}

Critter::Critter(const Critter &other)
{
	x = other.get_x();
	y = other.get_y();
	start = other.game_start();
	if_moved = other.has_moved();
}

Critter::~Critter() //this is needed for inheritence
{}

void Critter::move(game_board& board) //this always overrides
{}

bool Critter::breed(game_board& board) const //this always overrides
{
	return false;
}

const bool Critter::starve(const game_board& board) const //overidden by doodlebug
{
	return false;
}

void Critter::inc_eaten() //only every used/overriden by doodlebug
{}

const int Critter::game_start() const
{
	return start;
}

const char Critter::get_species() const
{
	return species;
}

const int Critter::get_x() const
{
	return x;
}

const int Critter::get_y() const
{
	return y;
}

const bool Critter::has_moved() const //return whether critter has moved this time step or not
{
	return if_moved;
}

void Critter::next_time_step() //new time step
{
	if_moved = false;
}
