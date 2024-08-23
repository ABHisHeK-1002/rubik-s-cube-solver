
#include <bits/stdc++.h>
#include "DFSSolver.h"
#include "RubiksCube3dArray.cpp"

using namespace std;

int main(){
   RubiksCube3dArray cube;
   cube.print();

   vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffleCube(6);
   for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
   cout << "\n";
   cube.print();

   DFSSolver<RubiksCube3dArray, Hash3d> dfsSolver(cube, 8);
   vector<RubiksCube::MOVE> solve_moves = dfsSolver.solve();

   for (auto move: solve_moves) cout << cube.getMove(move) << " ";
   cout << "\n";
   dfsSolver.rubiksCube.print();
}