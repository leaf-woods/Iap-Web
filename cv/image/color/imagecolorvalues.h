#ifndef IMAGECOLORVALUES_H
#define IMAGECOLORVALUES_H

#include <string>

enum class ColorType {
    NA,
    BGR,
    HSV,
    MASKED,
    TRAINED
};

class imagecolorvalues {
    public:
      static const int NOT_AVAILABLE = -1;
      static const int INVALID_KEY = -1;
      
      static const size_t channel = 3;

      static const int BLACK  = 0;
      static const int PURPLE = 16711807;    // RGB: 127, 0, 255
      static const int BLUE   = 16711680;    // RGB: 0, 0, 255
      static const int GREEN  = 65280;       // RGB: 0, 255, 0
      static const int L50_GREEN  = 65407;   // RGB: 0, 255, 127
      static const int YELLOW = 65535;       // RGB: 255, 255, 0
      static const int L75_YELLOW = 8388607; // RGB: 255, 255, 127
      static const int ORANGE = 32767;       // RGB: 255, 127, 0
      static const int RED    = 255;         // RGB: 255, 0, 0

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
          if (type == ColorType::TRAINED) {
             return "Trained";
          }
          return "NA";
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
          return "Not Available";
      }
};
#endif