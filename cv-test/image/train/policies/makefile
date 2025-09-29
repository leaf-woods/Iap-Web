iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_context=$(iap_ghl_cv_base)/context
dir_io=$(iap_ghl_cv_base)/io
dir_image=$(iap_ghl_cv_base)/image
dir_manage=$(iap_ghl_cv_base)/manage
dir_util=$(iap_ghl_cv_base)/util

INCLUDES = -I$(dir_context) \
           -I$(dir_image)/color \
           -I$(dir_image)/color/compare \
		   -I$(dir_image)/color/datatype \
		   -I$(dir_image)/color/datatype/status \
		   -I$(dir_image)/region \
		   -I$(dir_image)/region/datatype \
		   -I$(dir_image)/region/explore \
		   -I$(dir_image)/train \
		   -I$(dir_io) \
		   -I$(dir_manage) \
		   -I$(dir_util)/convert \
		   -I$(dir_util)/log \
           -I$(dir_util)/print \
           -I/usr/include/opencv4

LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

OBJS = testBorders.o \
       region_builder.o region_explore.o region_evaluator.o region_print.o \
	   matrix_bounds.o \
	   pixel_comparator.o \
	   iapcv_log.o iap_print.o \
	   sky_init_train.o iapcv_env.o
	
all : testBorders

testBorders : $(OBJS)
	g++ -o testBorders $(OBJS) $(LIBS)
testBorders.o : testBorders.cpp
	g++ -c testBorders.cpp $(INCLUDES)
test_region.o : test_region.cpp
	g++ -c test_region.cpp $(INCLUDES) 
region_builder.o : $(dir_image)/region/region_builder.cpp
	g++ -c $(dir_image)/region/region_builder.cpp $(INCLUDES)
region_explore.o : $(dir_image)/region/explore/region_explore.cpp
	g++ -c $(dir_image)/region/explore/region_explore.cpp $(INCLUDES)
region_print.o : $(dir_image)/region/region_print.cpp
	g++ -c $(dir_image)/region/region_print.cpp $(INCLUDES)
region_evaluator.o : $(dir_image)/region/region_evaluator.cpp
	g++ -c $(dir_image)/region/region_evaluator.cpp $(INCLUDES)
matrix_bounds.o : $(dir_image)/region/datatype/matrix_bounds.cpp
	g++ -c $(dir_image)/region/datatype/matrix_bounds.cpp $(INCLUDES)
pixel_comparator.o : $(dir_image)/color/compare/pixel_comparator.cpp
	g++ -c $(dir_image)/color/compare/pixel_comparator.cpp $(INCLUDES)
iapcv_log.o : $(dir_util)/log/iapcv_log.cpp
	g++ -c $(dir_util)/log/iapcv_log.cpp 
iap_print.o : $(dir_util)/print/iap_print.cpp
	g++ -c $(dir_util)/print/iap_print.cpp $(INCLUDES)
sky_init_train.o : $(dir_image)/train/sky_init_train.cpp
	g++ -c $(dir_image)/train/sky_init_train.cpp $(INCLUDES)
iapcv_env.o : $(dir_io)/iapcv_env.cpp
	g++ -c $(dir_io)/iapcv_env.cpp

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testBorders))
	rm  testBorders
endif