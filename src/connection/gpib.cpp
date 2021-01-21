#include "../../include/connection/gpib.h"
#include "../../include/log/logApplication.h"
#include <string.h>

GPIB::GPIB(char *addr){
    this->_testResponse = false;
    strncpy(this->_addr, addr, 100);
    #if defined(_WIN64) || defined(_WIN32)
    /* Microsoft Windows (64-bit or 32-bit) */
        this->_status = viOpenDefaultRM(&this->_defaultRM);	
        this->_checkError();
        
        this->_status = viOpen(this->_defaultRM, addr, VI_NULL, VI_NULL, &this->_instr);
        this->_checkError();

        this->_status = viSetAttribute(this->_instr, VI_ATTR_TMO_VALUE, 5000);
        this->_checkError();

    #endif
}

void GPIB::_checkError(){
    if (this->_status < VI_SUCCESS) {
        LogApplication::error("Erro de comunicação GPIB");
		throw("Erro de comunicação GPIB");
	}
}

void GPIB::setTestResponse(bool value){
    this->_testResponse = value;
}

void GPIB::setTestWrite(bool value){
    this->_testWrite = value;
}

void GPIB::write(const char* command){
    this->write((char*)command);
}

void GPIB::write(char* command){

    LogApplication::custom(this->_addr,command);
    if(this->_testWrite){ return ; }
    
    #if defined(_WIN64) || defined(_WIN32)
        this->_status = viWrite(this->_instr, (ViBuf) command, strlen(command), &this->_retCount);
        this->_checkError();
    #endif
}

char* GPIB::read(void){
    #if defined(_WIN64) || defined(_WIN32)
        this->_status = viRead(this->_instr,  (ViPBuf) this->_buffer, _GPIB_MAX_CNT, &this->_retCount);
        this->_checkError();
    #endif
    LogApplication::debug(this->_buffer);
    return this->_buffer;
}

char *GPIB::query(const char* command, const char* testResponse = nullptr){
    return this->query((char*)command, (char*)testResponse);
}

char *GPIB::query(char* command, char* testResponse = nullptr){

    this->write(command);
    if(this->_testResponse){ return testResponse; }
    return this->read();

}

GPIB::~GPIB(){
    char msg[200] = {0};
    strcat(msg, "Fechando conexão ");
    strcat(msg, this->_addr);
    LogApplication::info(msg);
    #if defined(_WIN64) || defined(_WIN32)
        this->_status = viClose(this->_instr);
        this->_checkError();
        this->_status = viClose(this->_defaultRM);
        this->_checkError();
    #endif
}