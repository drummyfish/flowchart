CXX=c++
CXXFLAGS=-pedantic -Wall -std=c++11 -g -O2

SRCDIR=src
OBJFILES=$(SRCDIR)/lodepng.o $(SRCDIR)/interpreter.o $(SRCDIR)/image.o $(SRCDIR)/program.o $(SRCDIR)/general.o

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
BIN=interpreter
else
BIN=interpreter.exe
endif

.PHONY:all clean

all: $(BIN)

$(BIN): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(SRCDIR)/*.o $(SRCDIR)/*.d $(BIN) $(ANIMBIN)

-include $(OBJFILES:.o=.d)
