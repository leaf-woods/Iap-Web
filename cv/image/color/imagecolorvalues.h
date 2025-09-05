#ifndef IMAGECOLORVAL_H
#define IMAGECOLORVAL_H
class imagecolorvalues {
    public:
      static const size_t channel = 3;
      
      static const int BGR=100;
      static const int HSV=200;
      static const int MASKED=300;

    public:
      static std::string getColorTypeVal(int type) {
          if (type == BGR) {
              return "BGR";
          }
          if (type == HSV) {
             return "HSV";
          }
          if (type == MASKED) {
             return "Masked";
          }
          return nullptr;
      }
};
#endif