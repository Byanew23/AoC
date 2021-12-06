#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include <fstream>

std::vector<std::string> splitter(std::string in_pattern, std::string &content)
{
    std::vector<std::string> split_content;

    std::regex pattern(in_pattern);
    copy(std::sregex_token_iterator(content.begin(), content.end(), pattern, -1),
         std::sregex_token_iterator(), back_inserter(split_content));
    return split_content;
}

void calcGen(std::map<int, long> &school)
{
    for (auto it : school)
    {

        if (it.first == 0 && school[0] > 0)
        {
            school[9] += school[0];  // new parents
            school[10] += school[0]; // new fish
            school[0] = 0;
        }
        else if (it.first == 9)
        {
            school[6] += school[9];
            school[9] = 0;
        }
        else if (it.first == 10)
        {
            school[8] += school[10];
            school[10] = 0;
        }
        else
        {
            if (school[it.first] > 0)
            {

                school[it.first - 1] += school[it.first];
                school[it.first] = 0;
            }
        }
    }
    return;
}

long solve1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string rawInputs;

    getline(file, rawInputs);

    std::vector<std::string> gen = splitter(",", rawInputs);

    std::map<int, long> school;

    for (auto i : gen)
    {
        school[std::stoi(i)]++;
    }

    for (int days = 0; days < 80; days++)
    {

        calcGen(school);
    }

    long res = 0;
    for (auto it : school)
    {
        res += it.second;
    }

    return res;
}

long solve2()
{

    std::ifstream file;
    file.open("input.txt");
    std::string rawInputs;

    getline(file, rawInputs);

    std::vector<std::string> gen = splitter(",", rawInputs);

    std::map<int, long> school;

    for (auto i : gen)
    {
        school[std::stoi(i)]++;
    }

    for (int days = 0; days < 256; days++)
    {

        calcGen(school);
    }

    long res = 0;
    for (auto it : school)
    {
        res += it.second;
    }

    return res;
}

int main(void)
{

    std::cout << "Solution for part 1: " << solve1() << std::endl;
    std::cout << "Solution for part 2: " << solve2() << std::endl;

    return 0;
}