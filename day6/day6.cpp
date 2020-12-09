#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

int get_positive_answers(std::string group, int num_lines)
{
	std::map<char, int> answer_times;
	int count = 0;

	for (auto answer : group)
	{
		answer_times[answer] += 1;
	}

	for (auto const& k : answer_times)
	{
		if (k.second == num_lines)
			count++;
	}

	return count;
}

int main()
{
	std::ifstream answers("./input.txt");
	std::string answer, group_answers_1, group_answers_2;
	int num_answers_1 = 0; int num_answers_2 = 0;
	int num_lines = 0;

	while (std::getline(answers, answer))
	{
		if (answer.length())
			num_lines++;

		for (auto ans : answer)
		{
			if (group_answers_1.find(ans) == std::string::npos && answer.length())
				group_answers_1 += ans;

			group_answers_2 += ans;
		}
		

		if (answers.peek() == std::string::npos || !answer.length())
		{
			num_answers_2 += get_positive_answers(group_answers_2, num_lines);
			num_lines = 0;

			num_answers_1 += group_answers_1.length();
			group_answers_1.clear();
			group_answers_2.clear();
		}
	}

	std::cout << "Part 1: " << num_answers_1 << std::endl << "Part 2: " << num_answers_2;

}
