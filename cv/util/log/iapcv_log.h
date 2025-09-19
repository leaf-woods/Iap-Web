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
#include <cassert>
#include <cstdarg>
#include <stdio.h>
#include <time.h>

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
  /*
   * @20250917
   * One arg: string
   * Two args: string, T
   * More than two args: variadic function
   *
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
        void cprintf(const char* fmt, va_list args);
    
    public:
        iapcv_log(string cname);
        
        void setLevel(int level);
        int getLevel();
        bool isDebug();
        void debug(string msg1);

        template<typename T>
        void debug(string msg1, T obj) {
            if (level == DEBUG) {
                cout << "Debug: " << msg1 << " " << obj << endl;
            }
        }
        void fdebug(const char* fmt ...);

        void info(string msg1);
        
        template<typename T>
        void info(string msg1, T obj) {
            if (level <= INFO) {
                cout << "Info: " << msg1 << " " << obj << endl;
            }
        }
        
        void finfo(const char* fmt, ...);

        void warn(string msg1);
        void warn(string msg1, int num);

        void error(string msg1);  

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

        void fDebug(const char* fmt, ...);

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