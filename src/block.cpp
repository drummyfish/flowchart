#include "block.hpp"

block::block(string block_string)
  {
    this->block_string = block_string;
  }

block_function::block_function(string block_string): block(block_string)
  {
  }

string block::get_string()
  {
    return this->block_string;
  }
