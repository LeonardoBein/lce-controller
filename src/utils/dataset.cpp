#ifndef DATASET_CPP
#define DATASET_CPP 1
 
#include "../../include/utils/dataset.h"
#include <sstream>
#include <algorithm> 
#include <string.h>
#include "../../include/utils/exception.h"

template<class T>
Dataset<T>::Dataset(char* first, ...)
        :size(0)
{
        va_list vlist;
        char* aux;
        aux = first;
        va_start(vlist, first);

        do {
                this->header.push_back(aux);
                this->size++;
                aux=va_arg(vlist, char*);
        } while (aux!=NULL);

        va_end(vlist);
}

template<class T>
void Dataset<T>::addRow(T value, ...){
        va_list vlist;
        std::vector<T> array;
        va_start(vlist, value);

        array.push_back(value);
        for (int i = 1; i < this->size; i++){
            array.push_back(va_arg(vlist, T));
        }
        
        va_end(vlist);
        this->rows.push_back(array);
}

template<class T>
std::vector<char*> Dataset<T>::getHeader(){
        return this->header;
}

template<class T>
std::vector<std::vector<T>> Dataset<T>::getRows(){
        return this->rows;
}

template<class T>
std::string Dataset<T>::exportCSV(){
        std::stringstream csv;
        char separator =  ';';
        int _size = 0;

        for (auto h: this->header){
                csv << '"' << h << '"';
                if(_size + 1 < this->size){ csv << separator; }
                _size++;
        }
        csv << std::endl;


        for (auto row: this->rows){
                _size = 0;
                for (auto item: row){
                        if(typeid(T) == typeid(char*)){
                                csv << '"' << item << '"';
                        }else{
                                csv << item;
                        }
                        if(_size + 1 < this->size){ csv << separator; }
                        _size++;
                }
                csv << std::endl;        
        }

        return csv.str();
        
}

template<class T>
void Dataset<T>::setRows(std::vector<std::vector<T>> _rows){
     this->rows = _rows;
}

template<class T>
std::vector<std::vector<T>> Dataset<T>::getPeaksIn(char* header, int nPeaks){
     std::vector<std::vector<T>> result = this->rows;

     int indexPeak = 0;
     bool find = false;

     for (auto h: this->header){
        if(strcmp(h,(char*)header) == 0){ find=true; break; }
        indexPeak++;
     }

     if(!find){ throw Exception("getPeaksIn: header não encontrado\n"); }

     std::sort(result.begin(), result.end(), [indexPeak](const std::vector<T>& a, const std::vector<T>& b) -> bool { return a[indexPeak] > b[indexPeak]; });

     if(result.size() > nPeaks){
        result.resize(nPeaks);
     }

     return result;

}
#endif // DATASET_CPP



