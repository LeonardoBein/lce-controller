
#ifndef _LOGGING_APPLICATION
#define _LOGGING_APPLICATION 1

#include <iostream>
#include <ctime>
#include <sstream> 

using namespace std;

class LogApplication
{
private:
    stringstream output;
    
public:
    void print_datetime(){
        time_t ttime = time(0);
        tm *local_time = localtime(&ttime);

        cout << 1900 + local_time->tm_year 
        << "-" << 1 + local_time->tm_mon 
        << "-" << local_time->tm_mday 
        << " " <<  local_time->tm_hour  << ":"
        << 1 + local_time->tm_min << ":" 
        << 1 + local_time->tm_sec;
    }

    void print(const char * tag, const char*msg){
        this->print_datetime();
        cout << " " 
             << tag 
             << " " 
             << msg << endl;
    }

    template <typename T> friend LogApplication& operator<<(LogApplication& os, const T& t)
    { os.output << t; return os; }

    void print(const char * tag){
        this->print_datetime();
        cout << " " 
             << tag 
             << " " 
             << this->output.str() << endl;
        this->output.str(std::string());
    }

    static void info(const char*msg){
        LogApplication l;
        l.print("INFO", msg);
    }
    static void error(const char*msg){
        LogApplication l;
        l.print("ERROR", msg);
    }
    static void debug(const char*msg){
        LogApplication l;
        l.print("DEBUG", msg);
    }
    static void custom(char* tag, const char*msg){
        LogApplication l;
        l.print(tag, msg);
    }
    static LogApplication stream(){
        LogApplication l;
        return l;
    }   
};

#endif
