#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

int binToDec(long long n)
{
  int dec = 0, i = 0, rem;

  while (n != 0)
  {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }

  return dec;
}

#define BITS_COUNT 12

int solve1()
{
  std::ifstream file;
  file.open("input.txt");

  std::string line;
  std::vector<int> bits(BITS_COUNT, 0);
  int total = 0;
  while (file >> line)
  {
    total++;
    for (int i = 0; i < line.length(); i++)
    {
      bits[i] += line[i] - '0';
    }
  }

  std::string gamma = "", epsilon = "";
  for (auto bit : bits)
  {
    if (bit >= total / 2)
    {
      gamma += "1";
      epsilon += "0";
    }
    else
    {
      gamma += "0";
      epsilon += "1";
    }
  }

  int gammaDec = binToDec(std::stol(gamma));
  int epsilonDec = binToDec(std::stol(epsilon));

  return gammaDec * epsilonDec;
}

int extract(std::vector<std::string> inputs, bool reverse)
{
  auto end = inputs.end(), newEnd = inputs.end();

  for (int i = 0; i < BITS_COUNT; i++)
  {
    auto distance = std::distance(inputs.begin(), end);

    // If distance is 1, break the loop and get first element
    if (distance <= 1)
    {
      break;
    }

    // Calculate common bits
    std::vector<int> bits(BITS_COUNT, 0);
    for (auto iter = inputs.begin(); iter != end; ++iter)
    {
      for (int pos = 0; pos < BITS_COUNT; pos++)
      {

        bits[pos] += iter->at(pos) - '0';
      }
    }

    // Get target bit at current position
    auto targetBit = (bits[i] >= (distance % 2 == 0 ? distance / 2 : distance / 2 + 1)) == reverse ? "0" : "1";

    // Move elements that have the target bit at the front and get the end of the section
    for (auto it = inputs.begin(); it != end; ++it)
    {
      newEnd = std::partition(inputs.begin(), end, [&](const auto value)
                              { return value[i] == *targetBit; });
    }

    // Move the end pointer of the vector to the end of the filtered elements
    end = newEnd;
  }

  return binToDec(std::stol(inputs.front()));
}
int solve2()
{
  std::ifstream file;
  file.open("input.txt");

  std::string line;
  std::vector<std::string> inputs;
  while (file >> line)
  {
    inputs.push_back(line);
  }

  int O2 = extract(inputs, false);
  int CO2 = extract(inputs, true);

  return O2 * CO2;
}

int main(void)
{

  std::cout << "Solution for part 1: " << solve1() << std::endl;
  std::cout << "Solution for part 2: " << solve2() << std::endl;

  return 0;
}