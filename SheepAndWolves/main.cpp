#include <iostream>
#include "Game_state.h"

//using namespace std;
using std::vector;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "DRATUI, MIR!" << endl;
	Game_state start_state = Game_state();
	start_state.write_state();

	vector<Game_state> s = start_state.get_posible_next_states();

	cout << "###################################" << endl;
	start_state.write_state();
	cout << start_state.shortest_sheep_path() << endl;
/*
	for (size_t i = 0; i < s.size(); i++)
	{
		s[i].write_state();
	}*/
	/*
	vector<Game_state> s1 = s[0].get_posible_next_states();
	for (size_t i = 0; i < s1.size(); i++)
	{
		s1[i].write_state();
	}
	s = s1[0].get_posible_next_states();
	for (size_t i = 0; i < s.size(); i++)
	{
		s[i].write_state();
	}*/
	system("pause");
}