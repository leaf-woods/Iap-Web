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
        // We don't use const std::string.
        // https://stackoverflow.com/questions/7571278/how-do-i-define-string-constants-in-c
        const char* H_TRACE = "Trace: ";
        const char* H_DEBUG = "Debug: ";
        const char* H_INFO  = "Info: ";
        const char* H_WARN  = "Warn: ";
        const char* H_ERROR = "Error: ";

        int level = DEBUG;

    public:
        static string cnames;

    public:
        static const int TRACE = 0;
        static const int DEBUG = 1;
        static const int INFO = 2;
        static const int WARN = 3;
        static const int ERROR = 4;

    private:
        void cprintf(const char* fmt, va_list args);
    
    public:
        iapcv_log(string cname);
        /// TODO: Since iapcv_log is provided by iapcv_context, we need to find other ways to record all iapcv_log clients.
        iapcv_log() {} 

        void setLevel(int level);
        int getLevel();
        bool isDebug();
        
        void trace(string msg1);

        template<typename T>
        void trace(string msg1, T obj) {
            if (level == TRACE) {
                cout << H_TRACE << msg1 << " " << obj << endl;
            }
        }

        void ftrace(const char* fmt ...);

        void debug(string msg1);

        template<typename T>
        void debug(string msg1, T obj) {
            if (level <= DEBUG) {
                cout << H_DEBUG << msg1 << " " << obj << endl;
            }
        }
        void fdebug(const char* fmt ...);

        void info(string msg1);
        
        template<typename T>
        void info(string msg1, T obj) {
            if (level <= INFO) {
                cout << H_INFO << msg1 << " " << obj << endl;
            }
        }
        
        void finfo(const char* fmt, ...);

        void warn(string msg1);
        void warn(string msg1, int num);

        /*
         * @20250919
         * We cannot have function Warn() and Error().
         */
        void error(string msg1);  

        template<typename T>
        void error(string msg1, T obj) {
            if (level <= ERROR) {
                cout << H_ERROR << msg1 << " " << obj << endl;
            }
        }

        /*
         *************************************************************
         *  For customer classes that do not want to print log levels.
         *************************************************************
         */
        template<typename T>
        void Trace(string msg1, T obj) {
            if (level == TRACE) {
                cout << msg1 << " " <<obj << endl;
            }
        }

        void fTrace(const char* fmt, ...);

        void Debug(string msg);

        template<typename T>
        void Debug(string msg1, T obj) {
            if (level <= DEBUG) {
                cout << msg1 << " " << obj << endl;
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
        void trace_inline(string msg);
};

#endif