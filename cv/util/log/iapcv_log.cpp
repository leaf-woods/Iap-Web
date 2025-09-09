#include <cstdarg>
#include <iostream>

#include "iapcv_log.h"

string iapcv_log::cnames = "";
iapcv_log::iapcv_log(string cname) {
    cnames+=cname;
    cnames+=" ";
    //cout << "names: " << cnames << endl;
}

void iapcv_log::setLevel(int level) {
    if (level>=DEBUG && level<=ERROR) {
        this->level = level;
    }
    else {
        cout << "Error: invalid level: " << level << endl;
    }
}

int iapcv_log::getLevel() {
    return level;
}

bool iapcv_log::isDebug() {
    return level==DEBUG;
}

bool iapcv_log::isInfo() {
    return level==INFO;
}

bool iapcv_log::isWarn() {
    return level==WARN;
}

void iapcv_log::debug(string msg1) {
    if (level == DEBUG) {
        cout << "Debug: " << msg1 << endl;
    }
}

void iapcv_log::debug( string msg1, string msg2) {
    if (level == DEBUG) {
        cout << "Debug: " << msg1 << " " << msg2 << endl;
    }
}

void iapcv_log::debug( string msg1, int num) {
    if (level == DEBUG) {
        cout << "Debug: " << msg1 << " " << num << endl;
    }
}

void iapcv_log::debug( string msg1, string msg2, string msg3) {
    if (level == DEBUG) {
        cout << "Debug: " << msg1 << " " << msg2 << " " << msg3 << endl;
    }
}
        
void iapcv_log::info(string msg1) {
    if (level <= INFO) {
        cout << "Info: " << msg1 << endl;
    }
}

void iapcv_log::info( string msg1, string msg2) {
    if (level <= INFO) {
        cout << "Info: " << msg1 << " " << msg2 << endl;
    }
}

void iapcv_log::info( string msg1, string msg2, string msg3) {
    if (level <= INFO) {
        cout << "Info: " << msg1 << " " << msg2 << " " << msg3 << endl;
    }
}

void iapcv_log::warn( string msg1 ) {
    if (level <= WARN) {
        cout << "Warn: " << msg1 << endl;
    }
}

void iapcv_log::warn( string msg1, int num) {
    if (level <= WARN) {
        cout << "Warn: " << msg1 << " " << num << endl;
    }
}

void iapcv_log::warn( string msg1, string msg2) {
    if (level <= WARN) {
        cout << "Warn: " << msg1 << " " << msg2 << endl;
    }
}

void iapcv_log::warn( string msg1, string msg2, string msg3) {
    if (level <= WARN) {
        cout << "Warn: " << msg1 << " " << msg2 << " " << msg3 << endl;
    }
}
    
void iapcv_log::error( string msg) {
    if (level <= ERROR) {
        cout << "Error: " << msg << endl;
    }
}

void iapcv_log::error( string msg1, string msg2) {
    if (level <= ERROR) {
        cout << "Error: " << msg1 << msg2 << endl;
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

void iapcv_log::Info(string msg1) {
    if (level <= INFO) {
        cout << msg1 << endl;
    }
}

void iapcv_log::Info(string msg1, int num) {
    if (level <= INFO) {
        cout << "Info: " << msg1 << num << endl;
    }
}



