iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv

dir_ctx=$(iap_ghl_cv_base)/context
dir_image=$(iap_ghl_cv_base)/image
dir_manage=$(iap_ghl_cv_base)/manage
dir_util=$(iap_ghl_cv_base)/util

#https://stackoverflow.com/questions/36381272/link-h-files-and-c-files-from-different-directory-using-makefile

# define the C compiler to use
CC = g++

# define any compile-time flags
#CFLAGS = -g -O -Wall -Wextra -Werror -Wfatal-errors -std=c99 -pedantic

# define any directories containing header files other than /usr/include
INCLUDES = -I$(dir_ctx) \
           -I$(dir_image)/color \
		   -I$(dir_image)/color/datatype \
		   -I$(dir_image)/color/datatype/status \
		   -I$(dir_image)/color/space \
		   -I$(dir_image)/toolbox \
		   -I$(dir_manage) \
		   -I$(dir_util)/convert \
		   -I$(dir_util)/log \
           -I$(dir_util)/print \
		   -I$(dir_util)/tree \
           -I$(dir_util)/tree/dtree \
		   -I$(dir_util)/tree/vtree \
           -I/usr/include/opencv4

# define library paths in addition to /usr/lib
#LFLAGS = -L/Users/nguyenmanhduc/Documents/C\ library/cii/src

# define any libraries to link into executable:
LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

# define the C source files
SRCS = main.cpp \
	   $(dir_image)/color/imagecolordesc.cpp \
	   $(dir_image)/color/imagereader.cpp \
	   $(dir_image)/toolbox/sky.cpp \
       $(dir_util)/convert/convertnumber.cpp \
	   $(dir_util)/convert/convert_bgrhsv.cpp \
	   $(dir_util)/tree/vtree/colorvaluetree.cpp \
	   $(dir_util)/tree/dtree/d3tree.cpp \
	   $(dir_util)/log/iapcv_log.cpp \
	   $(dir_util)/print/iap_print.cpp 

# define the C object files 
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = main
 
.PHONY: depend clean

all : $(MAIN)
	@echo  Simple compiler named runtest has been compiled

$(MAIN) : $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean :
	$(RM) *.o *~ $(MAIN)

depend : $(SRCS)
	makedepend $(INCLUDES) $^
