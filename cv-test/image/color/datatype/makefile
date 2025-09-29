iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_image=$(iap_ghl_cv_base)/image
#dir_util=$(iap_ghl_cv_base)/util

INCLUDES = -I$(dir_image)/color/datatype -I$(dir_image)/region/datatype

#LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

all : testSubMatr testMatrixBounds

testSubMatr : testSubMatr.o 
	g++ -o testSubMatr testSubMatr.o 
testSubMatr.o : testSubMatr.cpp
	g++ -c testSubMatr.cpp $(INCLUDES)

testMatrixBounds : testMatrixBounds.o matrix_bounds.o
	g++ -o testMatrixBounds testMatrixBounds.o matrix_bounds.o
testMatrixBounds.o : testMatrixBounds.cpp
	g++ -c testMatrixBounds.cpp $(INCLUDES)
matrix_bounds.o : $(dir_image)/region/datatype/matrix_bounds.cpp
	g++ -c $(dir_image)/region/datatype/matrix_bounds.cpp $(INCLUDES)

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testSubMatr))
	rm  testSubMatr
endif
ifneq (,$(wildcard testMatrixBounds))
	rm  testMatrixBounds
endif