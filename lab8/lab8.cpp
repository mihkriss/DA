#include <iostream>
#include <vector>
#include <sstream>
#include <string>

int main()
{
  std::vector<unsigned> vector;
  std::string line;

  std::getline(std::cin, line);
  std::getline(std::cin, line);
  std::istringstream s(line.c_str());
  while (!s.eof())
  {
    unsigned t;
    s >> t;
    vector.push_back(t);
  }

  unsigned n = vector.size();

  int count1 = 0; 
  int count2 = 0;
  for (unsigned k = 0; k < n; ++k)
  {
    if (vector[k] == 1)
      ++count1;
    else if (vector[k] == 2)
      ++count2;
    else if (vector[k] != 3)
    {
      return 1;
    }
  }

  unsigned swap = 0;

  unsigned r2 = count1;
  unsigned r3 = r2 + count2;

  for (unsigned k = 0; k < r2; ++k)
  {
    if (vector[k] == 2)
    {
      for (unsigned j = r2; j < n; ++j)
      {
        if (vector[j] == 1)
        {
          ++swap;

          vector[k] = vector[j];
          vector[j] = 2;
          break;
        }
      }
    }
    else if (vector[k] == 3)
    {
      for (int j = n - 1; j >= r2; --j)
      {
        if (vector[j] == 1)
        {
          ++swap;
          
          vector[k] = vector[j];
          vector[j] = 3;
          break;
        }
      }
    }
  }

  for (unsigned k = r2; k < r3; ++k)
  {
    if (vector[k] == 3)
    {
      for (unsigned j = r3; j < n; ++j)
      {
        if (vector[j] == 2)
        {
          ++swap;
          
          vector[k] = 2;
          vector[j] = 3;
          break;
        }
      }
    }
  }

  for (unsigned k = 0; k < n; ++k)
  {
  }

  std::cout << swap;
  return 0;
}