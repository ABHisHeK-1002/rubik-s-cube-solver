#include <bits/stdc++.h>
#include "RubiksCube.h"

#ifndef RUBIKS_CUBE_SOLVER_DFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_DFSSOLVER_H
// Typename T: RubiksCube Representation used (3d, 1d, Bitboard)
// Typename H: Corresponding Hash function

template<typename T, typename H>
class DFSSolver{
private:

    vector<RubiksCube::MOVE> moves;
    int max_search_depth;

    bool dfs(int depth){
        if(rubiksCube.isSolved()){
            return true;
        }
        if(depth>max_search_depth){
            return false;
        }
        for(int i=0; i<18; i++){
            rubiksCube.move(RubiksCube::MOVE(i));
            moves.push_back(RubiksCube::MOVE(i));
            if(dfs(depth+1)){
                return true;
            }
            moves.pop_back();
            rubiksCube.invert(RubiksCube::MOVE(i));
        }
        return false;
    }

public:
    T rubiksCube;

    DFSSolver(T rubiksCube, int max_search_depth=8){
        this->rubiksCube = rubiksCube;
        this->max_search_depth = max_search_depth;
    }

    vector<RubiksCube::MOVE> solve(){
        dfs(1);
        return moves;
    }
};

#endif //RUBIKS_CUBE_SOLVER_DFSSOLVER_H