#include "program.hpp"

bool program::load_from_file(string filename)
  {
    if (!this->font_mask.load_file(FONT_PATH))
      return false;

    image source_image;
    bool error;

    if (!source_image.load_file(filename))
      return false;

    cout << "=" << this->string_from_image_area(&source_image,make_coord(0,0),make_coord(100,70),error) << "=" << endl;

    return true;
  }

string program::string_from_image_area(image *img, coord_2d c1, coord_2d c2, bool &error)
  {
    string result = "";

    unsigned int max_y, min_y;
    unsigned int i,j;
    unsigned char r,g,b;

    max_y = c1.y;
    min_y = c2.y;

    for (j = c1.y; j <= c2.y; j++)
      for (i = c1.x; i <= c2.x; i++)
        {
          img->get_pixel(i,j,r,g,b);

          if (is_black(r,g,b))
            {
              if (j < min_y)
                min_y = j;

              if (j > max_y)
                max_y = j;
            }
        }

    cout << min_y << " " << max_y << endl;

    return result;
  }

vector<program_error> program::get_errors()
  {
    vector<program_error> result;
    return result;
  }
