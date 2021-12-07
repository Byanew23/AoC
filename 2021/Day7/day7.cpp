#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include <fstream>
#include <cstdlib>

std::vector<std::string> splitter(std::string in_pattern, std::string &content)
{
    std::vector<std::string> split_content;

    std::regex pattern(in_pattern);
    copy(std::sregex_token_iterator(content.begin(), content.end(), pattern, -1),
         std::sregex_token_iterator(), back_inserter(split_content));
    return split_content;
}

int solve1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string line;

    getline(file, line);

    std::vector<std::string> rawInput = splitter(",", line);
    std::vector<int> input;

    for (auto i : rawInput)
    {
        input.push_back(std::stoi(i));
    }

    std::sort(input.begin(), input.end());
    int res = 0;
    long least = 9999999999999;
    int winningPos;

    for (int i = input[0]; i <= input[input.size() - 1]; ++i)
    {
        long temp = 0;
        for (auto j : input)
        {
            temp += std::abs(j - i);
        }
        if (temp < least)
        {
            least = temp;
            winningPos = i;
        }
    }

    return least;
}

int solve2()
{
    std::ifstream file;
    file.open("input.txt");
    std::string line;

    getline(file, line);

    std::vector<std::string> rawInput = splitter(",", line);
    std::vector<int> input;

    for (auto i : rawInput)
    {
        input.push_back(std::stoi(i));
    }

    std::sort(input.begin(), input.end());
    int res = 0;
    long least = 9999999999999;
    int winningPos;

    for (int i = input[0]; i <= input[input.size() - 1]; ++i)
    {
        long temp = 0;
        for (auto j : input)
        {
            temp += ((std::abs(j - i) * (std::abs(j - i) - 1)) / 2) + std::abs(j - i);
        }
        if (temp < least)
        {
            least = temp;
            winningPos = i;
        }
    }

    return least;
}

int main(void)
{

    std::cout << "Solution for part 1: " << solve1() << std::endl;
    std::cout << "Solution for part 2: " << solve2() << std::endl;

    return 0;
}