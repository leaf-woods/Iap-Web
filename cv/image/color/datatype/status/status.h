#ifndef STATUS_H
#define STATUS_H
class status {
    public:
        static const int OK=0; 
        static const int ERROR=1;

    protected:
        int status_val;
        string msg;
};

class b_status : status{
    private:
        bool ret;

    public:
        b_status(int status_val, bool ret, string msg) {
            this->status_val = status_val;
            this->ret = ret;
            this->msg = msg;
        }

        b_status(int status_val, bool ret) {
            this->status_val = status_val;
            this->ret = ret;
            msg= "";
        }

        ~b_status() {
            status_val = 0;
            ret = false;
            msg = "";
        }
        
        int getStatusVal() {
            return status_val;
        }

        bool getRet() {
            return ret;
        }

        string getMsg() {
            return msg;
        }

        bool isOK() {
            return status_val == OK;
        }
};
#endif
