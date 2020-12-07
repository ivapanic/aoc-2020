#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

constexpr int SUM = 2020;
int main()
{
	std::ifstream stream("./day1/input.txt");
	std::vector<int> entries;

	int entry, max_next_entry = 2020;
	int current_line = 0;

	while (stream >> entry)
		entries.push_back(entry);

	for (int entry : entries)
	{
		for (int second_entry : entries)
		{
			//PART 1
			////starts here...
			if (entry + second_entry == SUM)
			{
				std::cout << entry * second_entry;
				exit(0);
			}
			//...ends here

			//PART2
			//starts here...
			for (int third_entry : entries)
			{
				if (entry + second_entry + third_entry == SUM)
				{
					std::cout << entry * second_entry * third_entry;
					return 0;
				}
			}
			//...ends here
		}

	}
}

