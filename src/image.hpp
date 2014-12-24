#ifndef IMAGE_H
#define IMAGE_H

/**
 @author Miloslav Číž
 */

#include <string>
#include "lodepng.hpp"
#include "bitmap_image.hpp"

using namespace std;

/**
 Represents a bitmap image that can be loaded from various file formats
 and then accessed by individual pixels.
 */

class image
  {
    protected:
      bitmap_image *bmp_image;  // this is used for handling the images internally

      inline void delete_image();

    public:
      image();
      ~image();

      bool load_bmp(string filename);
      bool load_png(string filename);

      bool load_file(string filename);
      /**<
       Loads the image from a file, guessing the image format.

       @param filename name of the file to be loaded
       @return true on success, false otherwise
       */

      bool save_bmp(string filename);
      bool save_png(string filename);

      inline unsigned int get_width();

      inline unsigned int get_height();
      void get_pixel(const unsigned int x, const unsigned int y,
        unsigned char &red, unsigned char &green, unsigned char &blue);

      void set_pixel(const unsigned int x, const unsigned int y,
        const char &red, const char &green, const char &blue);
  };

#endif
