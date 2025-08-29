iap_cv_base=/home/linye020603/iap-web/cv
dir_util_convert=$(iap_cv_base)/util/convert

INCLUDES = -I$(dir_util_convert) -I/usr/include/opencv4
LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all : main

main : createchart_main.o createhsvchart.o convert_bgrhsv.o
	g++ -o main createchart_main.o createhsvchart.o convert_bgrhsv.o $(LIBS)
createchart_main.o : createchart_main.cpp
	g++ -c createchart_main.cpp $(INCLUDES) 
createhsvchart.o : createhsvchart.cpp
	g++ -c createhsvchart.cpp $(INCLUDES)	
convert_bgrhsv.o : $(dir_util_convert)/convert_bgrhsv.cpp
	g++ -c $(dir_util_convert)/convert_bgrhsv.cpp $(INCLUDES)

clean :
	rm *.o