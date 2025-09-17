#ifndef IAPCV_LOG_H
#define IAPCV_LOG_H

//https://en.cppreference.com/w/c/language/variadic.html
/*
 * Variadic function provides a way to code clean but performance
 * is downgraded. Unless iapcv_log becomes really long, we do not
 * use variadic functions.
 *
 * We do not use template for the same reason, except debugging tree 
 * node addresses.
 * 
 * IAP-CV is generally a one time operation/computing for every input 
 * image. It is created for what has happened in these years. Therefore
 * we use a logger to ensure the correctness of code as accuracy is more
 * important of IAP-CV.
 */
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#include <iostream>
#include <string>
using namespace std;

/*
 * @20250902 
 * Since iap-web cv (analysis part) is not a web application, timestamp is not necessary.
 */
/*
 * This header file is created under not normal scenario.
 * Usage: Custom class calls setLevel(int level).
 * If level == INFO, then logger->debug(msg) will be ignored.
 */
 /*
  * @20250909
  * https://en.cppreference.com/w/cpp/language/unqualified_lookup.html
  * https://stackoverflow.com/questions/55119673/overload-resolution-order-of-defined-functions-and-templates
  * We have to ensure declaration order when template is used in overloading.
  */
class iapcv_log {
    private: 
        int level = DEBUG;

    public:
        static string cnames;

    public:
        static const int DEBUG = 0;
        static const int INFO = 1;
        static const int WARN = 2;
        static const int ERROR = 3;

    private:
        // https://stackoverflow.com/questions/611263/efficient-string-concatenation-in-c
        // strlen: https://en.cppreference.com/w/cpp/string/byte/strlen.html

        // 找来找去， 找不到最简单的dyanmic number of parameters passing, 没有定义和sample
        // 但是stackoverflow有个诱饵。 并且是错的。为什么是错的？因为那个strlen. No efficiency improvement.
        // 然后所有的网页找不到定义和description.
        // cplusplus.com 网页有问题。点击下面那个c link, 出来这个log例子。叶海唐女士微微一笑：妹妹！姐姐就是喜欢这样玩你！骚逼！
        // 后面有男人的低声讨论声音
        // cplusplus.com 给出的C funtion is wrong. Can't compile.

        /*
         * linye020603@penguin:~/iap-web/cv/image/toolbox$ make
g++  -I/home/linye020603/iap-web/cv/context -I/home/linye020603/iap-web/cv/image/color -I/home/linye020603/iap-web/cv/image/color/datatype -I/home/linye020603/iap-web/cv/image/color/space -I/home/linye020603/iap-web/cv/manage -I/home/linye020603/iap-web/cv/util/convert -I/home/linye020603/iap-web/cv/util/log -I/home/linye020603/iap-web/cv/util/print -I/home/linye020603/iap-web/cv/util/tree -I/home/linye020603/iap-web/cv/util/tree/htree -I/home/linye020603/iap-web/cv/util/tree/vtree -I/usr/include/opencv4 -o test_sky test_sky.cpp sky.cpp /home/linye020603/iap-web/cv/image/color/imagecolordesc.cpp /home/linye020603/iap-web/cv/image/color/imagereader.cpp /home/linye020603/iap-web/cv/util/convert/convertnumber.cpp /home/linye020603/iap-web/cv/util/convert/convert_bgrhsv.cpp /home/linye020603/iap-web/cv/util/tree/vtree/colorvaluetree.cpp /home/linye020603/iap-web/cv/util/tree/htree/hsvtree.cpp /home/linye020603/iap-web/cv/util/print/iap_print.cpp -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
In file included from sky.h:9,
                 from test_sky.cpp:5:
/home/linye020603/iap-web/cv/util/log/iapcv_log.h: In member function ‘void iapcv_log::tlog(const char*, ...)’:
/home/linye020603/iap-web/cv/util/log/iapcv_log.h:54:64: error: lvalue required as unary ‘&’ operand
   54 |             strftime(msg, sizeof msg, "%T", localtime(&(time_t){time(NULL)}));
      |                                                                ^~~~~~~~~~~~
In file included from sky.h:9,
                 from sky.cpp:1:
/home/linye020603/iap-web/cv/util/log/iapcv_log.h: In member function ‘void iapcv_log::tlog(const char*, ...)’:
/home/linye020603/iap-web/cv/util/log/iapcv_log.h:54:64: error: lvalue required as unary ‘&’ operand
   54 |             strftime(msg, sizeof msg, "%T", localtime(&(time_t){time(NULL)}));
      |                                                                ^~~~~~~~~~~~
make: *** [makefile:59: test_sky] Error 1
linye020603@penguin:~/iap-web/cv/image/toolbox$ 
         */
        void tlog(const char* fmt,...) {
            cout << "tlog" << endl;
            char msg[50];
            //strftime(msg, sizeof msg, "%T", localtime(&(time_t){time(NULL)}));
            //printf("[%s] ", msg);
            va_list args;
            va_start(args, fmt);
            vprintf(fmt, args);
            va_end(args);
        }
        
    public:
        iapcv_log(string cname);
        
        void setLevel(int level);
        int getLevel();
        bool isDebug();
        bool isInfo();
        bool isWarn();
        void debug(string msg1);
        void debug(string msg1, int num);
        void debug(string msg1, string msg2);

        template<typename T>
        void debug(string msg1, T obj) {
            if (level == DEBUG) {
                cout << "Debug: " << msg1 << " " << obj << endl;
            }
        }

        void debug(string msg1, string msg2, string msg3);

        //https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
        template <typename T>
        void debug(T t) 
        {
            cout << t << std::endl ;
        }
        
        template<typename T, typename... Args>
        void debug(T t, Args... args) 
        {
            cout << t << " ";
            debug(args...);
            cout << endl;
        }

        void info(string msg1);
        void info(string msg1, string msg2);
        
        template<typename T>
        void info(string msg1, T obj) {
            if (level <= INFO) {
                cout << "Info: " << msg1 << " " << obj << endl;
            }
        }
        
        void info(string msg1, string msg2, string msg3);
        
        void warn(string msg1);
        void warn(string msg1, int num);
        void warn(string msg1, string msg2);
        void warn(string msg1, string msg2, string msg3);

        void error(string msg1);  
        void error( string msg1, string msg2);
        template<typename T>
        void error(string msg1, T obj) {
            if (level <= ERROR) {
                cout << "Error: " << msg1 << " " << obj << endl;
            }
        }

        /*
         *************************************************************
         *  For customer classes that do not want to print log levels.
         *************************************************************
         */
        void Debug(string msg);

        template<typename T>
        void Debug(string msg1, T obj) {
            if (level == DEBUG) {
                cout << msg1 << obj << endl;
            }
        }

        template<typename T>
        void Debug(string msg1, int num, string msg2, T obj) {
            if (level == DEBUG) {
                cout << msg1 << num << msg2 << obj << endl;
            }
        }
       
        void Info(string msg);
        void Info(string msg1, int num);

        /*
         *************************************************************
         *  For customer classes that print without new line.
         *************************************************************
         */ 
        void debug_inline(string msg);
};

#endif