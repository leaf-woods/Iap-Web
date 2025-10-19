iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_context=$(iap_ghl_cv_base)/context
dir_io=$(iap_ghl_cv_base)/io
dir_image=$(iap_ghl_cv_base)/image
dir_manage=$(iap_ghl_cv_base)/manage
dir_stat=$(iap_ghl_cv_base)/statistics
dir_util=$(iap_ghl_cv_base)/util

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

REGION_CTX_OBJS = matrix_bounds.o \
                  region_builder.o \
				  region_colors_provider.o \
                  region_explore.o \
				  region_evaluator.o \
				  region_print.o \
	              pixel_comparator.o \
				  get_stddev.o \
				  explore_helper.o \
				  simple_explore.o \
				  abstract_explore.o \
	              iapcv_log.o iap_print.o \

FACT_SKY_INIT_OBJS = sky_init_train.o fact_sky_init_train.o iapcv_env.o

OBJS = $(FACT_SKY_INIT_OBJS) $(REGION_CTX_OBJS)
	   
all : testBorders testCloud

testBorders : testBorders.o $(OBJS)
	g++ -o testBorders testBorders.o $(OBJS) $(LIBS)
testBorders.o : testBorders.cpp
	g++ -c testBorders.cpp $(INCLUDES)

### REGION_CTX
matrix_bounds.o : $(dir_image)/region/datatype/matrix_bounds.cpp
	g++ -c $(dir_image)/region/datatype/matrix_bounds.cpp $(INCLUDES)
region_builder.o : $(dir_image)/region/region_builder.cpp
	g++ -c $(dir_image)/region/region_builder.cpp $(INCLUDES)
region_explore.o : $(dir_image)/region/explore/region_explore.cpp
	g++ -c $(dir_image)/region/explore/region_explore.cpp $(INCLUDES)
simple_explore.o : $(dir_image)/region/explore/simple_explore.cpp
	g++ -c $(dir_image)/region/explore/simple_explore.cpp $(INCLUDES)
abstract_explore.o : $(dir_image)/region/explore/abstract_explore.cpp
	g++ -c $(dir_image)/region/explore/abstract_explore.cpp $(INCLUDES)
explore_helper.o : $(dir_image)/region/explore/explore_helper.cpp
	g++ -c $(dir_image)/region/explore/explore_helper.cpp $(INCLUDES)
region_print.o : $(dir_image)/region/region_print.cpp
	g++ -c $(dir_image)/region/region_print.cpp $(INCLUDES)
region_evaluator.o : $(dir_image)/region/evaluate/region_evaluator.cpp
	g++ -c $(dir_image)/region/evaluate/region_evaluator.cpp $(INCLUDES)
pixel_comparator.o : $(dir_image)/color/compare/pixel_comparator.cpp
	g++ -c $(dir_image)/color/compare/pixel_comparator.cpp $(INCLUDES)
region_colors_provider.o : $(dir_image)/region/output/region_colors_provider.cpp
	g++ -c $(dir_image)/region/output/region_colors_provider.cpp $(INCLUDES)
get_stddev.o : $(dir_stat)/get_stddev.cpp
	g++ -c $(dir_stat)/get_stddev.cpp $(INCLUDES)
iapcv_log.o : $(dir_util)/log/iapcv_log.cpp
	g++ -c $(dir_util)/log/iapcv_log.cpp 
iap_print.o : $(dir_util)/print/iap_print.cpp
	g++ -c $(dir_util)/print/iap_print.cpp $(INCLUDES)

### FACT_SKY_INIT
sky_init_train.o : $(dir_image)/train/sky_init_train.cpp
	g++ -c $(dir_image)/train/sky_init_train.cpp $(INCLUDES)
fact_sky_init_train.o : $(dir_image)/train/fact_sky_init_train.cpp
	g++ -c $(dir_image)/train/fact_sky_init_train.cpp $(INCLUDES)
iapcv_env.o : $(dir_io)/iapcv_env.cpp
	g++ -c $(dir_io)/iapcv_env.cpp

testCloud : testCloud.o $(OBJS)
	g++ -o testCloud testCloud.o $(OBJS) $(LIBS)
testCloud.o : testCloud.cpp
	g++ -c testCloud.cpp $(INCLUDES)


clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testBorders))
	rm  testBorders
endif
ifneq (,$(wildcard testCloud))
	rm  testCloud
endif