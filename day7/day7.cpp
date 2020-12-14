#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>


std::vector<std::string>& split(const std::string& s, char delimeter, std::vector<std::string>& elems)
{
	std::istringstream iss(s);
	std::string item;

	while (std::getline(iss, item, delimeter))
		elems.push_back(item);
	return elems;
}


void adjust_data(std::vector<std::string>& elements, std::map<std::string, std::vector<std::string>>& bags)
{
	bool is_mother_bag = true;
	std::string mother; std::string child;

	for (auto element : elements)
	{
		if (element == "contain")
		{
			mother = mother.substr(0, mother.length() - 1);
			is_mother_bag = false;
		}
		else
		{
			if (is_mother_bag)
				mother += element + " ";
			else
			{
				if (element[element.length() - 1] == ',' || element[element.length() - 1] == '.')
				{
					child += element.substr(0, element.length() - 1);
					bags[mother].push_back(child);
					child.clear();
				}
				else
					child += element + " ";
			}
		}
	}
	mother.clear();
}

std::map<std::string, std::vector<std::pair<int, std::string>>> parse(std::map<std::string, std::vector<std::string>>& bags)
{
	std::map<std::string, std::vector<std::pair<int, std::string>>> parsed_bags;

	for (auto it = bags.begin(); it != bags.end(); ++it)
	{
		for (auto bag : it->second)
		{
			if (bag.find_first_of("0123456789") != std::string::npos)
			{
				std::string str(1, bag[0]);
				parsed_bags[it->first].push_back(std::make_pair(std::stoi(str), bag.substr(2)));
			}
			else
				parsed_bags[it->first].push_back(std::make_pair(0, bag.substr(3)));
		}
	}

	return parsed_bags;
}

std::string get_new_bag(std::pair<int, std::string>& bag)
{
	std::string new_mother = bag.second;
	if (bag.first == 1) new_mother += "s";

	return new_mother;
}


//PART 1
bool get_num_bags(std::string contained_bag, std::string mother, std::map<std::string, std::vector<std::pair<int, std::string>>>& bags, int& num_bags)
{
		for (auto bag : bags[mother])
		{
			if (bag.second.find(contained_bag) != std::string::npos)
				return true;
		}

		bool contains = false;
		for (auto bag : bags[mother])
		{
			std::string new_mother = get_new_bag(bag);

			if (get_num_bags(contained_bag, new_mother, bags, num_bags))
					contains = true;
		}
		return contains;
}


//PART 2
int get_num_inside_bag(std::string contained_bag, std::map<std::string, std::vector<std::pair<int, std::string>>>& bags, std::map<std::string, bool>& visited)
{
	visited[contained_bag] = true;
	int total_num_bags = 0;
	for (auto bag : bags[contained_bag])
	{
		int num_bags_inside = bag.first;
		std::string new_bag = get_new_bag(bag);

		if (!visited[new_bag])
		{
			total_num_bags += num_bags_inside;
			total_num_bags += num_bags_inside * get_num_inside_bag(new_bag, bags, visited);
		}
	}
	
	return total_num_bags;
}


int main()
{
	std::fstream bag_rules("./input.txt");
	std::string rule;
	std::map<std::string, std::vector<std::string>> bags;
	int num_bags_1 = 0; int num_bags_2 = 0; int num_bags_inside = 0;
	std::map<std::string, bool> visited;

	while (std::getline(bag_rules, rule))
	{
		std::vector<std::string> elements;
		split(rule, ' ', elements);
		adjust_data(elements, bags);
	}

	std::map<std::string, std::vector<std::pair<int, std::string>>> parsed_bags = parse(bags);

	for (auto it = bags.begin(); it != bags.end(); ++it)
		if(get_num_bags("shiny gold bag", it->first, parsed_bags, num_bags_1))
			++num_bags_1;

	num_bags_2 = get_num_inside_bag("shiny gold bags", parsed_bags, visited);

	std::cout << "Part 1: " << num_bags_1 << std::endl;
	std::cout << "Part 2: " << num_bags_2;
}
