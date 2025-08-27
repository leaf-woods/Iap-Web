#ifndef IMAGECOLORVAL_H
#define IMAGECOLORVAL_H
class imagecolorvalues {
    public:
      static const int BGR=100;
      static const int HSV=200;

    public:
      static std::string getColorTypeVal(int type) {
          if (type == BGR) {
              return "BGR";
          }
          if (type == HSV) {
             return "HSV";
          }
          return nullptr;
      }
};
#endif