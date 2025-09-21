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
    
    /*
     * @20250919 
     * At this moment we don't catch this error in project.
     */
    try {
        log->setLevel(5);
    }
    catch (const std::invalid_argument& e) {
        cout << "Exception: " << e.what() << endl;
    }

    cout << "Test Debug" << endl;
    assert(iapcv_log::DEBUG==log->getLevel());
    assert(log->isDebug());
    log->debug("msg-debug");
    log->debug("msg-debug", "msg2");
    log->debug("msg-debug", 1000);
    log->fdebug("sss", "msg1-debug", "variadic function used.", "msg3");
    log->fdebug("sns", "msg1-debug", 10, "msg3");
    log->fdebug("ssf", "msg1-debug", "msg2", 3.1415926);
    log->debug_inline("Line is called by debug_inline: ");
    log->debug("Print function.");
    log->debug("\n");
    log->Debug("msg-debug");
    log->Debug("msg-debug", "msg2");
    log->Debug("msg-debug", 1000);
    log->Debug("\n");

    log->setLevel(iapcv_log::INFO);
    // Not printed: debug
    log->debug("msg-debug not shown.");
    cout << "Test Debug: Done" << endl;
    cout << endl;
    
    cout << "Test Trace" << endl;
    log->setLevel(iapcv_log::TRACE);
    log->trace("msg-trace");
    log->trace("msg-trace", "msg2");
    log->Trace("msg-trace", "msg2");
    log->fTrace("sss", "msg1-trace", "variadic function used.", "Debug with no header.");
    log->fTrace("sns", "msg1-trace", 10, "Debug with no header.");
    log->fTrace("ssf", "msg1-trace", "msg2", 3.1415926);
    log->fTrace("nsf", 10, "msg2", 3.1415926);
    cout << endl;
    cout << "Test variadict function with wrong format." << endl;
    log->fTrace("ssd", "Message with wrong format.", "msg2", 3);
    cout << "Test variadict function with wrong format: Done" << endl;
    cout << "Test Trace: Done" << endl;
    cout << endl;

    cout << "Test Info" << endl;
    log->setLevel(iapcv_log::INFO);
    // Not printed: TRACE, DEBUG
    log->fTrace("sss", "msg1-trace", "msg2", "msg3");
    log->debug("msg-debug");
    log->info("msg-info");
    log->info("msg-info", "msg2");
    log->info("msg-info", 1000);
    log->finfo("sss", "msg1-info", "msg2", "msg3");
    log->finfo("nsf", 10, "msg2", 3.1415926);
    cout << "Test Info: Done" << endl;
    cout << endl;

    cout << "Test Warn" << endl;
    log->setLevel(iapcv_log::WARN);
    // Not printed: Debug and info
    log->fTrace("sss", "msg1-trace", "not shown", "msg3");
    log->fdebug("sss", "msg1-trace", "not shown", "msg3");
    log->finfo("sss", "msg1-info", "not shown", "msg3");
    log->warn("msg1-warn:", 1000);
    cout << "Test Warn: Done" << endl;
    cout << endl;

    cout << "Test Error" << endl;
    log->setLevel(iapcv_log::ERROR);
    // Only error message printed
    log->debug("msg-debug");
    log->info("msg-info");
    log->warn("msg-warn");
    log->error("msg-error");
    log->error("msg-error", "msg2");
    log->error("msg-error", 1000);
    cout << "Test Error: Done" << endl;
    cout << endl;

     // Set level to TRACE, all logging level messages printed
    log->setLevel(iapcv_log::TRACE);
    log->trace("Set level to TRACE: all logging level messages printed.");
    log->trace("\n");
    log->debug("");
    log->info("msg-info");
    log->warn("msg-warn");
    log->error("msg-error");
    cout << endl;

    // Set level to DEBUG, all logging level messages printed
    log->setLevel(iapcv_log::DEBUG);
    log->trace("msg-trace");
    log->debug_inline("Set level to DEBUG: DEBUG, INFO, WARN, ERROR messages printed.");
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
    log->finfo("sps", "Intance log: ", log, "ok");
    cout << endl;

    delete log;
    return 0;
}