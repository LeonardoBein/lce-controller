
#include <QApplication>

class GUI{
public:
    GUI(int &argc, char **argv);
    int run(void);
    ~GUI();
private:

    QApplication* application;


};

