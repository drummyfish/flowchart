#ifndef PROGRAM_H
#define PROGRAM_H

/**
 @author Miloslav Číž
 */

#include <vector>
#include "general.h"

/**
 Represents a program in flow_chart.
 */

class program
  {
    protected:


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
