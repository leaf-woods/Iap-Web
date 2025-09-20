iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_image=$(iap_ghl_cv_base)/image
dir_util=$(iap_ghl_cv_base)/util

#https://stackoverflow.com/questions/36381272/link-h-files-and-c-files-from-different-directory-using-makefile

# define the C compiler to use
CC = g++

# define any compile-time flags
#CFLAGS = -g -O -Wall -Wextra -Werror -Wfatal-errors -std=c99 -pedantic

# define any directories containing header files other than /usr/include
INCLUDES = -I$(dir_image)/toolbox \
           -I$(dir_util)/print \
           -I/usr/include/opencv4

# define library paths in addition to /usr/lib
#LFLAGS = -L/Users/nguyenmanhduc/Documents/C\ library/cii/src

# define any libraries to link into executable:
LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

# define the C source files
SRCS = test_init_train.cpp \
       $(dir_image)/toolbox/sky_init_train.cpp \
	   $(dir_util)/print/iap_print.cpp 

# define the C object files 
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = test_init_train
 
.PHONY: depend clean

all : $(MAIN)
	@echo  Simple compiler named runtest has been compiled

$(MAIN) : $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.cpp.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean :
	$(RM) *.o *~ $(MAIN)

depend : $(SRCS)
	makedepend $(INCLUDES) $^
