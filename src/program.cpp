#include "program.hpp"

bool program::load_from_file(string filename)
  {
    if (!this->font_mask.load_file(FONT_PATH))
      return false;

    image source_image;
    bool error;

    if (!source_image.load_file(filename))
      return false;

    cout << "=" << this->string_from_image_area(&source_image,make_coord(0,0),make_coord(100,100),error) << "=" << endl;

    return true;
  }


int program::char_from_image_position(image *img, coord_2d c)
  {
    unsigned int i, j, k, x, y;
    unsigned char r,g,b,r2,g2,b2;
    bool matches;

    for (k = 0; k < 256; k++)
      {
        x = (k % FONT_ROW_SYMBOLS) * FONT_WIDTH;   // character coordinates in the font mask
        y = (k / FONT_ROW_SYMBOLS) * FONT_HEIGHT;

        matches = true;

        for (j = 0; j < FONT_HEIGHT; j++)
          {
            for (i = 0; i < FONT_WIDTH; i++)
              {
                img->get_pixel(c.x + i,c.y + j,r,g,b);
                this->font_mask.get_pixel(x + i,y + j,r2,g2,b2);

                if ((is_black(r,g,b)) != (is_black(r2,g2,b2)))
                  matches = false;
              }
          }

        if (matches)
          return k;
      }

    return -1;
  }

string program::string_from_image_area(image *img, coord_2d c1, coord_2d c2, bool &error)
  {
    string result = "";

    int max_y, min_y, max_x, min_x;
    unsigned int i,j;
    unsigned char r,g,b;
    bool end_it;

    end_it = false;
    min_y = c2.y;

    for (j = c1.y; j <= c2.y; j++)
      {
        for (i = c1.x; i <= c2.x; i++)
          {
            img->get_pixel(i,j,r,g,b);

            if (is_black(r,g,b))
              {
                end_it = true;
                min_y = j;
              }
          }

        if (end_it)
          break;
      }

    max_y = c1.y;
    end_it = false;

    for (j = c2.y - 1; j >= c1.y; j--)
      {
        for (i = c1.x; i <= c2.x; i++)
          {
            img->get_pixel(i,j,r,g,b);

            if (is_black(r,g,b))
              {
                end_it = true;
                max_y = j;
              }
          }

        if (end_it)
          break;
      }

    if (max_y - min_y > (FONT_HEIGHT - 1) || max_y - min_y < 0)   // in this cases there cannot be a valid text
      {
        // SET ERROR HEREEEEEEEEEEEEEEEEEEE LATER

        return result;
      }

    min_x = c2.x;
    end_it = false;

    for (i = c1.x; i <= c2.x; i++)
      {
        for (j = min_y; ((int) j) <= max_y; j++)
          {
            img->get_pixel(i,j,r,g,b);

            if (is_black(r,g,b))
              {
                end_it = true;
                min_x = i;
              }
          }

        if (end_it)
          break;
      }

    max_x = c1.x;
    end_it = false;

    for (i = c2.x - 1; i >= c1.x; i--)
      {
        for (j = min_y; ((int) j) <= max_y; j++)
          {
            img->get_pixel(i,j,r,g,b);

            if (is_black(r,g,b))
              {
                end_it = true;
                max_x = i;
              }
          }

        if (end_it)
          break;
      }

    // now try to read the string at possitions it could possibly appear:

    coord_2d coord_from, coord_to;   // range of possible top left corner of the string, will be brute force-tested
    coord_2d current_coord;
    int x_limit, y_difference;
    bool success;

    y_difference = max_y - min_y;

    x_limit = saturate(max_x + FONT_WIDTH - 1,c1.x,c2.x);  // to what maximum x the sring should be read

    coord_to.x = min_x;
    coord_to.y = min_y;

    coord_from.y = saturate(coord_to.y - (FONT_HEIGHT - y_difference - 1),c1.y,c2.y);
    coord_from.x = saturate(min_x - FONT_WIDTH + 1,c1.x,c2.x);

    for (j = coord_from.y; j <= coord_to.y; j++)
      for (i = coord_from.x; i <= coord_to.x; i++)
        {
          current_coord.x = i;
          current_coord.y = j;

          result = this->string_from_image_position(img,current_coord,x_limit,success);

          if (success)
            return result;
        }

    return result;
  }

string program::string_from_image_position(image *img, coord_2d c, unsigned int max_x, bool &success)
  {
    int character;
    string result;
    success = true;

    result = "";

    while (c.x <= max_x)
      {
        character = this->char_from_image_position(img,c);

        if (character < 0)    // error
          {
            success = false;
            result = "";
            return result;
          }

        result += (unsigned char) character;
        c.x += (FONT_WIDTH + 1);   // move to the next character
      }

    result = trim(result);

    if (result.length() == 0)
      success = false;

    return result;
  }


vector<program_error> program::get_errors()
  {
    vector<program_error> result;
    return result;
  }
