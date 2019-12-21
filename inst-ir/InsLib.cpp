#ifndef INS_LIB
#define INS_LIB
#include <cstdlib>
#include <map>
#include <set>
#include <iostream>

std::map<int, std::set<void *>> ValidM;
void insert(int classAndMethod, void * methodPtr){
    ValidM[classAndMethod].insert(methodPtr);
}
void check(int classAndMethod, void * methodPtr){
    for(auto i = ValidM[classAndMethod].begin(), e = ValidM[classAndMethod].end();
        i != e;
        i++){
        if(methodPtr == *i)
            return;
    }
    std::cout << "No matches. int: " << classAndMethod << ", Pointer pointing to: " << methodPtr << '\n';
    std::cout << "Legitimate addresses are: \n";
    for(auto i = ValidM[classAndMethod].begin(), e = ValidM[classAndMethod].end();
        i != e;
        i++){
        std::cout << *i << '\n';
    }
    
    std::abort();
}
#endif