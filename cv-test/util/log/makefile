iap_ghl_cv_base=/home/linye020603/github-local/Iap-Web/cv
dir_image=$(iap_ghl_cv_base)/image
dir_util_log=$(iap_ghl_cv_base)/util/log

INCLUDES = -I$(dir_util_log) -I$(dir_image)/color -I$(dir_image)/region -I/usr/include/opencv4
#LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : testLog
testLog : testLog.o iapcv_log.o
	g++ -o testLog testLog.o iapcv_log.o
testLog.o : testLog.cpp
	g++ -c testLog.cpp $(INCLUDES)
iapcv_log.o : $(dir_util_log)/iapcv_log.cpp
	g++ -c $(dir_util_log)/iapcv_log.cpp $(INCLUDES)

clean : 
ifneq (,$(wildcard *.o))
	rm  *.o
endif
ifneq (,$(wildcard testLog))
	rm  testLog
endif