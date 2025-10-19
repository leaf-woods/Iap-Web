# For any test that needs regioncontext.h

iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_context=$(iap_ghl_cv_base)/context
dir_image=$(iap_ghl_cv_base)/image
dir_io=$(iap_ghl_cv_base)/io
dir_manage=$(iap_ghl_cv_base)/manage
dir_stat=$(iap_ghl_cv_base)/statistics
dir_util=$(iap_ghl_cv_base)/util

CC = g++

#CFLAGS = -g -O -Wall -Wextra -Werror -Wfatal-errors -std=c99 -pedantic

INCLUDES = -I$(dir_context) \
           -I$(dir_image)/color \
           -I$(dir_image)/color/compare \
		   -I$(dir_image)/color/datatype \
		   -I$(dir_image)/color/datatype/status \
		   -I$(dir_image)/region \
		   -I$(dir_image)/region/datatype \
		   -I$(dir_image)/region/evaluate \
		   -I$(dir_image)/region/explore \
		   -I$(dir_image)/region/output \
		   -I$(dir_image)/train \
		   -I$(dir_io) \
		   -I$(dir_manage) \
		   -I$(dir_stat) \
		   -I$(dir_util)/convert \
		   -I$(dir_util)/log \
		   -I$(dir_util)/print \
           -I/usr/include/opencv4

LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

REGIONCTX_SRCS = $(dir_image)/color/compare/pixel_comparator.cpp \
       $(dir_image)/region/region_builder.cpp \
       $(dir_image)/region/region_print.cpp \
	   $(dir_image)/region/datatype/matrix_bounds.cpp \
	   $(dir_image)/region/evaluate/region_evaluator.cpp \
	   $(dir_image)/region/explore/region_explore.cpp \
	   $(dir_image)/region/explore/abstract_explore.cpp \
	   $(dir_image)/region/explore/simple_explore.cpp \
	   $(dir_image)/region/explore/explore_helper.cpp \
	   $(dir_image)/region/output/region_colors_provider.cpp \
       $(dir_stat)/get_stddev.cpp \
       $(dir_util)/log/iapcv_log.cpp \
       $(dir_util)/print/iap_print.cpp 

FACT_SKY_SRCS = $(dir_image)/train/sky_init_train.cpp \
			   $(dir_image)/train/fact_sky_init_train.cpp \
	           $(dir_io)/iapcv_env.cpp
               #$(dir_util)/print/iap_print.cpp 

SRCS = testGetStddev.cpp $(FACT_SKY_SRCS) $(REGIONCTX_SRCS)

OBJS = $(SRCS:.c=.o)

MAIN = testGetStddev

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