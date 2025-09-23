iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_image=$(iap_ghl_cv_base)/image
dir_util=$(iap_ghl_cv_base)/util

INCLUDES = -I$(dir_image)/color \
           -I$(dir_image)/color/compare \
           -I$(dir_image)/region \
		   -I$(dir_util)/log \
		   -I$(dir_util)/print \
		   -I/usr/include/opencv4

LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

all : testComparator

testComparator : testComparator.o pixel_comparator.o imagereader.o iapcv_log.o iap_print.o
	g++ -o testComparator testComparator.o pixel_comparator.o imagereader.o iapcv_log.o iap_print.o $(LIBS)
testComparator.o : testComparator.cpp
	g++ -c testComparator.cpp $(INCLUDES) 
pixel_comparator.o : $(dir_image)/color/compare/pixel_comparator.cpp
	g++ -c $(dir_image)/color/compare/pixel_comparator.cpp $(INCLUDES)
imagereader.o : $(dir_image)/color/imagereader.cpp
	g++ -c $(dir_image)/color/imagereader.cpp $(INCLUDES)
iapcv_log.o : $(dir_util)/log/iapcv_log.cpp
	g++ -c $(dir_util)/log/iapcv_log.cpp $(INCLUDES)
iap_print.o : $(dir_util)/print/iap_print.cpp
	g++ -c $(dir_util)/print/iap_print.cpp $(INCLUDES)

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testComparator))
	rm  testComparator
endif