#include "block.hpp"

block::block(string block_string,coord_2d top_left,coord_2d bottom_right)
  {
    this->block_string = block_string;
    this->top_left = top_left;
    this->bottom_right = bottom_right;
  }

block_function::block_function(string block_string,coord_2d top_left,coord_2d bottom_right): block(block_string,top_left,bottom_right)
  {
  }

block_directive::block_directive(string block_string,coord_2d top_left,coord_2d bottom_right): block(block_string,top_left,bottom_right)
  {
  }

block_command::block_command(string block_string,coord_2d top_left,coord_2d bottom_right): block(block_string,top_left,bottom_right)
  {
  }

string block::get_string()
  {
    return this->block_string;
  }

coord_2d block::get_top_left()
  {
    return this->top_left;
  }

coord_2d block::get_bottom_right()
  {
    return this->bottom_right;
  }
