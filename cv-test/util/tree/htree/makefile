iap_cv_base=/home/linye020603/iap-web/cv
dir_image_color=$(iap_cv_base)/image/color
dir_util_log=$(iap_cv_base)/util/log
dir_util_tree=$(iap_cv_base)/util/tree
dir_util_print=$(iap_cv_base)/util/print
dir_util_tree_htree=$(iap_cv_base)/util/tree/htree

INCLUDES = -I$(dir_image_color) -I$(dir_util_log) -I$(dir_util_print) -I$(dir_util_tree) -I$(dir_util_tree_htree) -I/usr/include/opencv4
#LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : test
test : hsvtreeTest.o hsvtree.o iap_print.o iapcv_log.o
	g++ -o test hsvtreeTest.o hsvtree.o iap_print.o iapcv_log.o
hsvtreeTest.o : hsvtreeTest.cpp
	g++ -c hsvtreeTest.cpp $(INCLUDES)
hsvtree.o : $(dir_util_tree_htree)/hsvtree.cpp
	g++ -c $(dir_util_tree_htree)/hsvtree.cpp $(INCLUDES)
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