#ifndef PROGRAM_H
#define PROGRAM_H

/**
 @author Miloslav Číž
 */

#include <vector>
#include "general.hpp"
#include "image.hpp"

/**
 Represents a program in flow_chart.
 */

class program
  {
    protected:
      image font_mask;

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
