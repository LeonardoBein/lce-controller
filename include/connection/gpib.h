#include "visa/visa.h"

#ifndef _GPIB_APPLICATION

#define _GPIB_APPLICATION 1
#define _GPIB_MAX_CNT 2000

#if defined(_WIN64) || defined(_WIN32)
    /* Microsoft Windows (64-bit or 32-bit) */
#pragma comment(lib, "visa32.lib")

#endif



class GPIB {
private:
    ViStatus _status;
	ViSession _defaultRM, _instr;
	ViUInt32 _retCount;
    bool _testResponse, _testWrite;
    char _addr[100] = {0};
	char _buffer[_GPIB_MAX_CNT];

    void _checkError(void);

public:
    GPIB(char *addr);
    void setTestResponse(bool value);
    void setTestWrite(bool value);
    void write(char* command);
    void write(const char* command);
    char* read(void);
    char* query(const char* command, const char* testResponse);
    char* query(char* command, char* testResponse);
    ~GPIB();
};

#endif
