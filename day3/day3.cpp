#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>


std::vector<std::string> extend_tree_field(int num_right, std::vector<std::string> trees)
{
    std::vector<std::string> new_trees(trees);
    for (long i = 0; i < new_trees.size(); ++i)
    {
        long j = 1;
        std::string initial_row = new_trees[i];
        while (j < new_trees.size() * num_right * 2)
        {
            new_trees[i] += initial_row;
            ++j;
        }
    }
    return new_trees;
}


int determine_num_trees(int num_right, int num_down, std::vector<std::string> trees)
{
    trees = extend_tree_field(num_right, trees);

    long num_columns = trees.at(0).size();
    long num_trees = 0; long i = 0;

    for (long j = 0; j < num_columns - num_right;)
    {
        j += num_right;

        if (i < trees.size() - num_down)
        {
            i += num_down;
            if (trees[i][j] == '#')
                ++num_trees;
        }
    }
    return num_trees;
}


int main()
{
    std::ifstream stream("./input.txt");
    std::vector<std::string> trees;
    std::string line;

    while (stream >> line)
        trees.push_back(line);
    
    unsigned long num_trees = determine_num_trees(1, 1, trees) * determine_num_trees(3, 1, trees) * determine_num_trees(5, 1, trees) * determine_num_trees(7, 1, trees) * determine_num_trees(1, 2, trees);
    std::cout << "" << num_trees;
}
