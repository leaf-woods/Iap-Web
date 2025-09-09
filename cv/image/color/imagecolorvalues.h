#ifndef IMAGECOLORVAL_H
#define IMAGECOLORVAL_H
class imagecolorvalues {
    public:
      static const size_t channel = 3;
      
      static const int BGR=100;
      static const int HSV=200;
      static const int MASKED=300;

      static const int BLACK=1000;
      static const int PURPLE=1010;
      static const int BLUE=1020;
      static const int GREEN=1030;
      static const int YELLOW=1040;
      static const int ORANGE=1050;
      static const int RED=1060;

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

      static std::string getColorVal(int color) {
          switch (color) {
          case BLACK:
              return "Black";
              //break;
          case PURPLE:
              return "Purple";
  
          case BLUE:
              return "Blue";
    
          case GREEN:
              return "Green";
    
          case YELLOW:
              return "Yellow";
    
          case ORANGE:
              return "Orange";
  
          case RED:
              return "Red";
          break;
          }
          return "Null";
      }
};
#endif