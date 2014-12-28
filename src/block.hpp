#ifndef BLOCK_H
#define BLOCK_H

#include "general.hpp"

/**
 Represents a flow_chart language block.
 */

class block
  {
    /* the block should have a pointer to an instruction in
       bytecode sequence, so that the blocks will be able to
       form structures like branshing on their own */

    protected:
      string block_string;
      coord_2d top_left;
      coord_2d bottom_right;

    public:
      block(string block_string,coord_2d top_left,coord_2d bottom_right);
      string get_string();

      /**<
       Gets the string inside the block.

       @return string in the block
       */

      coord_2d get_top_left();
      coord_2d get_bottom_right();
  };

class block_directive: public block
  {
    public:
      block_directive(string block_string,coord_2d top_left,coord_2d bottom_right);
  };

class block_function: public block
  {
    public:
      block_function(string block_string,coord_2d top_left,coord_2d bottom_right);
  };

class block_command: public block
  {
    public:
      block_command(string block_string,coord_2d top_left,coord_2d bottom_right);
  };

class block_branch: public block
  {
    public:
      block_branch(string block_string,coord_2d top_left,coord_2d bottom_right);
  };

#endif
