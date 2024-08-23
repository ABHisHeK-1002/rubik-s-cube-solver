#include "RubiksCube.h"

/*
    Face    Color    8-bit representation
    Up      White          00000001
    Left    Green          00000010
    Front   Red            00000100
    Right   Blue           00001000
    Back    Orange         00010000
    Down    Yellow         00100000

    Face Indexing-
    0  1  2

    7     3

    6  5  4
*/

class RubiksCubeBitboard : public RubiksCube{
private:
    int solved_side_config[6]{};

    int arr[3][3] = {{0,1,2},
                     {7,8,3},
                     {6,5,4}};

    int64_t one_8 = (1<<8)-1;
    int64_t one_24 = (1<<24)-1;

    void rotateFace(int ind){
        int side = bitboard[ind];
        side = side >> (8 * 6);     //the first two 8 bit representation goes to the last two places
        bitboard[ind] = (bitboard[ind] << 16) | (side);   //last 6 goes to first 6
    }

    //Function to manually rotate the affected sides after we rotate a face ourselves.
    void rotateSide(int s1, int s1_1, int s1_2, int s1_3, int s2, int s2_1, int s2_2, int s2_3) {
        int64_t clr1 = (bitboard[s2] & (one_8 << (8 * s2_1))) >> (8 * s2_1);
        int64_t clr2 = (bitboard[s2] & (one_8 << (8 * s2_2))) >> (8 * s2_2);
        int64_t clr3 = (bitboard[s2] & (one_8 << (8 * s2_3))) >> (8 * s2_3);

        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_1))) | (clr1 << (8 * s1_1));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_2))) | (clr2 << (8 * s1_2));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_3))) | (clr3 << (8 * s1_3));
    }

    int get5bitcorner(){

    }

public:    
    int64_t bitboard[6]{};

    RubiksCubeBitboard(){
        for(int side=0; side<6; side++){
            int clr = 1<<side;
            bitboard[side] = 0;
            for(int index=0; index<8; index++){
                bitboard[side] |= clr << (8*index);
            }
            solved_side_config[side] = bitboard[side];
        }
    }

    //Implementing Virtual Functions
    COLOR getColor(FACE face, int row, int col) const override{
        int idx = arr[row][col];
        if(idx==8){
            return COLOR((int)face);
        }
        int side = bitboard[(int)face];
        int color = (side >> (8 * idx)) & one_8;    //taking the whole 64 bit number, and then taking the 8 bit representation of a particular cubie 

        int bit_pos = 0;
        while(color!=0){
            color = color >> 1;
            bit_pos++;
        }
        return COLOR(bit_pos-1);
    }

    bool isSolved() const override{
        for(int i=0; i<6; i++){
            if(solved_side_config[i]!=bitboard[i]){
                return false;
            }
        }
        return true;
    }

    RubiksCube &u() override {
        this->rotateFace(0);
        int64_t temp = bitboard[2] & one_24;
        bitboard[2] = (bitboard[2] & ~one_24) | (bitboard[3] & one_24);
        bitboard[3] = (bitboard[3] & ~one_24) | (bitboard[4] & one_24);
        bitboard[4] = (bitboard[4] & ~one_24) | (bitboard[1] & one_24);
        bitboard[1] = (bitboard[1] & ~one_24) | temp;
        return *this;
    }
    RubiksCube &uPrime() override {
        this->u();this->u();this->u();
        return *this; 
    }
    RubiksCube &u2() override {
        this->u(); this->u();
        return *this;
    }

    RubiksCube &l() override {
        this->rotateFace(1);
        int64_t clr1 = (bitboard[2] & (one_8 << (8 * 0))) >> (8 * 0);
        int64_t clr2 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);
        int64_t clr3 = (bitboard[2] & (one_8 << (8 * 7))) >> (8 * 7);

        this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
        this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
        this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);

        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 0))) | (clr1 << (8 * 0));
        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 7))) | (clr3 << (8 * 7));

        return *this;
    };
    RubiksCube &lPrime() override {
        this->l();this->l();this->l();
        return *this;
    };
    RubiksCube &l2() override {
        this->l();this->l();
        return *this;
    };

    RubiksCube &f() override {
        this->rotateFace(2);

        int64_t clr1 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);
        int64_t clr2 = (bitboard[0] & (one_8 << (8 * 5))) >> (8 * 5);
        int64_t clr3 = (bitboard[0] & (one_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
        this->rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
        this->rotateSide(5, 0, 1, 2, 3, 6, 7, 0);

        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    };
    RubiksCube &fPrime() override {
        this->f();this->f();this->f();
        return *this;
    };
    RubiksCube &f2() override {
        this->f();this->f();
        return *this;
    };

    RubiksCube &r() override {
        this->rotateFace(3);
        int64_t clr1 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);
        int64_t clr2 = (bitboard[0] & (one_8 << (8 * 3))) >> (8 * 3);
        int64_t clr3 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);

        this->rotateSide(0, 2, 3, 4, 2, 2, 3, 4);
        this->rotateSide(2, 2, 3, 4, 5, 2, 3, 4);
        this->rotateSide(5, 2, 3, 4, 4, 7, 6, 0);

        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 7))) | (clr1 << (8 * 7));
        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    };
    RubiksCube &rPrime() override {
        this->r();this->r();this->r();
        return *this;
    };
    RubiksCube &r2() override {
        this->r();this->r();
        return *this;
    };

    RubiksCube &b() override {
        this->rotateFace(4);

        int64_t clr1 = (bitboard[0] & (one_8 << (8 * 0))) >> (8 * 0);
        int64_t clr2 = (bitboard[0] & (one_8 << (8 * 1))) >> (8 * 1);
        int64_t clr3 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);

        this->rotateSide(0, 0, 1, 2, 3, 2, 3, 4);
        this->rotateSide(3, 2, 3, 4, 5, 4, 5, 6);
        this->rotateSide(5, 4, 5, 6, 1, 6, 7, 0);

        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    };
    RubiksCube &bPrime() override {
        this->b();this->b();this->b();
        return *this;
    };
    RubiksCube &b2() override {
        this->b();this->b();
        return *this;
    };

    RubiksCube &d() override {
        this->rotateFace(5);

        int64_t clr1 = (bitboard[2] & (one_8 << (8 * 4))) >> (8 * 4);
        int64_t clr2 = (bitboard[2] & (one_8 << (8 * 5))) >> (8 * 5);
        int64_t clr3 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
        this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
        this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);

        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 4))) | (clr1 << (8 * 4));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 5))) | (clr2 << (8 * 5));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));
        return *this;
    };
    RubiksCube &dPrime() override {
        this->d();this->d();this->d();
        return *this;
    };
    RubiksCube &d2() override {
        this->d();this->d();
        return *this;
    }

    bool operator==(const RubiksCubeBitboard &r1) const {
        for (int i = 0; i < 6; i++) {
            if (bitboard[i] != r1.bitboard[i]) return false;
        }
        return true;
    }

    RubiksCubeBitboard &operator=(const RubiksCubeBitboard &r1) {
        for (int i = 0; i < 6; i++) {
            bitboard[i] = r1.bitboard[i];
        }
        return *this;
    }
};

struct HashBitboard {
    size_t operator()(const RubiksCubeBitboard &r1) const {
        uint64_t final_hash = r1.bitboard[0];
        for (int i = 1; i < 6; i++) final_hash ^= r1.bitboard[i];
        return (size_t) final_hash;
    }
};