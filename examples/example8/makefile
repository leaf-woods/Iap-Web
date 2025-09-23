iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
#dir_util_convert=$(iap_ghl_cv_base)/util/convert

#INCLUDES = -I/usr/include/opencv4
#LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : test

test : test_general.o mtest.o
	g++ -o test test_general.o mtest.o

test_general.o : test_general.cpp
	g++ -c test_general.cpp  

m_test.o : m_test.cpp
	g++ -c m_test.cpp  

clean :
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard test))
	rm  test
endif