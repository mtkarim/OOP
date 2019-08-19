/*

 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "critter.hpp"
#include "game_board.hpp"

class Doodlebug : public Critter	//class doodlebug inherited with public class critter
{
	public:
		Doodlebug();
		Doodlebug(const int passed_x, const int passed_y, const int passed_start);
		Doodlebug(const Doodlebug& dbug);
		void move(game_board& board) override;
		bool breed(game_board& board) const override;
		const bool starve(const game_board& board) const override;	//only used by doodlebug
		void inc_eaten() override;
		const int get_eaten() const;		//only for doodlebug
	private:
		int since_eaten;
};

#endif
