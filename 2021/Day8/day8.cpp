#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}
std::vector<char> splitChars(std::string s)
{

    std::vector<char> res(s.begin(), s.end());

    return res;
}

int solve1()
{
    std::ifstream file;
    file.open("input.txt");

    std::string line;
    std::vector<std::string> res;
    while (getline(file, line))
    {
        res.push_back(line.substr(line.find('|') + 2));
    }

    int result = 0;
    for (auto input : res)
    {

        std::vector<std::string> splitted = split(input, " ");
        for (auto in : splitted)
        {
            if (in.size() == 2 || in.size() == 3 || in.size() == 4 || in.size() == 7)
            {
                result++;
            }
        }
    }

    return result;
}

void extractDigits(std::vector<std::string> combination, std::map<int, std::vector<char>> &display)
{
    auto one = std::find_if(combination.begin(), combination.end(), [](const auto value)
                            { return value.size() == 2; });
    display[1] = splitChars(*one);
    combination.erase(one);

    auto four = std::find_if(combination.begin(), combination.end(), [](const auto value)
                             { return value.size() == 4; });
    display[4] = splitChars(*four);
    combination.erase(four);

    auto seven = std::find_if(combination.begin(), combination.end(), [](const auto value)
                              { return value.size() == 3; });
    display[7] = splitChars(*seven);
    combination.erase(seven);

    auto eight = std::find_if(combination.begin(), combination.end(), [](const auto value)
                              { return value.size() == 7; });
    display[8] = splitChars(*eight);
    combination.erase(eight);

    // first iteration to find 3, 9
    for (auto j = combination.begin(); j != combination.end(); ++j)
    {
        auto splitted = splitChars(*j);

        if (splitted.size() == 5 && !display[3].size())
        {
            bool found = std::all_of(display[7].begin(), display[7].end(), [&](const auto ch)
                                     { return std::find(splitted.begin(), splitted.end(), ch) != splitted.end(); });

            if (found)
            {
                display[3] = splitted;
                combination.erase(j);
                --j;
                continue;
            }
        }

        else if (splitted.size() == 6 && !display[9].size())
        {
            bool found = std::all_of(display[4].begin(), display[4].end(), [&](const auto ch)
                                     { return std::find(splitted.begin(), splitted.end(), ch) != splitted.end(); });

            if (found)
            {
                display[9] = splitted;
                combination.erase(j);
                --j;
                continue;
            }
        }
    }

    // Second iter to find 5
    for (auto j = combination.begin(); j != combination.end(); ++j)
    {
        auto splitted = splitChars(*j);

        if (splitted.size() == 5 && !display[5].size())
        {

            bool found = std::all_of(splitted.begin(), splitted.end(), [&](const auto ch)
                                     { return std::find(display[9].begin(), display[9].end(), ch) != display[9].end(); });

            if (found)
            {
                display[5] = splitted;
                combination.erase(j);
                --j;
                break;
            }
        }
    }

    // Thirs iter to find 6
    for (auto j = combination.begin(); j != combination.end(); ++j)
    {
        auto splitted = splitChars(*j);
        if (splitted.size() == 6 && !display[6].size())
        {
            bool found = std::all_of(display[5].begin(), display[5].end(), [&](const auto ch)
                                     { return std::find(splitted.begin(), splitted.end(), ch) != splitted.end(); });

            if (found)
            {
                display[6] = splitted;
                combination.erase(j);
                --j;
                break;
            }
        }
    }

    // Forth iter to find remainng 0, 2
    for (auto j = combination.begin(); j != combination.end(); ++j)
    {
        auto splitted = splitChars(*j);

        if (splitted.size() == 5)
        {
            display[2] = splitted;
            combination.erase(j);
            --j;
        }
        else if (splitted.size() == 6)
        {
            display[0] = splitted;
            combination.erase(j);
            --j;
        }
    }

    return;
}

int solve2()
{
    std::ifstream file;
    file.open("input.txt");

    std::string line;

    std::vector<std::string> temp;
    std::vector<std::vector<std::string>> combinations, res;

    while (getline(file, line))
    {
        temp = split(line, " | ");
        std::vector<std::string> splitted = split(temp[0], " ");

        combinations.push_back(splitted);

        splitted = split(temp[1], " ");
        res.push_back(splitted);
    }

    int result = 0;
    for (auto i = 0; i < combinations.size(); ++i)
    {
        std::map<int, std::vector<char>> display;
        // clear map for every combinations
        for (int digit = 0; digit < 10; ++digit)
        {
            display[digit].clear();
        }

        extractDigits(combinations[i], display);

        std::vector<int> raw_res;

        std::string partial = "";
        for (auto j : res[i])
        {

            auto splitted = splitChars(j);
            bool found = false;
            for (auto digits : display)
            {
                found = (std::all_of(splitted.begin(), splitted.end(), [&](const auto ch)
                                     { return (std::find(digits.second.begin(), digits.second.end(), ch) != digits.second.end()) && (splitted.size() == digits.second.size()); }));

                if (found == true)
                {
                    partial += std::to_string(digits.first);
                    found = false;
                    continue;
                }
            }
        }

        raw_res.push_back(std::stoi(partial));
        partial = "";

        // for (auto j : display)
        // {
        //     std::cout << j.first << " -> ";
        //     for (auto dig : j.second)
        //     {
        //         std::cout << dig << ' ';
        //     }
        //     std::cout << std::endl;
        // }

        for (auto num : raw_res)
        {
            result += num;
        }
    }

    return result;
}

int main(void)
{

    // std::cout << "Solution for part 1: " << solve1() << std::endl;
    std::cout << "Solution for part 2: " << solve2() << std::endl;

    return 0;
}