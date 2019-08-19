/*
 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#ifndef ANT_HPP
#define ANT_HPP

#include "critter.hpp"
#include "game_board.hpp"

class Ant : public Critter	//class ant inherited with public class critter
{
	public:					//used outside of the class since its public
		Ant();
		Ant(const int passed_x, const int passed_y, const int start);
		Ant(const Ant& passed_ant);
		void move(game_board& board) override;			//overrides virtual functions in the Critter
		bool breed(game_board& board) const override;
};

#endif
