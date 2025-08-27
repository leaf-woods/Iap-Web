iap_cv_base=/home/linye020603/iap-web/cv
dir_util_tree=$(iap_cv_base)/util/tree
dir_util_print=$(iap_cv_base)/util/print

INCLUDES = -I$(dir_util_print) -I$(dir_util_tree) -I/usr/include/opencv4
#LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : test
test : bstreeTest.o bstree.o
	g++ -o test bstreeTest.o bstree.o 
bstreeTest.o : bstreeTest.cpp
	g++ -c bstreeTest.cpp $(INCLUDES)
bstree.o : bstree.cpp
	g++ -c bstree.cpp $(INCLUDES)

clean :
	rm  *.o 