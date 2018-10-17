#include <iostream>
#include "Game_state.h"

//using namespace std;
using std::vector;

int main()
{
	setlocale(LC_ALL, "Russian");
	//vector<Position> woolves_pos = vector<Position> {Position(2, 1), Position(2, 3), Position(1, 4), Position(1, 6) };
	//Position sheep_pos = Position(2, 5);
	//Game_state start_state = Game_state(sheep_pos, woolves_pos, false);
	Game_state start_state = Game_state();
	//start_state.write_state();
	//start_state.next_move();
	start_state.write_state();
	int turn;
	cout << "Who do you wanna be? Sheep - 1, Wolf - 2" << endl;
	cin >> turn;
	if (turn == 1)
	{
		cout << "Do you want to set sheep's starting position? 1 - yes, 2 - no" << endl;
		cin >> turn;
		if (turn == 1)
		{
			int row, col;
			cin >> row >> col;
			start_state.move_sheep(Position(row, col));
			start_state.write_state();
		}
		while (!start_state.game_over())
		{
			int move_res = start_state.make_move();
			while (move_res != 1)
				start_state.make_move();
			start_state.write_state();
			start_state.next_move();
			start_state.write_state();
		}
	}
	else
	{
		while (!start_state.game_over())
		{
			start_state.next_move();
			start_state.write_state();
			if (!start_state.game_over())
			{
				int move_res = start_state.make_move();
				while (move_res != 1)
					start_state.make_move();
				start_state.write_state();
			}
		}
	}
	start_state.write_state();
	system("pause");
}