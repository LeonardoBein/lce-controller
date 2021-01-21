// #include "machines/turntable/deisel_hd50.cpp"
// #include "machines/antenna_controller/m2090.cpp"
// #include "machines/spectral_analysis/esvs_30.cpp"
// #include "modules/emissao_radiada.cpp"
#include "../include/gui/mainWindow.h"
// #include "../include/gui/chartWindow.h"
#include "../include/gui/gui.h"
// #include "utils/math.cpp"
// #include "../include/utils/math.h"
// #include <iostream>
// #include <vector>
// #include "../include/utils/dataset.h"
// #include "../include/log/logApplication.h"


int main(int argc, char const *argv[])
{
    // DeiselHD50* turntable = new DeiselHD50((char*)"GPIB0::7::INSTR");
    // M2090* antenna = new M2090((char*)"GPIB0::17::INSTR");
    // ESVS30* spectral_analysis = new ESVS30((char*)"GPIB0::27::INSTR");

    // turntable->Reset();
    // turntable->CheckStatus(1);
    // turntable->SetPosition(10);
    // turntable->SetPosition(-10);
    // turntable->SetPosition(10000);


    // std::cout << antenna->CheckStatus(100.1) << " " << (std::to_string(10.11)).c_str() ;

    // spectral_analysis->ConfigureDetector(0);
    

    // delete turntable;
    // delete spectral_analysis;
    // delete antenna;

    // EmissaoRadiada* test = new EmissaoRadiada(1000, 2000, 45);

    // test->run();

    // delete test;
    GUI app(argc, (char **)argv);
    MainWindow scheen;
    scheen.show();
    // ChartWindow chart;
    // chart.show();
    return app.run();
    // std::vector<int> a;

    // a.

    // Dataset<double> dataset("A","B", "C", NULL);

    // dataset.addRow(1.0, 22.2, 0.1);
    // dataset.addRow(3.0, 4.0,  0.2);
    // auto peaks = dataset.getPeaksIn("B");
    
    // dataset.setRows(peaks);

    // std::cout << dataset.exportCSV() << std::endl;

    // LogApplication log = LogApplication::stream();    

    // auto vet = Math::range<float, float>(1,10,0.1);

    // for (auto item: vet)
    // {
    //     log << item << " ";
    // }
    
    // log.print("INFO");



    return 0;

}
