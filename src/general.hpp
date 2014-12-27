#ifndef GENERAL_H
#define GENERAL_H

#include <string>
#include <iostream>
#include <algorithm>

#define FONT_PATH        "font.png"
#define FONT_WIDTH       7
#define FONT_HEIGHT      8
#define FONT_ROW_SYMBOLS 32

using namespace std;

#define is_black(r,g,b)  r == 0 && g == 0 && b == 0

typedef struct
  {
    unsigned int x;
    unsigned int y;
  } coord_2d;

typedef enum
  {
    ERROR_SYNTAX = 0,
    ERROR_SEMANTICS,
    ERROR_FILE,
    ERROR_OTHER
  } program_error_type;

typedef enum
  {
    // general:
    INSTRUCTION_ASSIGN = 0,      /// assign value to variable
    INSTRUCTION_EOF,             /// check if EOF has been reached
    INSTRUCTION_OPEN,            /// open file
    INSTRUCTION_CLOSE,           /// close file
    INSTRUCTION_WAIT,            /// wait for given amount of time
    INSTRUCTION_GARBAGE,         /// collect garbage (unreferenced lists)

    // arithmrtic:
    INSTRUCTION_ADD,             /// addition
    INSTRUCTION_SUB,             /// substraction
    INSTRUCTION_MULT,            /// multiplication
    INSTRUCTION_DIV,             /// division
    INSTRUCTION_MOD,             /// modulo

    // control:
    INSTRUCTION_IF,              /// conditional branching
    INSTRUCTION_JMP,             /// unconditional jump
    INSTRUCTION_CALL,            /// function call
    INSTRUCTION_RET,             /// return
    INSTRUCTION_HALT,            /// end the program

    // input/output:
    INSTRUCTION_PRINT,           /// print
    INSTRUCTION_PRINTLN,         /// print newline
    INSTRUCTION_READ,            /// read character
    INSTRUCTION_READLN,          /// read line

    // data types:
    INSTRUCTION_TYPE,            /// get data type of a variable
    INSTRUCTION_LEN,             /// get length of a list variable
    INSTRUCTION_LIST,            /// create a new list and put a pointer to it to a variable
  } instruction_type;

typedef struct
  {
    program_error_type type;
    string description;          // text description of the error
    coord_2d position;           // position in the image where the error appeared
  } program_error;

struct instruction_struct;
typedef instruction_struct instruction;

struct instruction_struct                   /**< bytecode instruction */
  {
    instruction_type type;

    unsigned int variable1;
    unsigned int variable2;

    instruction *jump;           // pointer to another instruction in case of branching etc.

  };

coord_2d make_coord(unsigned int x, unsigned int y);
void print_coord(coord_2d c);
int saturate(int value, int min, int max);
string trim_left(string s);
string trim_right(string s);
string trim(string s);

#endif
