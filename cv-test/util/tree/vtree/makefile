iap_ghl_cv_base=/home/linye020603/iap-web/cv
dir_util_log=$(iap_ghl_cv_base)/util/log
dir_util_tree=$(iap_ghl_cv_base)/util/tree
dir_util_print=$(iap_ghl_cv_base)/util/print
dir_util_tree_vtree=$(iap_ghl_cv_base)/util/tree/vtree

INCLUDES = -I$(dir_util_log) -I$(dir_util_print) -I$(dir_util_tree) -I$(dir_util_tree_vtree) -I/usr/include/opencv4
#LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : test
test : colorvaluetreeTest.o colorvaluetree.o iap_print.o iapcv_log.o
	g++ -o test colorvaluetreeTest.o colorvaluetree.o iap_print.o iapcv_log.o
colorvaluetreeTest.o : colorvaluetreeTest.cpp
	g++ -c colorvaluetreeTest.cpp $(INCLUDES)
colorvaluetree.o : $(dir_util_tree_vtree)/colorvaluetree.cpp 
	g++ -c $(dir_util_tree_vtree)/colorvaluetree.cpp $(INCLUDES)
iap_print.o : $(dir_util_print)/iap_print.cpp
	g++ -c $(dir_util_print)/iap_print.cpp $(INCLUDES)
iapcv_log.o : $(dir_util_log)/iapcv_log.cpp
	g++ -c $(dir_util_log)/iapcv_log.cpp

clean :
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard test))
	rm  test
endif
