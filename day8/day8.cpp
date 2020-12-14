#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <string>
#include <stack>


void execute_instruction(std::map<int, std::tuple<std::string, int, int>>::iterator& it, std::map<int, std::tuple<std::string, int, int>> instructions, int& acc_value)
{
	auto instruction = std::get<0>(it->second);

	it->second = std::make_tuple(std::get<0>(it->second), std::get<1>(it->second), ++std::get<2>(it->second));
	if (std::get<2>(it->second) != 2)
	{
		if (instruction == "nop")
			++it;
		else if (instruction == "acc")
		{
			acc_value += std::get<1>(it->second);
			++it;
		}
		else if (instruction == "jmp")
		{
			int distance = std::get<1>(it->second);
			std::advance(it, distance);
		}
	}
}


int main()
{
	std::map<int, std::tuple<std::string, int, int>> instructions;
	std::ifstream stream("./input.txt");
	std::string line;

	int index = 0;

	while (getline(stream, line))
	{
		std::string instruction = line.substr(0, 3);
		int direction = line[4] == '-' ? std::stoi(line.substr(5)) / (-1) : std::stoi(line.substr(5));
		instructions[index] = std::make_tuple(instruction, direction, 0);
		++index;
	}

	int acc_value = 0;
	auto it = instructions.begin();
	std::stack<int> last_instructions;
	bool changed = false;

	while (std::get<2>(it->second) != 2)
		execute_instruction(it, instructions, acc_value);

	std::cout << "Part1 : " << acc_value << std::endl;

}

