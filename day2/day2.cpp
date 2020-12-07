#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <tuple>
#include <string>

std::vector<std::string>& split(const std::string& s, char delimeter, std::vector<std::string>& elems)
{
	std::istringstream iss(s);
	std::string item;

	while (std::getline(iss, item, delimeter))
		elems.push_back(item);
	return elems;
}

int main()
{
	std::ifstream stream("./input.txt");
	std::string line;
	int num_valid = 0;

	while (std::getline(stream, line))
	{
		std::vector<std::string> elements;
		split(line, '-', elements);
		int first_num = std::stoi(elements.at(0));
		int second_num = std::stoi(elements.at(1));

		split(line, ':', elements);
		std::string password = elements.at(3);
		split(elements.at(2), ' ', elements);
		std::string letter = elements.at(5);

		//PART 1
		//starts here...
		int count = 0;

		for (auto let : password)
		{
			std::string l;
			l.push_back(let);

			if (letter.compare(l) == 0)
				++count;
		}
		
		if (count >= first_num && count <= second_num)
			++num_valid;
		//...ends here
		
		//PART2
		//starts here...
		int i = 1;
		bool first_contains = false; bool second_contains = false;
		
		std::string pass_at_first; pass_at_first.push_back(password.at(first_num));
		std::string pass_at_second; pass_at_second.push_back(password.at(second_num));

		if (pass_at_first == letter)
			first_contains = true;
		if (pass_at_second == letter)
			second_contains = true;

		if (first_contains xor second_contains)
			++num_valid;
		//...ends here
	}

	std::cout << num_valid;

}