iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_image_color=$(iap_ghl_cv_base)/image/color
dir_util_log=$(iap_ghl_cv_base)/util/log
dir_util_tree=$(iap_ghl_cv_base)/util/tree
dir_util_print=$(iap_ghl_cv_base)/util/print
dir_util_tree_dtree=$(iap_ghl_cv_base)/util/tree/dtree

INCLUDES = -I$(dir_image_color) -I$(dir_util_log) -I$(dir_util_print) -I$(dir_util_tree) -I$(dir_util_tree_dtree) -I/usr/include/opencv4
#LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : test
test : d3treeTest.o d3tree.o iap_print.o iapcv_log.o
	g++ -o test d3treeTest.o d3tree.o iap_print.o iapcv_log.o
d3treeTest.o : d3treeTest.cpp
	g++ -c d3treeTest.cpp $(INCLUDES)
d3tree.o : $(dir_util_tree_dtree)/d3tree.cpp
	g++ -c $(dir_util_tree_dtree)/d3tree.cpp $(INCLUDES)
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