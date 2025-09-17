iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_image=$(iap_ghl_cv_base)/image

INCLUDES = -I$(dir_image)/color \
           -I$(dir_image)/color/compare \
           -I$(dir_image)/region \
		   -I/usr/include/opencv4

LIBS = -lopencv_core -lopencv_imgcodecs

all : testComparator

testComparator : testComparator.o pixel_comparator.o
	g++ -o testComparator testComparator.o pixel_comparator.o $(LIBS)
testComparator.o : testComparator.cpp
	g++ -c testComparator.cpp $(INCLUDES) 
pixel_comparator.o : $(dir_image)/color/compare/pixel_comparator.cpp
	g++ -c $(dir_image)/color/compare/pixel_comparator.cpp $(INCLUDES)

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testComparator))
	rm  testComparator
endif