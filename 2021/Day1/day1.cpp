#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int solve1(void)
{
    std::ifstream myfile("input.txt");
    std::string depthstr;

    std::string prevstr;
    std::getline(myfile, prevstr);

    int prev = std::stoi(prevstr);

    int res = 0;
    while (myfile >> depthstr)
    {
        int depth = std::stoi(depthstr);
        if (depth > prev)
            res++;
        prev = depth;
    }

    return res;
};

int solve2(void)
{
    std::ifstream myfile("input.txt");

    std::string init;
    int first, sec, third, fourth;
    int prev = -1, curr;
    int res = 0;

    while (std::getline(myfile, init))
    {
        std::istringstream iss(init);
        int depth;
        if (!(iss >> depth))
        {
            break;
        } // error

        if (!first)
        {
            first = depth;
        }
        else if (!sec)
        {
            sec = depth;
        }
        else if (!third)
        {
            third = depth;
        }
        else if (!fourth)
        {
            fourth = depth;
        }
        else
        {
            if (first + sec + third < sec + third + fourth)
                res++;
            first = sec;
            sec = third;
            third = fourth;
            fourth = depth;
        }
    }

    return res;
};

int main(void)
{

    std::cout << "Solution for part 1: " << solve1() << std::endl;
    std::cout << "Solution for part 2: " << solve2() << std::endl;
    return 0;
}
