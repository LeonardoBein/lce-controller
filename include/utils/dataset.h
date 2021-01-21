#ifndef DATASET_H
#define DATASET_H 1

#include <vector>
#include <string>
#include <cstdarg>

template<class T=int>
class Dataset{

private:
    int size;
    std::vector<char*> header;
    std::vector<std::vector<T>> rows;


public:
    Dataset(char* first, ...);
    void addRow(T value, ...);

    std::vector<char*> getHeader();
    std::vector<std::vector<T>> getRows();

    void setRows(std::vector<std::vector<T>>);

    std::vector<std::vector<T>> getPeaksIn(char* header,int nPeaks = 1);


    std::string exportCSV();
};

#include "../../src/utils/dataset.cpp"

#endif // DATASET_H

