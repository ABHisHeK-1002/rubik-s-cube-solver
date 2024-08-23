#ifndef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H

#include<bits/stdc++.h>
using namespace std;

/*
    This is an abstract class.
    Provides a template for all the 3 models of Rubik's Cube
*/

class RubiksCube{
    public:
        enum class FACE{
            UP,
            LEFT,
            FRONT,
            RIGHT,
            BACK,
            DOWN
        };

        enum class COLOR{
            WHITE,
            GREEN,
            RED,
            BLUE,
            ORANGE,
            YELLOW
        };

        enum class MOVE{
            L, LPRIME, L2,
            R, RPRIME, R2,
            U, UPRIME, U2,
            D, DPRIME, D2,
            F, FPRIME, F2,
            B, BPRIME, B2,
        };

        
        //Returns the color of the cell at (row,col) in face
        virtual COLOR getColor(FACE face, int row, int col) const = 0;

        //Returns the first letter of the given COLOR    
        static char getColorLetter(COLOR color);

        //Returns true if the Rubik's cube is solved
        virtual bool isSolved() const = 0;

        //Returns the move in string datatype
        static string getMove(MOVE ind);

        //Print
        void print() const;

        //Random shuffle of the cube 'times' times
        vector<MOVE> randomShuffleCube(int times);

        //Peform moves on the cube
        RubiksCube &move(MOVE ind);

        //Invert a move
        RubiksCube &invert(MOVE ind);

        virtual RubiksCube &f() = 0;
        virtual RubiksCube &fPrime() = 0;
        virtual RubiksCube &f2() = 0;

        virtual RubiksCube &u() = 0;
        virtual RubiksCube &uPrime() = 0;
        virtual RubiksCube &u2() = 0;

        virtual RubiksCube &l() = 0;
        virtual RubiksCube &lPrime() = 0;
        virtual RubiksCube &l2() = 0;

        virtual RubiksCube &d() = 0;
        virtual RubiksCube &dPrime() = 0;
        virtual RubiksCube &d2() = 0;

        virtual RubiksCube &r() = 0;
        virtual RubiksCube &rPrime() = 0;
        virtual RubiksCube &r2() = 0;

        virtual RubiksCube &b() = 0;
        virtual RubiksCube &bPrime() = 0;
        virtual RubiksCube &b2() = 0;

        string getCornerColorString(int ind);
        int getCornerIndex(int ind);
        int getCornerOrientation(int ind);
};

#endif //RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H