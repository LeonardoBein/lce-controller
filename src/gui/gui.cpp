#include "../../include/gui/gui.h"


GUI::GUI(int &argc, char **argv): application(new QApplication(argc, argv)){ }

int GUI::run(){
    return this->application->exec();
}
GUI::~GUI(){
    delete this->application;
}