#include "program.hpp"

bool program::load_from_file(string filename)
  {
    if (!this->font_mask.load_file(FONT_PATH))
      return false;

    image source_image;
    bool error;

    if (!source_image.load_file(filename))
      return false;

    // cout << "=" << this->string_from_image_area(&source_image,make_coord(0,0),make_coord(100,100),error) << "=" << endl;

    vector<block_function> v = this->get_function_blocks(&source_image);

    unsigned int i;

    cout << "functions:" << endl;

    for (i = 0; i < v.size(); i++)
      cout << v[i].get_string() << endl;

    cout << "directives:" << endl;
    vector<block_directive> v2 = this->get_directive_blocks(&source_image);

    for (i = 0; i < v2.size(); i++)
      cout << v2[i].get_string() << endl;

    return true;
  }

template<class T>
vector<T> program::get_directive_function_blocks(image *img)

  {
    unsigned int i,j,x,y;
    vector<T> result;
    coord_2d c1, c2;

    bool directive = switch_value<T>::value == 0;  // whether directive or function blocks are being looked for

    for (j = 0; j < img->get_height(); j++)
      for (i = 0; i < img->get_width(); i++)
        {
          if (   // function block corner
            !img->pixel_is_black(i - 1,j)     &&
            !img->pixel_is_black(i - 1,j - 1) &&
            !img->pixel_is_black(i,j - 1) &&
            img->pixel_is_black(i,j)     &&
            img->pixel_is_black(i + 1,j) &&
            img->pixel_is_black(i + 2,j) &&
            img->pixel_is_black(i,j + 1)     &&
            directive != img->pixel_is_black(i + 1,j + 1) &&
            directive != img->pixel_is_black(i + 2,j + 1) &&
            img->pixel_is_black(i,j + 2)     &&
            directive != img->pixel_is_black(i + 1,j + 2) &&
            img->pixel_is_black(i + 2,j + 2))
            {
              // try to follow the block border now:

              c1.x = i;
              c1.y = j;

              x = i + 2;
              y = j;

              while (   // upper horizontal border
                img->pixel_is_black(x + 1,y)     &&
                directive != img->pixel_is_black(x + 1,y + 1) &&    // the middle pixel differs for function and directive block
                img->pixel_is_black(x + 1,y + 2))
                {
                  x++;
                }

              i = x + 1;   // i can skip here now
              y += 2;

              if (directive)    // with directive blocks we have to checks corners
                {
                  if (!(
                    !img->pixel_is_black(x + 1,y - 1) &&
                    img->pixel_is_black(x + 2,y - 1) &&
                    img->pixel_is_black(x + 2,y - 2) &&
                    img->pixel_is_black(x + 1,y - 2)))
                    break;    // corner not valid

                  x += 2;
                }

              while (   // right verticel border
                img->pixel_is_black(x,y + 1)     &&
                directive != img->pixel_is_black(x - 1,y + 1) &&
                img->pixel_is_black(x - 2,y + 1))
                {
                  y++;
                }

              if (directive)
                {
                  if (!(
                    img->pixel_is_black(x,y + 1) &&
                    img->pixel_is_black(x,y + 2) &&
                    !img->pixel_is_black(x - 1,y + 1) &&
                    img->pixel_is_black(x - 1,y + 2)))
                    break;    // corner not valid
                  x -= 2;
                  y += 2;
                }

              c2.x = x;
              c2.y = y;

              if (directive)
                c2.x += 2;

              while (   // lower horizontal border
                img->pixel_is_black(x - 1,y)     &&
                directive != img->pixel_is_black(x - 1,y - 1) &&
                img->pixel_is_black(x - 1,y - 2))
                {
                  x--;
                }

              if (directive)
                {
                  if (!(
                    img->pixel_is_black(x - 1,y) &&
                    img->pixel_is_black(x - 2,y) &&
                    !img->pixel_is_black(x - 1,y - 1) &&
                    img->pixel_is_black(x - 2,y - 1)))
                    break;    // corner not valid

                  x -= 2;
                }

              y -= 2;

              while (   // left vertical border
                img->pixel_is_black(x,y - 1)     &&
                directive != img->pixel_is_black(x + 1,y - 1) &&
                img->pixel_is_black(x + 2,y - 1))
                {
                  y--;
                }

              if (directive)
                y -= 2;

              if (
                x == c1.x && y == c1.y &&          // block detected
                c2.x - c1.x > FONT_WIDTH + 6 &&    // minimum block size to have at least one character
                c2.y - c1.y > FONT_HEIGHT + 6)
                {
                  string block_string;
                  bool error;

                  block_string = this->string_from_image_area(img,make_coord(c1.x + 3,c1.y + 3),make_coord(c2.x - 3,c2.y - 3),error);

                  T b(block_string);

                  result.push_back(b);
                }
            }
        }

    return result;
  }

vector<block_directive> program::get_directive_blocks(image *img)
  {
    return get_directive_function_blocks<block_directive>(img);
  }

vector<block_function> program::get_function_blocks(image *img)
  {
    return get_directive_function_blocks<block_function>(img);
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
