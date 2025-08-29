#include <iostream>

#include "convert_bgrhsv.h"
#include "createhsvchart.h"

int main(int argc, char* argv[]) {
    convert_bgrhsv* convert = new convert_bgrhsv();
    createhsvchart* chart = new createhsvchart();

    chart->setConvertHSV(convert);
    chart->createChart(217.0);

    delete convert;
    delete chart;
    return 0;
}