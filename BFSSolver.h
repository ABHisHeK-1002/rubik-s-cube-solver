#include <bits/stdc++.h>
#include "RubiksCube.h"

#ifndef RUBIKS_CUBE_SOLVER_BFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_BFSSOLVER_H

template<typename T, typename H>
class BFSSolver{
private:
    vector<RubiksCube::MOVE> moves;
    unordered_map<T,bool,H> visited;
    unordered_map<T,RubiksCube::MOVE, H> movedone;

    // bfs() -> performs breadth-first-search and returns a solved Rubik's Cube
    // move_done[] -> Back-Pointer map as to how we reached that state

    T bfs(){
        queue<T>q;
        q.push(rubikscube);
        visited[rubikscube] = true;

        while(!q.empty()){
            T node = q.front();
            q.pop();
            if(node.isSolved()){
                return node;
            }
            for(int i=0; i<18; i++){
                auto curr_move = RubiksCube::MOVE(i);
                node.move(curr_move);
                if(!visited[node]){
                    visited[node] = true;
                    move_done[node] = curr_move;
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
        return rubikscube;
    }

public:
    T rubikscube;

    BFSSolver(T rubikscube){
        this->rubikscube = rubikscube;
    }

    vector<RubiksCube::MOVE> solve(){
        T solved_cube = bfs();
        assert(solved_cube.isSolved());
        T curr_cube = solved_cube;
        while(!(curr_cube == rubikscube)){
            RubiksCube::MOVE curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        rubikscube = solved_cube;   //overriden and hence a deep copy
        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif //RUBIKS_CUBE_SOLVER_BFSSOLVER_H