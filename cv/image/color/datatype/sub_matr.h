#ifndef SUB_MAT_H
#define SUB_MAT_H
class sub_matr {
  private: 
    static const int INVALID = -1;

    bool in_use;
    int row;
    int col;
    int num_rows;
    int num_cols;

    int sub_origin[2] = {0};
    int sub_diag[2] = {0};

  public:
    void setUse(bool use) {
        in_use = use;
        if (!in_use) {
          row = INVALID;
          col = INVALID;
          num_rows = INVALID;
          num_cols = INVALID;
          sub_origin[0] = INVALID;
          sub_origin[1] = INVALID;
          sub_diag[0] = INVALID;
          sub_diag[1] = INVALID;
        }
    }
    
    bool use() {
      return in_use;
    }

    void setSubMat(int r, int c, int num_rs, int num_cs) {
        row = r;
        col = c;
        num_rows = num_rs;
        num_cols = num_cs;

        sub_origin[0] = row;
        sub_origin[1] = col;
        sub_diag[0] = getBottomRow();
        sub_diag[1] = getRightCol();
        in_use = true;
    }

    int getTopRow() {
      return row;
    }

    int getLeftCol() {
      return col;
    }

    int getSubH() {
        return num_rows;
    }

    int getSubW() {
        return num_cols;
    }

    int getBottomRow() {
        return row + num_rows -1;
    }

    int getRightCol() {
        return col + num_cols -1;
    }

    int* getSubOriginal() {
        return sub_origin;
    }

    int* getSubDiag() {
        return sub_diag;
    }
};
#endif