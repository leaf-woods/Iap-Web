exp1=../example1

#https://stackoverflow.com/questions/36381272/link-h-files-and-c-files-from-different-directory-using-makefile

# define the C compiler to use
CC = g++

# define any compile-time flags
#CFLAGS = -g -O -Wall -Wextra -Werror -Wfatal-errors -std=c99 -pedantic

# define any directories containing header files other than /usr/include
INCLUDES = -I/usr/include/opencv4

# define library paths in addition to /usr/lib
#LFLAGS = -L/Users/nguyenmanhduc/Documents/C\ library/cii/src

# define any libraries to link into executable:
LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

# define the C source files
SRCS = example2.cpp $(exp1)/imagecolordesc.cpp $(exp1)/convertnumber.cpp $(exp1)/vtree/colorvaluetree.cpp

# define the C object files 
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = example2
 
.PHONY: depend clean

all : $(MAIN)
	@echo  Simple compiler named example2 has been compiled

$(MAIN) : $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean :
	$(RM) *.o *~ $(MAIN)

depend : $(SRCS)
	makedepend $(INCLUDES) $^
