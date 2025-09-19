#include <cstdarg>
#include <iostream>

#include "iapcv_log.h"

using namespace std;

//https://en.cppreference.com/w/cpp/utility/variadic.html
void simple_printf(const char* fmt...) // C-style "const char* fmt, ..." is also valid
{
    va_list args;
    va_start(args, fmt);
 
    while (*fmt != '\0')
    {
        if (*fmt == 's') {
            char* s = va_arg(args, char*);
            cout << string(s) << ' ';
        }
        else if (*fmt == 'n') {
            int s = va_arg(args, int);
            cout << to_string(s) << ' ';
        }
        else if (*fmt == 'f')
        {
            double d = va_arg(args, double);
            std::cout << d << ' ';
        }
        else if (*fmt == 'c')
        {
            // note automatic conversion to integral type
            int c = va_arg(args, int);
            std::cout << static_cast<char>(c) << ' ';
        }
        else if (*fmt == 'd')
        {
            int i = va_arg(args, int);
            std::cout << i << ' ';
        }
        ++fmt;
    }
    va_end(args);
    cout << endl;
}

void print(int n_args, ...) // C-style "const char* fmt, ..." is also valid
{
    va_list args;
    va_start(args, n_args);

    for (int i=0; i<n_args; i++) {
         char* s = va_arg(args, char*);
         cout << string(s) << ' ';
    }
    va_end(args);
    cout << endl;
}

int main(int argc, char* argv[]) {
    simple_printf("dcffsn", 3, 'a', 1.999, 42.5, "msg1", 1000);
    print(2, "msg1", "msg2");

    iapcv_log* log = new iapcv_log("testLog");
    
    log->debug("msg-debug");
    log->debug("msg-debug", "msg2");
    log->debug("msg-debug", 1000);
    assert(iapcv_log::DEBUG==log->getLevel());
    assert(log->isDebug());
    log->fdebug("sss", "msg1-debug", "variadic function used.", "msg3");
    log->fdebug("sns", "msg1-debug", 10, "msg3");
    log->fdebug("ssf", "msg1-debug", "msg2", 3.1415926);

    log->setLevel(iapcv_log::INFO);
    // Not printed: debug
    log->debug("msg-debug not shown.");
    
    log->setLevel(iapcv_log::DEBUG);
    log->Debug("msg-debug");
    log->Debug("msg-debug", "msg2");
    log->Debug("msg-debug", 1000);
    log->fDebug("sss", "msg1-debug", "variadic function used.", "Debug with no header.");
    log->fDebug("sns", "msg1-debug", 10, "Debug with no header.");
    log->fDebug("ssf", "msg1-debug", "msg2", 3.1415926);
    cout << endl;
    cout << "Test variadict function with wrong format." << endl;
    log->fDebug("ssd", "Message with wrong format.", "msg2", 3);
    cout << endl;
    log->fDebug("nsf", 10, "msg2", 3.1415926);
    cout << endl;

    log->setLevel(iapcv_log::INFO);
    // Not printed: Debug
    log->fDebug("sss", "msg1-debug", "msg2", "msg3");
    log->info("msg-info");
    log->info("msg-info", "msg2");
    log->info("msg-info", 1000);
    log->finfo("sss", "msg1-info", "msg2", "msg3");
    log->finfo("nsf", 10, "msg2", 3.1415926);
    cout << endl;

    log->setLevel(iapcv_log::WARN);
    // Not printed: Debug and info
    log->fDebug("sss", "msg1-debug", "not shown", "msg3");
    log->finfo("sss", "msg1-info", "not shown", "msg3");
    log->warn("msg1-warn:", 1000);
    cout << endl;

    log->setLevel(iapcv_log::ERROR);
    // Only error message printed
    log->debug("msg-debug");
    log->info("msg-info");
    log->warn("msg-warn");
    log->error("msg-error");
    log->error("msg-error", "msg2");
    log->error("msg-error", 1000);
    cout << endl;

    // Set level to DEBUG, all logging level messages printed
    log->setLevel(iapcv_log::DEBUG);
    log->debug_inline("Set level to DEBUG: all logging level messages printed.");
    log->Debug("\n");
    log->debug("");
    log->info("msg-info");
    log->warn("msg-warn");
    log->error("msg-error");
    cout << endl;

    // Set level to INFO, INFO, WARN, ERROR messages printed
    log->setLevel(iapcv_log::INFO);
    log->debug("msg-debug");
    log->info("Set level to INFO: INFO, WARN, ERROR messages printed");
    log->warn("msg-warn");
    log->error("msg-error");
    cout << endl;

    // Set level to WARN, WARN, ERROR messages printed
    log->setLevel(iapcv_log::WARN);
    log->debug("msg-debug");
    log->info("msg-info");
    log->warn("Set level to WARN: WARN, ERROR messages printed");
    log->error("msg-error");
    cout << endl;

    // Set level to ERROR, only ERROR messages printed
    log->setLevel(iapcv_log::ERROR);
    log->debug("msg-debug");
    log->info("msg-info");
    log->warn("msg-warn");
    log->error("Set level to ERROR: only ERROR messages printed");
    cout << endl;

    log->setLevel(iapcv_log::DEBUG);
    log->finfo("ssp", "Intance log: ", "addr:", log);
    cout << endl;

    delete log;
    return 0;
}