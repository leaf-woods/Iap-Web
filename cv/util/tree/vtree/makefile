iap_cv_base=/home/linye020603/iap-web/cv
dir_tree=$(iap_cv_base)/util/tree
dir_print=$(iap_cv_base)/util/print

INCLUDES = -I$(dir_print) -I$(dir_tree) -I/usr/include/opencv4
#LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : test
test : colorvaluetreeTest.o colorvaluetree.o iap_print.o
	g++ -o test colorvaluetreeTest.o colorvaluetree.o iap_print.o
colorvaluetreeTest.o : colorvaluetreeTest.cpp
	g++ -c colorvaluetreeTest.cpp $(INCLUDES)
colorvaluetree.o : colorvaluetree.cpp 
	g++ -c colorvaluetree.cpp $(INCLUDES)
iap_print.o : $(dir_print)/iap_print.cpp
	g++ -c $(dir_print)/iap_print.cpp $(INCLUDES)

clean :
	rm  *.o 