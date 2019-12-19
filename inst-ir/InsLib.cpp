#include <cstdlib>
#include <vector>
#include <set>

namespace safedispatch{
    std::vector<std::set<void *>> ValidM;

    void insert(int classAndMethod, void * methodPtr){
        if(classAndMethod > (ValidM.size() - 1))
            ValidM.resize(classAndMethod + 1);
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
};