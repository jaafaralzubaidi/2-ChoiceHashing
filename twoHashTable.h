#include "position.h"
#include "UPCEntry.h"
#include "SLinkedList.h"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

class TwoHashTable
{

private:
    int SIZE = 100;
    SLinkedList<UPCEntry> *hashtable;

    float stddev(int *binLengths, int tableSize)
    {
        float sum = 0;
        for (int i = 0; i < tableSize; i++)
            sum += binLengths[i];

        float avarage = sum / tableSize;

        float dev_sum = 0;
        for (int i = 0; i < tableSize; i++)
        {
            dev_sum = dev_sum + (binLengths[i] - avarage) * (binLengths[i] - avarage);
        }

        float variance = dev_sum / tableSize;
        return sqrt(variance);
    }

    void load(string);
public:
    TwoHashTable(string filename, int tableSize);
    ~TwoHashTable();
    
    bool insert(UPCEntry &item);     // returns true if successful, false otherwise.
    Position search(UPCEntry &item); // if not found, return the default position with both indices set as -1
    float getStdDev();

    

};

TwoHashTable::TwoHashTable(string fileName, int tableSize){
    SIZE = tableSize;
    hashtable = new SLinkedList<UPCEntry>[SIZE];
    load(fileName);
}

TwoHashTable::~TwoHashTable(){
    delete[] hashtable;
}

void TwoHashTable::load(string inputFile){
    ifstream file;
    file.open(inputFile);

    string temp, line;
    // extracting the first row of columns name
    getline(file, temp);

    while(getline(file, line)){
        UPCEntry item(line);

        int tableIndex1 =  item.hash1(SIZE);
        int tableIndex2 =  item.hash2(SIZE);
        
        if( !hashtable[tableIndex1].find(item) && !hashtable[tableIndex2].find(item) ){

            if( hashtable[tableIndex1].size() <= hashtable[tableIndex2].size() )
                hashtable[tableIndex1].insert(item, hashtable[tableIndex1].zeroth());
            
            else
                hashtable[tableIndex2].insert(item, hashtable[tableIndex2].zeroth());
        }

    }
}


float TwoHashTable::getStdDev(){
    int * binLength = new int[SIZE];
    for( int i = 0; i < SIZE; i++)
        binLength[i] = hashtable[i].size();

    return stddev(binLength, SIZE);
}


Position TwoHashTable::search(UPCEntry &item){
    int tableIndex1 =  item.hash1(SIZE);
    int tableIndex2 =  item.hash2(SIZE);

    int indexInTable, index;
    Position position;

    index = hashtable[tableIndex1].indexOf(item);
    if(index > -1){
        position.indexInBin = index;
        position.indexInTable = tableIndex1;
    }

    index = hashtable[tableIndex2].indexOf(item);
    if(index > -1){
        position.indexInBin = index;
        position.indexInTable = tableIndex2;
    }

    return position;
}
