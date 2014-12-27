#include "general.hpp"

coord_2d make_coord(unsigned int x, unsigned int y)
  {
    coord_2d result;

    result.x = x;
    result.y = y;

    return result;
  }

string trim_left(string s)
  {
    s.erase(s.begin(),find_if(s.begin(),s.end(),not1(ptr_fun<int,int>(std::isspace))));
    return s;
  }

string trim_right(string s)
  {
    s.erase(find_if(s.rbegin(),s.rend(),not1(std::ptr_fun<int, int>(std::isspace))).base(),s.end());
    return s;
  }

string trim(string s)
  {
    return trim_left(trim_right(s));
  }

int saturate(int value, int min, int max)
  {
    if (value > max)
      return max;

    if (value < min)
      return min;

    return value;
  }

void print_coord(coord_2d c)
  {
    cout << "[" << c.x << ", " << c.y << "]" << endl;
  }
