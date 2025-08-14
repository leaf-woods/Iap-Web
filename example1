all : example1
example1 : example1.o imagecolordesc.o convertnumber.o colorvaluetree.o
	g++ -o example1 example1.o imagecolordesc.o convertnumber.o colorvaluetree.o -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
example1.o : example1.cpp
	g++ -c example1.cpp -I/usr/include/opencv4 
imagecolordesc.o: imagecolordesc.cpp
	g++ -c imagecolordesc.cpp -I/usr/include/opencv4
convertnumber.o : convertnumber.cpp
	g++ -c convertnumber.cpp -I/usr/include/opencv4
colorvaluetree.o : ./vtree/colorvaluetree.cpp
	g++ -c ./vtree/colorvaluetree.cpp

clean :
	rm example1 *.o example1.log
