#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>
#include <map>

std::vector<int> splitChars(std::string s)
{

    std::vector<int> res;
    for (auto ch : s)
    {
        res.push_back(ch - '0');
    }

    return res;
}

void checkNeighbours(int row, int col, std::vector<std::vector<int>> &heightMap, std::vector<int> &min, std::vector<std::vector<int>> &found, std::vector<std::vector<int>> &checked)
{
    int cur = heightMap.at(row).at(col);

    if (!checked[row][col])
    {
        checked[row][col]++;
    }
    else
    {

        return;
    }

    if (row >= heightMap.size() || col >= heightMap.at(row).size())
    {
        std::cout << "\n\nToo big, Something wrong"
                  << "\n\n";
        return;
    }

    if (row == 0 || col == 0)
    {
        if (row == 0 && col == 0)
        {
            if (heightMap.at(row + 1).at(col) > cur && heightMap.at(row).at(col + 1) > cur)
            {
                if (found.at(row).at(col) == 0)
                {
                    min.push_back(cur);
                    found.at(row).at(col) = 1;
                }
                return;
            }
            if (heightMap.at(row + 1).at(col) < cur)
            {
                checkNeighbours(row + 1, col, heightMap, min, found, checked);
            }
            if (heightMap.at(row).at(col + 1) < cur)
            {
                checkNeighbours(row, col + 1, heightMap, min, found, checked);
            }
        }
        else if (row == heightMap.size() - 1)
        {
            if (heightMap.at(row - 1).at(col) > cur && heightMap.at(row).at(col + 1) > cur)
            {

                if (found.at(row).at(col) == 0)
                {
                    min.push_back(cur);
                    found.at(row).at(col) = 1;
                }
                return;
            }
            if (heightMap.at(row - 1).at(col) < cur)
            {
                checkNeighbours(row - 1, col, heightMap, min, found, checked);
            }
            if (heightMap.at(row).at(col + 1) < cur)
            {
                checkNeighbours(row, col + 1, heightMap, min, found, checked);
            }
        }
        else if (col == heightMap.at(row).size() - 1)
        {
            if (heightMap.at(row + 1).at(col) > cur && heightMap.at(row).at(col - 1) > cur)
            {
                if (found.at(row).at(col) == 0)
                {
                    min.push_back(cur);
                    found.at(row).at(col) = 1;
                }
                return;
            }
            if (heightMap.at(row + 1).at(col) < cur)
            {
                checkNeighbours(row + 1, col, heightMap, min, found, checked);
            }
            if (heightMap.at(row).at(col - 1) < cur)
            {
                checkNeighbours(row, col - 1, heightMap, min, found, checked);
            }
        }
        else
        {
            if (row == 0)
            {
                if (heightMap.at(row + 1).at(col) > cur && heightMap.at(row).at(col - 1) > cur && heightMap.at(row).at(col + 1) > cur)
                {

                    if (found.at(row).at(col) == 0)
                    {
                        min.push_back(cur);
                        found.at(row).at(col) = 1;
                    }

                    return;
                }
                if (heightMap.at(row + 1).at(col) < cur)
                {
                    checkNeighbours(row + 1, col, heightMap, min, found, checked);
                }
                if (heightMap.at(row).at(col - 1) < cur)
                {
                    checkNeighbours(row, col - 1, heightMap, min, found, checked);
                }
                if (heightMap.at(row).at(col + 1) < cur)
                {
                    checkNeighbours(row, col + 1, heightMap, min, found, checked);
                }
            }
            else if (col == 0)
            {
                if (heightMap.at(row - 1).at(col) > cur && heightMap.at(row + 1).at(col) > cur && heightMap.at(row).at(col + 1) > cur)
                {

                    if (found.at(row).at(col) == 0)
                    {
                        min.push_back(cur);
                        found.at(row).at(col) = 1;
                    }
                    return;
                }
                if (heightMap.at(row - 1).at(col) < cur)
                {
                    checkNeighbours(row - 1, col, heightMap, min, found, checked);
                }
                if (heightMap.at(row + 1).at(col) < cur)
                {
                    checkNeighbours(row + 1, col, heightMap, min, found, checked);
                }
                if (heightMap.at(row).at(col + 1) < cur)
                {
                    checkNeighbours(row, col + 1, heightMap, min, found, checked);
                }
            }
        }
    }
    else if (row == heightMap.size() - 1 || col == heightMap.at(row).size() - 1)
    {
        if (row == heightMap.size() - 1 && col == heightMap.at(row).size() - 1)
        {
            if (heightMap.at(row - 1).at(col) > cur && heightMap.at(row).at(col - 1) > cur)
            {

                if (found.at(row).at(col) == 0)
                {
                    min.push_back(cur);
                    found.at(row).at(col) = 1;
                }
                return;
            }
            if (heightMap.at(row - 1).at(col) < cur)
            {
                checkNeighbours(row - 1, col, heightMap, min, found, checked);
            }
            if (heightMap.at(row).at(col - 1) < cur)
            {
                checkNeighbours(row, col - 1, heightMap, min, found, checked);
            }
        }
        else if (row == 0)
        {
            if (heightMap.at(row + 1).at(col) > cur && heightMap.at(row).at(col - 1) > cur)
            {

                if (found.at(row).at(col) == 0)
                {
                    min.push_back(cur);
                    found.at(row).at(col) = 1;
                }
                return;
            }
            if (heightMap.at(row + 1).at(col) < cur)
            {
                checkNeighbours(row + 1, col, heightMap, min, found, checked);
            }
            if (heightMap.at(row).at(col - 1) < cur)
            {
                checkNeighbours(row, col - 1, heightMap, min, found, checked);
            }
        }
        else if (col == 0)
        {
            if (heightMap.at(row - 1).at(col) > cur && heightMap.at(row).at(col + 1) > cur)
            {

                if (found.at(row).at(col) == 0)
                {
                    min.push_back(cur);
                    found.at(row).at(col) = 1;
                }
                return;
            }
            if (heightMap.at(row - 1).at(col) < cur)
            {
                checkNeighbours(row - 1, col, heightMap, min, found, checked);
            }
            if (heightMap.at(row).at(col + 1) < cur)
            {
                checkNeighbours(row, col + 1, heightMap, min, found, checked);
            }
        }
        else
        {
            if (row == heightMap.size() - 1)
            {
                if (heightMap.at(row - 1).at(col) > cur && heightMap.at(row).at(col - 1) > cur && heightMap.at(row).at(col + 1) > cur)
                {
                    if (found.at(row).at(col) == 0)
                    {
                        min.push_back(cur);
                        found.at(row).at(col) = 1;
                    }
                    return;
                }
                if (heightMap.at(row - 1).at(col) < cur)
                {
                    checkNeighbours(row - 1, col, heightMap, min, found, checked);
                }
                if (heightMap.at(row).at(col - 1) < cur)
                {
                    checkNeighbours(row, col - 1, heightMap, min, found, checked);
                }
                if (heightMap.at(row).at(col + 1) < cur)
                {
                    checkNeighbours(row, col + 1, heightMap, min, found, checked);
                }
            }
            else if (col == heightMap.at(row).size() - 1)
            {
                if (heightMap.at(row - 1).at(col) > cur && heightMap.at(row + 1).at(col) > cur && heightMap.at(row).at(col - 1) > cur)
                {

                    if (found.at(row).at(col) == 0)
                    {
                        min.push_back(cur);
                        found.at(row).at(col) = 1;
                    }
                    return;
                }
                if (heightMap.at(row - 1).at(col) < cur)
                {
                    checkNeighbours(row - 1, col, heightMap, min, found, checked);
                }
                if (heightMap.at(row + 1).at(col) < cur)
                {
                    checkNeighbours(row + 1, col, heightMap, min, found, checked);
                }
                if (heightMap.at(row).at(col - 1) < cur)
                {
                    checkNeighbours(row, col - 1, heightMap, min, found, checked);
                }
            }
        }
    }
    else
    {
        if (heightMap.at(row + 1).at(col) > cur && heightMap.at(row - 1).at(col) > cur && heightMap.at(row).at(col + 1) > cur && heightMap.at(row).at(col - 1) > cur)
        {
            if (found.at(row).at(col) == 0)
            {

                min.push_back(cur);
                found.at(row).at(col) = 1;
            }
            else
            {

                return;
            }
        }
        if (heightMap.at(row + 1).at(col) < cur)
        {
            checkNeighbours(row + 1, col, heightMap, min, found, checked);
        }
        if (heightMap.at(row - 1).at(col) < cur)
        {
            checkNeighbours(row - 1, col, heightMap, min, found, checked);
        }
        if (heightMap.at(row).at(col + 1) < cur)
        {
            checkNeighbours(row, col + 1, heightMap, min, found, checked);
        }
        if (heightMap.at(row).at(col - 1) < cur)
        {
            checkNeighbours(row, col - 1, heightMap, min, found, checked);
        }
    }
    return;
}
void checkMap(std::vector<std::vector<int>> &heightMap, std::vector<int> &min, std::vector<std::vector<int>> &found, std::vector<std::vector<int>> &checked)
{

    for (int row = 0; row < heightMap.size(); row++)
    {
        for (int col = 0; col < heightMap.at(row).size(); col++)
        {
            // std::cout << row << ' ' << col << std::endl;
            checkNeighbours(row, col, heightMap, min, found, checked);
        }
        // std::cout << std::endl;
    }

    return;
}

int solve1()
{
    std::ifstream file;
    file.open("input.txt");

    std::string line;
    std::vector<int> row;
    std::vector<std::vector<int>> heightMap;

    while (file >> line)
    {
        row = splitChars(line);
        heightMap.push_back(row);
    }

    int currRow = 0;
    std::vector<int> min;

    std::vector<int> tempInt;
    std::vector<std::vector<int>> checked, found;
    std::vector<bool> temp;
    for (int row = 0; row < heightMap.size(); ++row)
    {
        for (int col = 0; col < heightMap.at(row).size(); ++col)
        {
            temp.push_back(false);
            tempInt.push_back(0);
        }
        checked.push_back(tempInt);
        found.push_back(tempInt);
        temp.clear();
    }

    checkMap(heightMap, min, found, checked);

    int result = 0;
    for (auto num : min)
    {
        result += num + 1;
    }

    return result;
}

std::vector<std::string> splitter(std::string in_pattern, std::string &content)
{
    std::vector<std::string> split_content;

    std::regex pattern(in_pattern);
    copy(std::sregex_token_iterator(content.begin(), content.end(), pattern, -1),
         std::sregex_token_iterator(), back_inserter(split_content));
    return split_content;
}

int solve2()
{
    std::ifstream file;
    file.open("sample.txt");

    std::string line;
    std::vector<int> row;
    std::vector<std::string> heightMap;

    while (getline(file, line))
    {
        // row = splitChars(line);
        heightMap.push_back(line);
    }

    std::map<int, int> basins;

    std::cout << std::endl;
    int rowN = 0;
    while (rowN <= heightMap.size())
    {
        int len = 0, basNum = 0;
        // auto splitted = splitter("9", row);
        char prev;
        auto begin = heightMap[rowN].begin();
        auto end = heightMap[rowN].end();

        for (auto it = begin; it != end; ++it)
        {
            std::cout << "checking " << *it << " at row " << rowN << std::endl;

            if (*it == '9' && (it != begin || std::distance(begin, it) <= len - 1 || std::distance(begin, it) == len + 1))
            {
                if (rowN = heightMap.size() - 1)
                    break;

                it = heightMap[rowN + 1].begin();
                end = heightMap[rowN + 1].end();

                continue;
            }
            else if (*it == '9')
            {
                len = 0;
                heightMap[rowN].erase(0, *it);
                rowN++;
                if (rowN == heightMap.size() - 1)
                {
                    break;
                }
            }
            else
            {
                basins[rowN]++;
                len++;
            }
        }
        // std::cout << row << std::endl;
        // for (auto n : splitted)
        // {
        //     if (n == "")
        //     {
        //         std::cout << "*";
        //         continue;
        //     }

        //     std::cout << n;

        // }
        // std::cout << std::endl;
    }
    for (auto n : basins)
    {
        std::cout << n.first << " -> " << n.second << std::endl;
    }
    int result = 0;

    return result;
}

int main(void)
{

    // std::cout << "Solution for part 1: " << solve1() << std::endl;
    std::cout << "Solution for part 2: " << solve2() << std::endl;

    return 0;
}