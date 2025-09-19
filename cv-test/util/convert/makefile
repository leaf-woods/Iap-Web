iap_ghl_cv_base=/home/linye020603/iap-web/cv
dir_image_color=$(iap_ghl_cv_base)/image/color
dir_util_convert=$(iap_ghl_cv_base)/util/convert

INCLUDES = -I$(dir_image_color) -I$(dir_util_convert) -I/usr/include/opencv4
LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : bgrhsvTest testConvertnumber

bgrhsvTest : convert_bgrhsv_test.o convert_bgrhsv.o
	g++ -o bgrhsvTest convert_bgrhsv_test.o convert_bgrhsv.o $(LIBS)
convert_bgrhsv_test.o : convert_bgrhsv_test.cpp
	g++ -c convert_bgrhsv_test.cpp $(INCLUDES) 
convert_bgrhsv.o : $(dir_util_convert)/convert_bgrhsv.cpp
	g++ -c $(dir_util_convert)/convert_bgrhsv.cpp $(INCLUDES)

testConvertnumber : test_convertnumber.o convertnumber.o
	g++ -o testConvertnumber test_convertnumber.o convertnumber.o 
test_convertnumber.o : test_convertnumber.cpp
	g++ -c test_convertnumber.cpp $(INCLUDES)
convertnumber.o : $(dir_util_convert)/convertnumber.cpp
	g++ -c $(dir_util_convert)/convertnumber.cpp $(INCLUDES)

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard bgrhsvTest))
	rm  bgrhsvTest
endif
ifneq (,$(wildcard testConvertnumber))
	rm  testConvertnumber
endif