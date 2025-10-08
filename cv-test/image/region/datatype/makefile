iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_image=$(iap_ghl_cv_base)/image
#dir_util=$(iap_ghl_cv_base)/util

INCLUDES = -I$(dir_image)/region/datatype -I/usr/include/opencv4

#LIBS = -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

all : testBorderPixelDiffNode

testBorderPixelDiffNode : testBorderPixelDiffNode.o 
	g++ -o testBorderPixelDiffNode testBorderPixelDiffNode.o 
testBorderPixelDiffNode.o : testBorderPixelDiffNode.cpp
	g++ -c testBorderPixelDiffNode.cpp $(INCLUDES)

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testBorderPixelDiffNode))
	rm  testBorderPixelDiffNode
endif
