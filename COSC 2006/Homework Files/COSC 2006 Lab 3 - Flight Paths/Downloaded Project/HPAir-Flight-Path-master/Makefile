# Sample Makefile for reference.
# created by bjuliano@csuchico.edu

# Instructions:
#   1) Replace "driver" in line 10 (under TARGET) with the name of the executable.
#   2) Replace "sample0.o sample0-tester.o" in line 11 (under OBJS) with the names of the object files.
#   3) Check and make sure the flags in line 14 are the ones you need for your project.
#   4) Save and use by typing "make" on the command line.

TARGET       = HPAir
OBJS         = HPAir.o
REBUILDABLES = $(TARGET) $(OBJS)
CC           = g++
FLAGS        = -g -Wall -pedantic -std=c++11
OTHERFLAGS   = -lstdc++
INCLIB       =

# Note: You shouldn't have to change anything below this line.

# Driver rules ...
$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $(OTHERFLAGS) -o $@ $^ $(INCLIB)

# Standard rules ...
%.o: %.cpp
	$(CC) $(FLAGS) -o $@ -c $<

# Additional make options ...
clean:
	@rm -f $(REBUILDABLES)
	@echo "All rebuildables deleted!"