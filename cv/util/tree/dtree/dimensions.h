#ifndef DIMENSIONS_H
#define DIMENSIONS_H
enum class DimType {
    BGR,
    HSV,
    XYZ
};

class dimensions {
  public: 
    /*
     * Current available dimensions.
     */
    const static int D_X = 0;
    const static int D_Y = 1;
    const static int D_Z = 2;
      
    const static int HUE = 0;
    const static int SAT = 1;
    const static int VAL = 2;

    const static int B = 0;
    const static int G = 1;
    const static int R = 2;

  public:
    static std::string toString(DimType type, int which) {
        switch(type) {
            case DimType::XYZ:
            switch(which) {
                case D_X:
                  return "X";
                case D_Y:
                  return "Y";
                case D_Z:
                  return "Z";
            break;
            }
            
            case DimType::HSV:
            switch(which) {
                case HUE:
                  return "HUE";
                case SAT:
                  return "SAT";
                case VAL:
                  return "VAL";
            break;
            }
            
            case DimType::BGR:  
            switch(which) {
                case B:
                  return "B";
                case G:
                  return "G";
                case R:
                  return "R";
            break;
            }
            
        break;
        }
        return nullptr;
    }

    static std::string toString(DimType type) {
        switch(type) {
            case DimType::XYZ:
              return "XYZ";
            case DimType::HSV:
              return "HSV";
            case DimType::BGR:
              return "BGR";
        break;
        }
        return nullptr;
    }
};
#endif