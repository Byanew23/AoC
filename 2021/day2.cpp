#include <iostream>
#include <fstream>
#include <vector>

int solve1(void)
{
    std::ifstream myfile("input.txt");
    std::string command, value;

    int forw = 0, depth = 0;
    const std::string delim = " ";

    while (myfile >> command >> value)
    {

        if (command.compare("down") == 0)
        {
            depth += std::stoi(value);
        }
        if (command.compare("up") == 0)
        {
            depth -= std::stoi(value);
        }

        if (command.compare("forward") == 0)
        {
            forw += std::stoi(value);
        }
    };

    return forw * depth;
};

int solve2()
{
    std::ifstream myfile("input.txt");
    std::string command, value;

    int forw = 0, depth = 0, aim = 0;

    while (myfile >> command >> value)
    {
        int intValue = std::stoi(value);

        // Compare only 1st letter ssuggested by invakid404
        switch (command[0])
        {
        case 'd':
            aim += intValue;
            break;
        case 'u':
            aim -= intValue;
            break;
        case 'f':
            forw += intValue;
            depth += aim * intValue;
            break;
        default:
            break;
        }
    };

    return forw * depth;
};

int main(void)
{

    std::cout << "Solution for part 1: " << solve1() << std::endl;
    std::cout << "Solution for part 2: " << solve2() << std::endl;
    return 0;
}
