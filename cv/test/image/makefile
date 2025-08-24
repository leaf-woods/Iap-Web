### A test build
#   Run shell script to ensure prod code is updated.
#   Use production code only
###

#iap_cv_base=/home/linye020603/iap-web/cv

#dir_ctx=$(iap_cv_base)/context
#dir_image=/home/linye020603/iap-web/cv/image
#dir_util=/home/linye020603/iap-web/cv/util

INCLUDES = -I/usr/include/opencv4
LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

#ctx_objs = iap_context.o imagecolordesc.o colorvaluetree.o hsvtree.o convertnumber.o convert_bgrhsv.o iap_print.o

all : runtest 

runtest : runtest.o test_img_data.o
	g++ -o runtest runtest.o test_img_data.o $(LIBS)

runtest.o : runtest.cpp
	g++ -c runtest.cpp $(INCLUDES)
test_img_data.o : test_img_data.cpp
	g++ -c test_img_data.cpp $(INCLUDES)

clean :
	rm  *.o
