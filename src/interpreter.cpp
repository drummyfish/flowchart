#include <iostream>
#include "image.hpp"
#include "program.hpp"

using namespace std;

int main()
  {
    program p;

    cout << p.load_from_file("test2.bmp") << endl;

    return 0;
  }
