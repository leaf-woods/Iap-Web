#include <iostream>
#include <stdexcept>

#include "iapcv_log.h"

string iapcv_log::cnames = "";
iapcv_log::iapcv_log(string cname) {
    cnames+=cname;
    cnames+=" ";
    //cout << "names: " << cnames << endl;
}

void iapcv_log::setLevel(int level) {
    if (level<TRACE || level>ERROR) {
        throw invalid_argument( "Invalid log level: " + to_string(level) );
    }
    this->level = level;
}

int iapcv_log::getLevel() {
    return level;
}

bool iapcv_log::isDebug() {
    return level==DEBUG;
}

// https://stackoverflow.com/questions/13294067/how-to-convert-string-to-char-array-in-c
/**
 * std::string variables and string literals are different in function cprintf(). They cannot be replaced
 * with each other when calling cprintf().
 */
void iapcv_log::cprintf(const char* fmt, va_list args) 
{
    while (*fmt != '\0')
    {
        if (*fmt == 's') {
            char* s = va_arg(args, char*);
            cout << string(s) << ' ';
        }
        else if (*fmt == 'v') {
            string s = va_arg(args, string);
            cout << string(s) << ' ';
        }   
        else if (*fmt == 'n') {
            int s = va_arg(args, int);
            cout << to_string(s) << ' ';
        }
        else if (*fmt == 'f')
        {
            double d = va_arg(args, double);
            cout << d << ' ';
        }
        else if (*fmt == 'p')
        {
            void* addr = va_arg(args, void*);
            cout << addr << ' ';
        }
        else {
            cout << endl;
            cout << "Error in logging process: Invalid format: " << *fmt << endl;
        }
        ++fmt;
    }
    cout << endl;
}

void iapcv_log::trace(string msg1) {
    if (level == TRACE) {
        cout << H_TRACE << msg1 << endl;
    }
}

void iapcv_log::debug(string msg1) {
    if (level <= DEBUG) {
        cout << H_DEBUG << msg1 << endl;
    }
}

void iapcv_log::fdebug(const char* fmt ...) {
    if (level <= DEBUG) {
        cout << H_DEBUG;
        va_list args;
        va_start(args, fmt);
        cprintf(fmt, args);
        va_end(args);
    }
}
       
void iapcv_log::info(string msg1) {
    if (level <= INFO) {
        cout << H_INFO << msg1 << endl;
    }
}

// https://cplusplus.com/reference/cstdio/vfprintf/
void iapcv_log::finfo(const char* fmt, ...) {
    if (level <= INFO) {
        cout << H_INFO;
        va_list args;
        va_start(args, fmt);
        cprintf(fmt, args);
        va_end(args);
    }
}

void iapcv_log::warn( string msg1 ) {
    if (level <= WARN) {
        cout << H_WARN << msg1 << endl;
    }
}

void iapcv_log::warn( string msg1, int num) {
    if (level <= WARN) {
        cout << H_WARN << msg1 << " " << num << endl;
    }
}

void iapcv_log::error( string msg) {
    if (level <= ERROR) {
        cout << H_ERROR << msg << endl;
    }
}

/*
 *************************************************************
 *  For customer classes that do not want to print log levels.
 *************************************************************
 */     
void iapcv_log::Debug(string msg) {
    if (level <= DEBUG) {
        cout << msg << endl;
    }
}

void iapcv_log::fTrace(const char* fmt ...) {
    if (level == TRACE) {
        va_list args;
        va_start(args, fmt);
        cprintf(fmt, args);
        va_end(args);
    }
}

void iapcv_log::Info(string msg1) {
    if (level <= INFO) {
        cout << msg1 << endl;
    }
}

void iapcv_log::Info(string msg1, int num) {
    if (level <= INFO) {
        cout << msg1 << " " << num << endl;
    }
}

/*
 *************************************************************
 *  For customer classes that print without new line.
 *************************************************************
 */  
 void iapcv_log::debug_inline(string msg) {
    if (level <= DEBUG) {
        cout << H_DEBUG << " " << msg << " ";
    }
}



