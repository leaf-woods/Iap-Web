iap_cv_base=/home/linye020603/iap-web/cv
dir_util_log=$(iap_cv_base)/util/log
dir_util_print=$(iap_cv_base)/util/print
dir_util_tree=$(iap_cv_base)/util/tree
dir_util_tree_bstree=$(iap_cv_base)/util/tree/bstree

INCLUDES = -I$(dir_util_log) -I$(dir_util_print) -I$(dir_util_tree) -I$(dir_util_tree_bstree) -I/usr/include/opencv4
#LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : test
test : bstreeTest.o bstree.o iap_print.o iapcv_log.o
	g++ -o test bstreeTest.o bstree.o iap_print.o iapcv_log.o
bstreeTest.o : bstreeTest.cpp
	g++ -c bstreeTest.cpp $(INCLUDES)
bstree.o : $(dir_util_tree_bstree)/bstree.cpp
	g++ -c $(dir_util_tree_bstree)/bstree.cpp $(INCLUDES)

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