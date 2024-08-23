#include <bits/stdc++.h>
#include "RubiksCube.h"
#include "DFSSolver.h"

#ifndef RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H

template<typename T, typename H>
class IDDFSSolver{
private:
    int max_search_depth;
    vector <RubiksCube::MOVE> moves;
public: 
    T rubikscube;
    IDDFSSolver(T rubikscube, int max_search_depth){
        this->rubikscube = rubikscube;
        this->max_search_depth = max_search_depth;
    }

    vector<RubiksCube::MOVE> solve(){
        for(int i=1; i<-max_search_depth; i++){
            DFSSolver<T,H> dfssolver(rubikscube,i);
            moves = dfssolver.solve();
            if (dfsSolver.rubiksCube.isSolved()) {
                rubiksCube = dfsSolver.rubiksCube;
                break;
            }
        }
    }
    return moves;

};

#endif //RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
