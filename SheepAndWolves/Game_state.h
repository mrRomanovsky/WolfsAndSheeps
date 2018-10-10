#pragma once
#include "Position.h"
#include "vector"
#include "iostream"
#include "string"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;

class Game_state
{
public:
	Game_state(bool m_s = true);
	Game_state(Position & s_pos, bool m_s = true);
	Game_state(Position s_pos, Position w1_pos, Position w2_pos, Position w3_pos, Position w4_pos, bool s_m);
	Game_state(Position s_pos, vector<Position>ws_poss, bool s_m);
	Game_state(int s_pos_x, int s_pos_y, int w1_pos_x, int w1_pos_y, int w2_pos_x, int w2_pos_y, 
		int w3_pos_x, int w3_pos_y, int w4_pos_x, int w4_pos_y, bool s_m);
	~Game_state();

	string whose_turn();
	void write_state();
	vector<vector<char>> get_board();
	vector<Game_state> get_posible_next_states();
	bool free_position(Position & new_pos);
private:
	Position sheep_position;
	vector<Position> wolves_positions;
	bool sheep_move;
};
  
inline Game_state::Game_state(bool m_s)
{
	sheep_move = m_s;
	sheep_position = Position(7, 1);
	wolves_positions = vector<Position>{ Position(0,0), Position(0,2), Position(0,4), Position(0,6) };
}

inline Game_state::Game_state(Position & s_pos, bool m_s)
{
	sheep_move = m_s;
	sheep_position = s_pos;
	wolves_positions = vector<Position>{ Position(0,0), Position(0,2), Position(0,4), Position(0,6) };
}

inline Game_state::Game_state(Position s_pos, Position w1_pos, Position w2_pos, Position w3_pos, Position w4_pos, bool s_m)
{
	sheep_position = s_pos;
	wolves_positions = vector<Position>{ w1_pos, w2_pos, w3_pos, w4_pos };
	sheep_move = s_m;
}

inline Game_state::Game_state(Position s_pos, vector<Position> ws_poss, bool s_m)
{
	sheep_position = s_pos;
	wolves_positions = ws_poss;
	sheep_move = s_m;
}

inline Game_state::Game_state(int s_pos_x, int s_pos_y, int w1_pos_x, int w1_pos_y, int w2_pos_x, int w2_pos_y, 
	int w3_pos_x, int w3_pos_y, int w4_pos_x, int w4_pos_y, bool s_m)
{
	sheep_position = Position(s_pos_x, s_pos_y);
	wolves_positions = vector<Position>{ Position(w1_pos_x, w1_pos_y), Position(w2_pos_x, w2_pos_y), Position(w3_pos_x, w3_pos_y), Position(w4_pos_x, w4_pos_y) };
	sheep_move = s_m;
}

Game_state::~Game_state()
{
	wolves_positions.clear();
}

inline string Game_state::whose_turn()
{
	return sheep_move ? "овцы" : "волков";
}

inline void Game_state::write_state()
{
	cout << "Сейчас ход " << whose_turn() << "!" << endl;
	vector<vector<char>> board = get_board();
	for (size_t i = 0; i < 8; ++i)
	{
		for (size_t j = 0; j < 8; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

inline vector<vector<char>> Game_state::get_board()
{
	vector<vector<char>> board = vector<vector<char>>(8, vector<char>(8, '_'));
	board[sheep_position.row][sheep_position.col] = '!';
	board[wolves_positions[0].row][wolves_positions[0].col] = '#';
	board[wolves_positions[1].row][wolves_positions[1].col] = '#';
	board[wolves_positions[2].row][wolves_positions[2].col] = '#';
	board[wolves_positions[3].row][wolves_positions[3].col] = '#';
	return board;
}

inline vector<Game_state> Game_state::get_posible_next_states()
{
	vector <Game_state> next_state = vector<Game_state>();
	Position new_pos;
	if (sheep_move)
	{
		vector<pair<int, int>> steps = vector<pair<int, int>>{ pair<int, int>(-1,-1), pair<int, int>(-1, 1), pair<int, int>(1, -1), pair<int, int>(1,1)};
		for (size_t i = 0; i < 4; i++)
		{
			if (!correct_position(sheep_position.row + steps[i].first,
				sheep_position.col + steps[i].second))
				continue;
			new_pos = Position(sheep_position.row + steps[i].first,
				sheep_position.col + steps[i].second);
			if (free_position(new_pos))
				next_state.push_back(Game_state(new_pos, wolves_positions, !sheep_move));
		}
	}
	else
	{
		vector<pair<int, int>> steps = vector<pair<int, int>>{ pair<int, int>(1, -1), pair<int, int>(1, 1) };
		for (size_t i = 0; i < 4; i++)
		{
			if (correct_position(wolves_positions[i].row + steps[0].first,
				wolves_positions[i].col + steps[0].second))
			{
				new_pos = Position(wolves_positions[i].row + steps[0].first,
					wolves_positions[i].col + steps[0].second);
				if (free_position(new_pos))
				{
					vector<Position> new_wolves_positions = wolves_positions;
					new_wolves_positions[i] = new_pos;
					next_state.push_back(Game_state(sheep_position, new_wolves_positions, !sheep_move));
				}
			}
			if (correct_position(wolves_positions[i].row + steps[1].first,
				wolves_positions[i].col + steps[1].second))
			{
				new_pos = Position(wolves_positions[i].row + steps[1].first,
					wolves_positions[i].col + steps[1].second);
				if (free_position(new_pos))
				{
					vector<Position> new_wolves_positions = wolves_positions;
					new_wolves_positions[i] = new_pos;
					next_state.push_back(Game_state(sheep_position, new_wolves_positions, !sheep_move));
				}
			}
		}
	}
	return next_state;
}

inline bool Game_state::free_position(Position & new_pos)
{
	bool free = true;
	for (size_t i = 0; i < 4; i++)
	{
		free = wolves_positions[i] != new_pos;
	}
	return sheep_position != new_pos && free;
}
