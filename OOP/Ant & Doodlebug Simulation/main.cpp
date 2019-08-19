/*

 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#include <iostream>
#include <string>

#include "game_board.hpp"

int main()
{
	game_board board; //to call constructor
	std::string exit;	//this is placeholder
	bool game = true; 	//game simulation is continuous

	while(game)			//this while is continuous until the user exits
	{
		board.time_step();			//this increments time
		board.display_board();		//this displays the game board
		board.display_stats(); 	//this is used to display all stats

		std::cout << "Press Enter to Continue or Space to Exit: "; //prompts user to either continue or exit
		std::getline(std::cin, exit);
		if(exit == " ")
			game = false;
		std::cout << "\nYou have exited the predator-prey simulator.\n\n";
	}
	return 0;
}
