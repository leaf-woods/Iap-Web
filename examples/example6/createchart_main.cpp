#include <iostream>

#include "convert_bgrhsv.h"
#include "createhsvchart.h"

int main(int argc, char* argv[]) {
    convert_bgrhsv* convert = new convert_bgrhsv();
    createhsvchart* chart = new createhsvchart();

    chart->setFileName("IMG_4624_S_CHT.JPG");
    chart->setConvertHSV(convert);
    chart->createChart(217.0);

    uchar b=255;  uchar g=255;  uchar r=255;
    chart->createChart(b, g, r);

    b=0;  g=0;  r=0;
    chart->createChart(b, g, r);

    delete convert;
    delete chart;
    return 0;
}