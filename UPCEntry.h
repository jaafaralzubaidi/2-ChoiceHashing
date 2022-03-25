#ifndef UPC_ENTRY
#define UPC_ENTRY
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class UPCEntry{  

private:
    long long upc = -1;
    string desc = "";
    void extractInfo(string line);


public:
    int hash1(int tableSize){
        return upc % tableSize;
    }

    int hash2(int tableSize){
        return abs(desc[0] + 27 * desc[1] + 729 * desc[2]) % tableSize;
    }
    
    UPCEntry(long long u = 0, string d = string()): upc(u), desc(d){} 
    UPCEntry(string);
    void print();

    bool operator == (const UPCEntry &) ;
    
};


UPCEntry::UPCEntry(string line){
    extractInfo(line);
}

void UPCEntry::extractInfo(string line){
    string upcString, description;
    stringstream ss(line);
    
    getline(ss,upcString,',');
    upc = stoll(upcString);

    getline(ss,description);
    desc = description;
}


void UPCEntry::print(){
    cout << "# " << upc << " : " << desc << endl;
}


bool UPCEntry::operator==(const UPCEntry & other) {
    if(upc == other.upc)
        return true;
    return false;
}


#endif
