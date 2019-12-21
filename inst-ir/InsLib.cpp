#ifndef INS_LIB
#define INS_LIB
#include <cstdlib>
#include <map>
#include <set>

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
    std::abort();
}
#endif