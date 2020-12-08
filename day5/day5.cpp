#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

constexpr int LOW_ROW = 0;
constexpr int HIGH_ROW = 127;
constexpr int LOW_COLUMN = 0;
constexpr int HIGH_COLUMN = 7;

std::vector<int> get_seat(const std::string& specification, int low_row, int high_row, int low_column, int high_column)
{
	int last_index = 0; int length = specification.length();
	char last_character; int half_rows, half_columns;

	while (last_index < length)
	{
		last_character = specification[last_index];

		half_rows = high_row - low_row >> 1;
		half_columns = high_column - low_column >> 1;

		if (last_index < length - 3)
		{
			if (last_character == 'B') //upper half
				low_row += half_rows + 1;
			else if (last_character == 'F') //lower half
				high_row -= (half_rows + 1);
		}
		else
		{
			if (last_character == 'R') //upper half
				low_column += half_columns + 1;
			else if (last_character == 'L') //lower half
				high_column -= (half_columns + 1);
		}
		++last_index;
	}

	std::vector<int> vector; vector.push_back(low_row); vector.push_back(low_column);
	return vector;
}

int find_your_seat(std::vector<int> all_seats)
{
	std::sort(all_seats.begin(), all_seats.end());
	int last_seat = all_seats[0];
	for (auto seat : all_seats)
	{
		if (seat - last_seat == 2)
			return last_seat + 1;
		last_seat = seat;
	}

}

int main()
{
	std::fstream seats("./input.txt");
	std::string seat;
	std::vector<int> seat_coor; std::vector<int> all_seats;
	int max_id = 0;
	
	while (seats >> seat)
	{
		seat_coor = get_seat(seat, LOW_ROW, HIGH_ROW, LOW_COLUMN, HIGH_COLUMN);
		int id = seat_coor[0] * 8 + seat_coor[1];
		all_seats.push_back(id);

		//PART 1
		//starts here...
		if (id >= max_id)
			max_id = id;
		//...ends_here

	}

	std::cout << "The highest seat ID: " << max_id << std::endl;

	//PART 2
	//starts here...
	std::cout << "Your seat ID is: " << find_your_seat(all_seats) << std::endl;
	//...ends here
}
