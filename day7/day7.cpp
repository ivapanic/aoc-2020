//#include <iostream>
//#include <cstdlib>
//#include <vector>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <map>
//#include <algorithm>
//
//
//std::vector<std::string>& split(const std::string& s, char delimeter, std::vector<std::string>& elems)
//{
//	std::istringstream iss(s);
//	std::string item;
//
//	while (std::getline(iss, item, delimeter))
//		elems.push_back(item);
//	return elems;
//}
//
//
//void get_bags(std::vector<std::string>& elements, std::map<std::string, std::vector<std::string>>& bags)
//{
//	bool is_mother_bag = true;
//	std::string mother; std::string child;
//
//	for (auto element : elements)
//	{
//		if (element == "contain")
//		{
//			mother = mother.substr(0, mother.length() - 1);
//			is_mother_bag = false;
//		}
//		else
//		{
//			if (is_mother_bag)
//				mother += element + " ";
//			else
//			{
//				if (element[element.length() - 1] == ',' || element[element.length() - 1] == '.')
//				{
//					child += element.substr(0, element.length() - 1);
//					bags[mother].push_back(child);
//					child.clear();
//				}
//				else
//					child += element + " ";
//			}
//		}
//	}
//	mother.clear();
//}
//
////PART 1
//bool get_num_bags(std::string contained_bag, std::string mother, std::map<std::string, std::vector<std::string>>& bags, int& num_bags)
//{
//		for (auto bag : bags[mother])
//		{
//			if (bag.find(contained_bag) != std::string::npos)
//				return true;
//		}
//
//		bool contains = false;
//		for (auto bag : bags[mother])
//		{
//			if (bag.find_first_of("0123456789") != std::string::npos)
//			{
//				std::string new_mother = bag.substr(bag.find_first_of("0123456789") + 2);
//				if (new_mother[new_mother.length() - 1] != 's')
//					new_mother += "s";
//				if (get_num_bags(contained_bag, new_mother, bags, num_bags))
//					contains = true;
//			}
//		}
//		return contains;
//}
//
//
//int get_num_inside_bag(std::string contained_bag, std::map<std::string, std::vector<std::string>>& bags, int& num_bags_inside, int& total_num_bags)
//{
//	for (auto bag : bags[contained_bag])
//	{
//		std::string new_bag;
//		if (bag.find_first_of("0123456789") != std::string::npos && bag.substr(0, 2) != "no")
//		{
//			std::string str(1, bag[0]);
//			num_bags_inside = std::stoi(str);
//			new_bag = bag.substr(bag.find_first_of("0123456789") + 2);
//
//			if (bag[0] == 1)
//				new_bag += "s";
//
//			total_num_bags += num_bags_inside;
//		}
//		total_num_bags += num_bags_inside * get_num_inside_bag(new_bag, bags, num_bags_inside, total_num_bags);
//	}
//
//	return total_num_bags;
//}
//
//int main()
//{
//	std::fstream bag_rules("./input.txt");
//	std::string rule;
//	std::map<std::string, std::vector<std::string>> bags;
//	int num_bags_1 = 0; int num_bags_2 = 0; int num_bags_inside = 0;
//
//	while (std::getline(bag_rules, rule))
//	{
//		std::vector<std::string> elements;
//		split(rule, ' ', elements);
//		get_bags(elements, bags);
//	}
//
//	for (auto it = bags.begin(); it != bags.end(); ++it)
//		if(get_num_bags("shiny gold bag", it->first, bags, num_bags_1))
//			++num_bags_1;
//
//	num_bags_2 = get_num_inside_bag("shiny gold bags", bags, num_bags_inside, num_bags_2);
//
//	std::cout << "Part 1: " << num_bags_1 << std::endl;
//	std::cout << "Part 2: " << num_bags_2;
//}

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>

using namespace std;


class Solution {

public:
    int solve(const vector<string>& rules) {

        unordered_map<string, unordered_map<string, int>> g;
        for (const string& rule : rules)
            get_bags(g, rule);

        assert(g.count("shiny gold bag"));
        unordered_map<string, int> dp;
        return dfs(g, "shiny gold bag", dp) - 1;
    }

private:
    int dfs(const unordered_map<string, unordered_map<string, int>>& g,
        string v, unordered_map<string, int>& dp) {

        if (dp.count(v)) return dp[v];

        int res = 1;
        for (const pair<string, int>& p : g.at(v))
            res += p.second * dfs(g, p.first, dp);
        return dp[v] = res;
    }

    void get_bags(unordered_map<string, unordered_map<string, int>>& g,
        const string& s) {

        int contain_index = s.find("contain");

        string p = s.substr(0, contain_index - 2);
        assert(p.substr(p.size() - 3) == "bag");

        string left = s.substr(contain_index + 8);
        assert(isdigit(left[0]) || left.substr(0, 2) == "no");
        if (!isdigit(left[0])) {
            g[p];
            return;
        }

        for (int start = 0, i = start + 1; i < left.size(); i++)
            if (left[i] == ',' || left[i] == '.') {
                string bag_s = left.substr(start, i - start);
                if (bag_s.back() == 's') bag_s.pop_back();

                int space_index = bag_s.find(' ');
                int num = atoi(bag_s.substr(0, space_index).c_str());
                string bag = bag_s.substr(space_index + 1);
                g[p][bag] = num;

                start = i + 2;
                if (start < left.size() && !isdigit(left[start]))
                    assert(false);

                i = start;
            }
    }
};

int main() {

    ifstream input;
    input.open("./input.txt");
    //    input.open("../../input_test_1.txt"); // 32
    assert(input.is_open());

    string line;
    vector<string> rules;
    while (!input.eof()) {
        getline(input, line);
        rules.push_back(line);
    }

    cout << Solution().solve(rules) << endl;

    input.close();

    return 0;
}