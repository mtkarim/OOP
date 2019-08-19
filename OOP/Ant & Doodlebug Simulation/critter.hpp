/*

 * Assignment: 6
 * Description: You will be creating a predator-prey simulator, with ants and doodlebugs.
 */

#ifndef CRITTER_HPP
#define CRITTER_HPP

class game_board; //game_board is forward declared here in order for this to work

class Critter
{
protected:			//protected so derived class can use constructors and private data
		int start;	//first day for living organisms
		char species; //how to distinguish on board -- O = ANT, X = DOODLEBUG
		int x;		  //x position on board
		int y;		  //y position on board
		bool if_moved;   //to check if critter moves

		Critter();
		Critter(const int passed_x, const int passed_y, const int passed_start);
		Critter(const Critter &other);

	public:
		virtual ~Critter();		//virtual deconstructor since class is inherrited
		virtual void move(game_board& board);	//move function is virtual
		virtual bool breed(game_board& board) const;
		virtual const bool starve(const game_board& board) const;
		virtual void inc_eaten();
		const char get_species() const;
		const bool has_moved() const;
		void next_time_step();
		const int get_x() const;
		const int get_y() const;
		const int game_start() const;
};

#endif
