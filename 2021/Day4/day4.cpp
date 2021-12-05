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

int solve1()
{
  std::ifstream file;
  file.open("input.txt");
  std::string inputs;
  getline(file, inputs);

  auto splittedInputs = splitter(",", inputs);

  std::string line;

  std::map<int, std::vector<std::string>> bingos;

  std::string a, b, c, d, e;
  int row = 0, num = 0;
  while (file >> a >> b >> c >> d >> e)
  {
    if (row >= 5)
    {
      row = 0;
      num++;
    }

    bingos[num].push_back(a);
    bingos[num].push_back(b);
    bingos[num].push_back(c);
    bingos[num].push_back(d);
    bingos[num].push_back(e);
    bingos[num].push_back("*");
    row++;
  }

  bool BINGO = false;
  int winningBoard, winningNum, prevInput;

  // Chek every input
  for (auto input : splittedInputs)
  {
    if (BINGO)
      break;
    // Check every Bingo board
    for (auto i = bingos.begin(); i != bingos.end(); i++)
    {
      if (BINGO)
        break;

      bool first = true;
      auto prev = bingos[i->first][0];

      // Check every number in the board
      for (auto num : bingos[i->first])
      {
        // If the first char is '*' or there are 2 '*' next to eachother - BINGO!
        if (first && num == "*" || (prev == num && num == "*"))
        {
          BINGO = true;
          winningBoard = i->first;
          winningNum = std::stoi(input);

          break;
        }

        if (num == input)
        {
          auto position = std::find(bingos[i->first].begin(), bingos[i->first].end(), num);

          if (position != bingos[i->first].end())
            bingos[i->first].erase(position);
        }

        prev = num;
        first = false;
      }
    }
    winningNum = prevInput;
    prevInput = std::stoi(input);
  }

  int sum = 0;
  if (BINGO)
  {
    for (auto ch : bingos[winningBoard])
    {
      if (ch != "*")
        sum += stoi(ch);
    }
  }

  return sum * winningNum;
}

int solve2()
{
  std::ifstream file;
  file.open("input.txt");
  std::string rawInputs;
  getline(file, rawInputs);

  auto inputs = splitter(",", rawInputs);

  std::vector<std::vector<int>> bingoBoard(5), bingoCols(5);
  std::map<int, std::vector<std::vector<int>>> bingos, bingosVert;
  std::vector<bool> checkedBoards;

  std::vector<int> bingoSums(1024, 0);

  std::string a, b, c, d, e;
  int num = 0, row = 0;

  while (file >> a >> b >> c >> d >> e)
  {
    // Add columns to [row] at bingo [num]
    bingoBoard[row].push_back(std::stoi(a));
    bingoBoard[row].push_back(std::stoi(b));
    bingoBoard[row].push_back(std::stoi(c));
    bingoBoard[row].push_back(std::stoi(d));
    bingoBoard[row].push_back(std::stoi(e));

    // Add the columns to bingovert [num] to check for veritcal bingos
    bingoCols[0].push_back(std::stoi(a));
    bingoCols[1].push_back(std::stoi(b));
    bingoCols[2].push_back(std::stoi(c));
    bingoCols[3].push_back(std::stoi(d));
    bingoCols[4].push_back(std::stoi(e));

    //increase the sums
    bingoSums[num] += std::stoi(a);
    bingoSums[num] += std::stoi(b);
    bingoSums[num] += std::stoi(c);
    bingoSums[num] += std::stoi(d);
    bingoSums[num] += std::stoi(e);

    row++;

    if (row >= 5)
    {
      checkedBoards.push_back(false);
      bingos[num] = bingoBoard;
      for (int i = 0; i < row; ++i)
      {
        bingosVert[num].push_back(bingoCols[i]);

        bingoCols[i].clear();
        bingoBoard[i].clear();
      }

      row = 0;
      num++;
    }
  }

  bool BINGO = false;
  int winningNumber, winningBingo;
  // Chek every input
  for (auto input : inputs)
  {
    if (BINGO)
      break;

    // Check rows
    for (auto bingo : bingos)
    {
      if (BINGO)
        break;

      for (auto row = bingos[bingo.first].begin(); row != bingos[bingo.first].end(); ++row)
      {
        // for every row
        if (BINGO)
          break;
        for (auto num = row->begin(); num != row->end(); ++num)
        {
          if (std::stoi(input) == *num)
          {
            // Decrease the total sum
            bingoSums[bingo.first] -= std::stoi(input);

            // Remove the number
            auto positionRow = std::find(row->begin(), row->end(), *num);
            // auto positionCol = std::find(col->begin(), col->end(), *num);

            if (positionRow != row->end())
              row->erase(positionRow);

            //Check for bingo
            if (row->empty())
            {
              checkedBoards[bingo.first] = true;
            }

            // Check for last board
            if (std::all_of(checkedBoards.begin(), checkedBoards.end(), [](const auto value)
                            { return value; }))
            {
              BINGO = true;
              winningNumber = std::stoi(input);
              winningBingo = bingo.first;
            }
            break;
          }
        }
      }

      // Check cols
      for (auto col = bingosVert[bingo.first].begin(); col != bingosVert[bingo.first].end(); ++col)
      {
        // for every row
        if (BINGO)
          break;
        for (auto num = col->begin(); num != col->end(); ++num)
        {
          if (std::stoi(input) == *num)
          {

            // Remove the number
            auto positionCol = std::find(col->begin(), col->end(), *num);

            if (positionCol != col->end())
              col->erase(positionCol);

            //Check for bingo
            if (col->empty())
            {
              checkedBoards[bingo.first] = true;
            }

            // Check for last board
            if (std::all_of(checkedBoards.begin(), checkedBoards.end(), [](const auto value)
                            { return value; }))
            {
              BINGO = true;
              winningNumber = std::stoi(input);
              winningBingo = bingo.first;
            }
            break;
          }
        }
      }
    }
  }

  return winningNumber * bingoSums[winningBingo];
}

int main(void)
{

  std::cout << "Solution for part 1: " << solve1() << std::endl;
  std::cout << "Solution for part 2: " << solve2() << std::endl;

  return 0;
}