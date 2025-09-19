iap_ghl_cv_base=/home/linye020603/iap-web/cv

dir_image=$(iap_ghl_cv_base)/image
dir_manage=$(iap_ghl_cv_base)/manage
dir_util=$(iap_ghl_cv_base)/util

INCLUDES = -I$(dir_image)/color \
           -I$(dir_image)/color/compare \
		   -I$(dir_image)/color/datatype/status \
		   -I$(dir_image)/region \
		   -I$(dir_manage) \
		   -I$(dir_util)/log \
           -I$(dir_util)/print \
           -I/usr/include/opencv4

LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

all : testRegion

testRegion : test_region.o region_builder.o region_evaluator.o pixel_comparator.o iapcv_log.o iap_print.o
	g++ -o testRegion test_region.o region_builder.o region_evaluator.o pixel_comparator.o iapcv_log.o iap_print.o $(LIBS)
test_region.o : test_region.cpp
	g++ -c test_region.cpp $(INCLUDES) 
region_builder.o : $(dir_image)/region/region_builder.cpp
	g++ -c $(dir_image)/region/region_builder.cpp $(INCLUDES)
region_evaluator.o : $(dir_image)/region/region_evaluator.cpp
	g++ -c $(dir_image)/region/region_evaluator.cpp $(INCLUDES)
pixel_comparator.o : $(dir_image)/color/compare/pixel_comparator.cpp
	g++ -c $(dir_image)/color/compare/pixel_comparator.cpp $(INCLUDES)
iapcv_log.o : $(dir_util)/log/iapcv_log.cpp
	g++ -c $(dir_util)/log/iapcv_log.cpp 
iap_print.o : $(dir_util)/print/iap_print.cpp
	g++ -c $(dir_util)/print/iap_print.cpp $(INCLUDES)

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testRegion))
	rm  testRegion
endif