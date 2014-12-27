#ifndef PROGRAM_H
#define PROGRAM_H

/**
 @author Miloslav Číž
 */

#include <vector>
#include "general.hpp"
#include "image.hpp"
#include "block.hpp"

/**
 Represents a program in flow_chart.
 */

template<typename T>    // these three are needed for template branching
struct switch_value {};

template<>
struct switch_value<block_directive>
{
  enum { value = 0 };
};

template<>
struct switch_value<block_function>
{
  enum { value = 1 };
};

class program
  {
    protected:
      image font_mask;

      int char_from_image_position(image *img, coord_2d c);

      /**<
       Compares all flow_chart font characters to given area in image
       whether it matches any and if so, the character is returned.

       @param img image in which the character should be compared
       @param c character top left coordinate in the image

       @return character ASCII code or -1 if no character was matched
       */

      string string_from_image_position(image *img, coord_2d c, unsigned int max_x, bool &success);

      /**<
       Tries to read a string written in given image and at given
       position in flow_chart font. The string to be read must consist
       of at least one character that has at least one black pixel in
       it in order to be succesfully read.

       @param img image from which the string should be read
       @param c string top left coordinate in the image
       @param max_x maximum x coordinate to which the string should be
              read
       @param success in this variable a success flag will be returned
              (true - string read succesfully, false otherwise)

       @return the string that was read with leading and trailing spaces
               stripped in case of success or "" in case the string
               could not be read
       */

      string string_from_image_area(image *img, coord_2d c1, coord_2d c2, bool &error);

      /**<
       Finds a string in given area of given image, reads it and
       returns it. The string must be written with black color in
       flow_chart bitmap font and must be on one line. There must not be
       any other black pixels in the area besides the ones in the text.

       @param img
       @param c1 top left corner coordinate of the area rectangle
       @param c2 bottom right corner coordinate of the area rectangle
       @param error in this variable the information whether any error
              occured will be returned
       @return extracted string or "" in case there is none or if there
               was an error

       */

      template<class T>
      vector<T> get_directive_function_blocks(image *img);
      /**<
       Helper function for get_function_blocks and get_directive_blocks.
       T is either block_directive or block_function.

       @param img image
       @return list of blocks
       */

      vector<block_directive> get_directive_blocks(image *img);

      /**<
       Gets all directive blocks in given image as a list.

       @param img image
       @return vector of directive_blocks
       */

      vector<block_function> get_function_blocks(image *img);

    public:
      bool load_from_file(string filename);

      /**<
       Loads the program from given file and compiles it into bytecode.

       @param filename name of the program file (image)
       @return true on success, false otherwise (call get_errors() for
               error details)
       */

      vector<program_error> get_errors();

      /**<
       Gets a list of errors that occured in the program since this
       object was created.

       @return list of errors
       */
  };


#endif
