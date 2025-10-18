#ifndef IMAGECOLORVALUES_H
#define IMAGECOLORVALUES_H

#include <string>

enum class ColorType {
    NA,
    BGR,
    HSV,
    MASKED
};

class imagecolorvalues {
    public:
      static const int NOT_AVAILABLE = -1;
      
      static const size_t channel = 3;
      
      //static const int BGR=100;
      //static const int HSV=200;
      //static const int MASKED=300;

      static const int BLACK  = 0;
      static const int PURPLE = 8323327;  // 127, 0, 255
      static const int BLUE   = 255;      // 0, 0, 255
      static const int GREEN  = 65280;    // 0, 255, 0
      static const int L50_GREEN  = 65407;    // 0, 255, 127
      static const int YELLOW = 16776960; // 255, 255, 0
      static const int L75_YELLOW = 8388607; // 255, 255, 127
      static const int ORANGE = 16744192; // 255, 127, 0
      static const int RED    = 16711680; // 255, 0, 0

      static const int DELTA = 20;
      static const int M_DELTA = 15; 

    public:
      static std::string getColorTypeVal(ColorType type) {
          if (type == ColorType::BGR) {
              return "BGR";
          }
          if (type == ColorType::HSV) {
             return "HSV";
          }
          if (type == ColorType::MASKED) {
             return "Masked";
          }
          return nullptr;
      }

      static std::string getColorVal(int color) {
          switch (color) {
          case BLACK:
              return "Black";
              
          case PURPLE:
              return "Purple";
  
          case BLUE:
              return "Blue";
    
          case GREEN:
              return "Green";

          case L50_GREEN:
              return "L50_Green";
    
          case YELLOW:
              return "Yellow";

          case L75_YELLOW:
              return "L75_Yellow";
    
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