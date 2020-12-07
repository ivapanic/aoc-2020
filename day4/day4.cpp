#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <regex>

constexpr int NUM_PASS_ELEMENTS = 8;

std::vector<std::string>& split(const std::string& s, char delimeter, std::vector<std::string>& elems)
{
	std::istringstream iss(s);
	std::string item;

	while (std::getline(iss, item, delimeter))
		elems.push_back(item);
	return elems;
}


bool check_range(const std::string& field, const std::string& value)
{
	if (field == "byr")
		return std::regex_match(value, std::regex("[0-9]{4}")) && std::stoi(value) >= 1920 && std::stoi(value) <= 2002;
	else if (field == "iyr")
		return std::regex_match(value, std::regex("[0-9]{4}")) && std::stoi(value) >= 2010 && std::stoi(value) <= 2020;
	else if (field == "eyr")
		return std::regex_match(value, std::regex("[0-9]{4}")) && std::stoi(value) >= 2020 && std::stoi(value) <= 2030;
	else if (field == "hgt")
	{
		int pos_cm = value.find("cm"); int pos_in = value.find("in");
		return (pos_cm != std::string::npos && std::stoi(value.substr(0, 3)) >= 150 && std::stoi(value.substr(0, 3)) <= 193)
			|| (pos_in != std::string::npos && std::stoi(value.substr(0, 2)) >= 59 && std::stoi(value.substr(0, 2)) <= 76);
	}
	else if (field == "hcl")
		return value[0] == '#' && value.length() == 7 && std::regex_match(value.substr(1, value.length() - 1), std::regex("[0-9a-f]{6}"));
	else if (field == "ecl")
		return std::regex_match(value, std::regex("amb|blu|brn|gry|grn|hzl|oth"));
	else if (field == "pid")
		return std::regex_match(value, std::regex("[0-9]{9}"));
	else if (field == "cid")
		return true;
}


int main()
{
	std::ifstream input("./input.txt");
	std::string line, passport;
	int valid_1 = 0; int valid_2 = 0;
	std::vector<std::string> fields;
	std::vector<std::vector<std::string>> valid_passports;
	
	//PART 1
	//starts here...
	while (std::getline(input, line))
	{
		if (line.size())
			passport += line + " ";
			
		if (input.peek() == EOF || !line.size())
		{
			split(passport, ' ', fields);
			int num_fields = fields.size();

			if (num_fields == NUM_PASS_ELEMENTS) {
				++valid_1;
				valid_passports.push_back(fields);
			}
			else if (num_fields == NUM_PASS_ELEMENTS - 1)
			{
				bool north_pole_cred = false;
				for (auto field : fields)
				{
					std::vector<std::string> key;
					split(field, ':', key);
					if (!key.empty() && key[0] == "cid")
					{
						north_pole_cred = true;
						break;
					}
				}
				if (!north_pole_cred) {
					++valid_1;
					valid_passports.push_back(fields);
				}
			}
			fields.clear();
			passport.clear();
		}
	}
	//...ends here

	//PART 2
	//starts here...

	for (auto passport : valid_passports)
	{
		bool is_valid = true;
		for (auto field : passport)
		{
			split(field, ':', fields);
			is_valid = check_range(fields[0], fields[1]);
			fields.clear();
			if (!is_valid) break;
		}
		if (is_valid)
			++valid_2;
	}
	//...ends here

	std::cout << "Part 1: " << valid_1 << std::endl;
	std::cout << "Part 2: " << valid_2 << std::endl;

}
