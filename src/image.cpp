#include "image.hpp"

image::image()
  {
    this->bmp_image = NULL;
  }

void image::delete_image()
  {
    if (this->bmp_image != NULL)
      delete this->bmp_image;

    this->bmp_image = NULL;
  }

image::~image()
  {
    this->delete_image();
  }

bool image::load_bmp(string filename)
  {
    this->delete_image();

    this->bmp_image = new bitmap_image(filename);

    if (!this->bmp_image->is_loaded())
      {
        this->delete_image();
        return false;
      }

    return true;
  }

bool image::load_png(string filename)
  {
    this->delete_image();

    unsigned char *pixel_data, r, g, b;
    unsigned int width, height, i, j, offset;

    if (lodepng_decode32_file(&pixel_data,&width,&height,filename.c_str()) != 0)
      return false;

    this->bmp_image = new bitmap_image(width,height);

    offset = 0;

    for (j = 0; j < height; j++)
      for (i = 0; i < width; i++)
        {
          r = pixel_data[offset];
          g = pixel_data[offset + 1];
          b = pixel_data[offset + 2];

          this->bmp_image->set_pixel(i,j,r,g,b);

          offset += 4;
        }

    return true;
  }

bool image::load_file(string filename)
  {
    if (this->load_png(filename))
      return true;

    if (this->load_bmp(filename))
      return true;

    return false;
  }

bool image::save_bmp(string filename)
  {
    if (this->bmp_image == NULL)
      return false;

    return this->bmp_image->save_image(filename);
  }

bool image::save_png(string filename)
  {
    if (this->bmp_image == NULL)
      return false;

    unsigned char *pixel_data, r, g, b;
    unsigned int i, j, offset;
    bool result;

    pixel_data = (unsigned char *) malloc(this->bmp_image->width() * this->bmp_image->height() * 3);

    offset = 0;

    for (j = 0; j < this->bmp_image->width(); j++)
      for (i = 0; i < this->bmp_image->width(); i++)
        {
          this->bmp_image->get_pixel(i,j,r,g,b);

          pixel_data[offset] = r;
          pixel_data[offset + 1] = g;
          pixel_data[offset + 2] = b;

          offset += 3;
        }

    result = (lodepng_encode24_file(filename.c_str(),pixel_data,
      this->bmp_image->width(),this->bmp_image->height()) == 0);

    free(pixel_data);

    return result;
  }

unsigned int image::get_width()
  {
    return this->bmp_image == NULL ? 0 : this->bmp_image->width();
  }

unsigned int image::get_height()
  {
    return this->bmp_image == NULL ? 0 : this->bmp_image->height();
  }

void image::get_pixel(const unsigned int x, const unsigned int y,
  unsigned char &red, unsigned char &green, unsigned char &blue)
  {
    if (this->bmp_image != NULL && x < this->bmp_image->width() && y < this->bmp_image->height())
      {
        this->bmp_image->get_pixel(x,y,red,green,blue);
      }
    else
      {
        red = 255;
        green = 255;
        blue = 255;
      }
  }

void image::set_pixel(const unsigned int x, const unsigned int y,
  const char &red, const char &green, const char &blue)
  {
    if (x >= this->bmp_image->width() || y >= this->bmp_image->height())
      return;

    if (this->bmp_image != NULL)
      this->bmp_image->set_pixel(x,y,red,green,blue);
  }

bool image::pixel_is_black(unsigned int x, unsigned int y)
  {
    unsigned char r,g,b;

    this->get_pixel(x,y,r,g,b);

    return r == 0 && g == 0 && b == 0;
  }
