#ifndef STATUS_H
#define STATUS_H

#include "iclearable.h"

class status : iclearable {
    public:
        static const int NORMAL=0; 
        static const int ERROR =1;

    protected:
        /*
         * Indiates a function is successfully completed or not.
         * In case that error occurred, we set f_status to ERROR.
         * For a bool function, this tells the difference between a normal 
         * function return false and a failed completion of the function.

         * Example: For function isSky(), return false means input image is not sky.
         * Return status_val ERROR means the function is not completed due to
         * exceptions/errors. We don't know whether the input image is sky or not.
         */
        int f_status;
        std::string msg;
};

class bool_status : status{
    private:
        bool f_result;

    public:
        bool_status(int f_status, bool f_result, std::string msg) {
            this->f_status = f_status;
            this->f_result = f_result;
            this->msg = msg;
        }

        bool_status(int f_status, bool f_result) {
            this->f_status = f_status;
            this->f_result = f_result;
            msg= "";
        }

        ~bool_status() {
            f_status = 0;
            f_result = false;
            msg = "";
        }
        
        int getStatus() {
            return f_status;
        }

        bool getResult() {
            return f_result;
        }

        std::string getMsg() {
            return msg;
        }

        bool isNormal() {
            return f_status == NORMAL;
        }

        void setResult(bool rv) {
            f_result = rv;
        }

        void setStatus(int status) {
            f_status = status;
        }

        void setMsg(std::string msg) {
            this->msg = msg;
        }

        void clear() {
            f_result = false;
            f_status = NORMAL;
            msg = "";
        }
};
#endif
