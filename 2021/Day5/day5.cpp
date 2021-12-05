#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include <fstream>

std::vector<int> splitter(std::string in_pattern, std::string &content)
{
  std::vector<std::string> split_content;

  std::regex pattern(in_pattern);
  copy(std::sregex_token_iterator(content.begin(), content.end(), pattern, -1),
       std::sregex_token_iterator(), back_inserter(split_content));
  return {std::stoi(split_content[0]), std::stoi(split_content[1])};
}

void checkStraight(int startX, int endX, int startY, int endY, std::vector<std::vector<int>> &map)
{
  if (startX == endX)
  {
    if (startY < endY)
    {
      while (startY <= endY)
      {
        map[startY][startX]++;
        startY++;
      }
    }
    else
    {
      while (startY >= endY)
      {
        map[startY][startX]++;
        startY--;
      }
    }
  }
  else if (startY == endY)
  {
    if (startX < endX)
    {
      while (startX <= endX)
      {
        map[startY][startX]++;
        startX++;
      }
    }
    else
    {
      while (startX >= endX)
      {
        map[startY][startX]++;
        startX--;
      }
    }
  }
  return;
}

void checkDiagonals(int startX, int endX, int startY, int endY, std::vector<std::vector<int>> &map)
{
  if (startX > endX)
  {
    if (startY > endY)
    {
      while (startX >= endX)
      {
        map[startY][startX]++;
        startX--;
        startY--;
      }
    }
    else
    {
      while (startX >= endX)
      {
        map[startY][startX]++;
        startX--;
        startY++;
      }
    }
  }
  else
  {
    if (startY > endY)
    {
      while (startX <= endX)
      {
        map[startY][startX]++;
        startX++;
        startY--;
      }
    }
    else
    {
      while (startX <= endX)
      {
        map[startY][startX]++;
        startX++;
        startY++;
      }
    }
  }
  return;
}

int solve1()
{
  std::ifstream file;
  file.open("input.txt");
  std::string a, s, b;
  std::vector<int> start(2), end(2);
  std::map<int, std::vector<std::vector<int>>> mines;
  const int START = 0, END = 1, X = 0, Y = 1;

  int iter = 0, maxX = -1, maxY = -1;
  while (file >> a >> s >> b)
  {
    start = splitter(",", a);
    end = splitter(",", b);

    if ((start[X]) > maxX)
      maxX = (start[X]);
    if ((end[X]) > maxX)
      maxX = (end[X]);
    if ((start[Y]) > maxY)
      maxY = (start[Y]);
    if ((end[Y]) > maxY)
      maxY = (end[Y]);

    mines[iter].push_back(start);
    mines[iter].push_back(end);

    iter++;
  }

  std::vector<std::vector<int>> map(maxY + 1);

  for (int i = 0; i <= maxY; ++i)
  {
    for (int j = 0; j <= maxX; ++j)
    {
      map[i].push_back(0);
    }
  }

  for (auto mine = 0; mine < mines.size(); mine++)
  {
    int startX = mines[mine][START][X];
    int endX = mines[mine][END][X];
    int startY = mines[mine][START][Y];
    int endY = mines[mine][END][Y];

    checkStraight(startX, endX, startY, endY, map);
  }

  // Render the map like in the example
  // std::cout << std::endl;
  // for (auto row = 0; row <= maxY; row++)
  // {
  //   for (auto col = 0; col <= maxX; col++)
  //   {
  //     if (map[row][col] == 0)
  //     {

  //       std::cout << '*' << " ";
  //     }
  //     else
  //     {

  //       std::cout << map[row][col] << " ";
  //     }
  //   }
  //   std::cout << std::endl;
  // }

  int res = 0;
  for (auto row = 0; row <= maxY; row++)
  {
    for (auto col = 0; col <= maxX; col++)
    {
      if (map[row][col] > 1)
      {
        res++;
      }
    }
  }

  return res;
}

int solve2()
{
  std::ifstream file;
  file.open("input.txt");
  std::string a, s, b;
  std::vector<int> start(2), end(2);
  std::map<int, std::vector<std::vector<int>>> mines;
  const int START = 0, END = 1, X = 0, Y = 1;

  int iter = 0, maxX = -1, maxY = -1;
  while (file >> a >> s >> b)
  {
    start = splitter(",", a);
    end = splitter(",", b);

    if ((start[X]) > maxX)
      maxX = (start[X]);
    if ((end[X]) > maxX)
      maxX = (end[X]);
    if ((start[Y]) > maxY)
      maxY = (start[Y]);
    if ((end[Y]) > maxY)
      maxY = (end[Y]);

    mines[iter].push_back(start);
    mines[iter].push_back(end);

    iter++;
  }

  std::vector<std::vector<int>> map(maxY + 1);

  for (int i = 0; i <= maxY; ++i)
  {
    for (int j = 0; j <= maxX; ++j)
    {
      map[i].push_back(0);
    }
  }

  for (auto mine = 0; mine < mines.size(); mine++)
  {
    int startX = mines[mine][START][X];
    int endX = mines[mine][END][X];
    int startY = mines[mine][START][Y];
    int endY = mines[mine][END][Y];

    if (startX == endX || startY == endY)
    {

      checkStraight(startX, endX, startY, endY, map);
    }
    else
    {
      checkDiagonals(startX, endX, startY, endY, map);
    }
  }

  // Render the map like in the example
  // std::cout << std::endl;
  // for (auto row = 0; row <= maxY; row++)
  // {
  //   for (auto col = 0; col <= maxX; col++)
  //   {
  //     if (map[row][col] == 0)
  //     {

  //       std::cout << '*' << " ";
  //     }
  //     else
  //     {

  //       std::cout << map[row][col] << " ";
  //     }
  //   }
  //   std::cout << std::endl;
  // }

  // Count overlapping lines
  int res = 0;
  for (auto row = 0; row <= maxY; row++)
  {
    for (auto col = 0; col <= maxX; col++)
    {
      if (map[row][col] > 1)
      {
        res++;
      }
    }
  }

  return res;
}

int main(void)
{

  std::cout << "Solution for part 1: " << solve1() << std::endl;
  std::cout << "Solution for part 2: " << solve2() << std::endl;

  return 0;
}