#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>
#include <map>

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
    std::vector<std::string> row;

    std::map<char, int> scores;
    scores[')'] = 3;
    scores[']'] = 57;
    scores['}'] = 1197;
    scores['>'] = 25137;

    while (file >> line)
    {
        row.push_back(line);
    }

    std::stack<char> q;

    std::vector<std::string> corrupted;
    int res = 0;

    for (auto it = row.begin(); it != row.end(); ++it)
    {
        for (int i = 0; i < it->size(); ++i)
        {
            switch (it->at(i))
            {
            case '(':
                q.push(it->at(i));
                break;
            case '[':
                q.push(it->at(i));
                break;
            case '{':
                q.push(it->at(i));
                break;
            case '<':
                q.push(it->at(i));
                break;
            case ')':
                if (q.top() != '(')
                {
                    res += scores[it->at(i)];
                }
                q.pop();
                break;
            case ']':
                if (q.top() != '[')
                {
                    res += scores[it->at(i)];
                }
                q.pop();
                break;
            case '}':
                if (q.top() != '{')
                {
                    res += scores[it->at(i)];
                }
                q.pop();
                break;
            case '>':
                if (q.top() != '<')
                {
                    res += scores[it->at(i)];
                }
                q.pop();
                break;
            default:
                break;
            }
        }
        q = std::stack<char>();
    }

    return res;
}

long long solve2()
{
    std::ifstream file;
    file.open("input.txt");

    std::string line;
    std::vector<std::string> row;

    std::map<char, int> scores;
    scores[')'] = 1;
    scores[']'] = 2;
    scores['}'] = 3;
    scores['>'] = 4;

    std::map<char, char> complements;
    complements['('] = ')';
    complements['['] = ']';
    complements['{'] = '}';
    complements['<'] = '>';

    while (file >> line)
    {
        row.push_back(line);
    }

    for (auto it = row.begin(); it != row.end(); ++it)
    {
        std::stack<char> q;
        bool removed = false;
        for (int i = 0; i < it->size(); ++i)
        {
            switch (it->at(i))
            {
            case '(':
                q.push(it->at(i));
                break;
            case '[':
                q.push(it->at(i));
                break;
            case '{':
                q.push(it->at(i));
                break;
            case '<':
                q.push(it->at(i));
                break;
            case ')':
                if (q.top() != '(')
                {
                    row.erase(it);
                    removed = true;
                }
                q.pop();
                break;
            case ']':
                if (q.top() != '[')
                {
                    row.erase(it);
                    removed = true;
                }
                q.pop();
                break;
            case '}':
                if (q.top() != '{')
                {
                    row.erase(it);
                    removed = true;
                }
                q.pop();
                break;
            case '>':
                if (q.top() != '<')
                {
                    row.erase(it);
                    removed = true;
                }
                q.pop();
                break;
            default:
                break;
            }

            if (removed)
                break;
        }
        if (removed)
        {
            it--;
        }
    }

    long long res = 0, temp = 0;
    std::vector<long long> tempResults;
    for (auto s : row)
    {
        std::stack<char> q;
        for (int i = s.size() - 1; i >= 0; --i)
        {

            switch (s[i])
            {
            case '(':
                if (temp == 0)
                {

                    res = res * 5 + scores[complements[s[i]]];
                }
                else
                {
                    temp--;
                }
                break;
            case '[':
                if (temp == 0)
                {
                    res = res * 5 + scores[complements[s[i]]];
                }
                else
                {
                    temp--;
                }
                break;
            case '{':
                if (temp == 0)
                {

                    res = res * 5 + scores[complements[s[i]]];
                }
                else
                {
                    temp--;
                }
                break;
            case '<':
                if (temp == 0)
                {

                    res = res * 5 + scores[complements[s[i]]];
                }
                else
                {
                    temp--;
                }
                break;
            case ')':
                temp++;
                break;
            case ']':
                temp++;
                break;
            case '}':
                temp++;
                break;
            case '>':
                temp++;
                break;
            default:
                break;
            }
        }
        temp = 0;
        tempResults.push_back(res);
        res = 0;
        // break;
    }

    std::sort(tempResults.begin(), tempResults.end());

    return tempResults[tempResults.size() / 2];
}

int main(void)
{

    // std::cout << "Solution for part 1: " << solve1() << std::endl;
    std::cout << "Solution for part 2: " << solve2() << std::endl;

    return 0;
}