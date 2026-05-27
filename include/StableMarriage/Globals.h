#ifndef Globals_h
#define Globals_h

#include <vector>

// Struct definition
struct PAIR {
    int m, w;
};

// Global Configuration (Adjustable)
extern int n;
extern int MAX_SM;
extern int histogramSize;

// Shared Global Variables (Dynamic Vectors)
extern std::vector<std::vector<PAIR>> matrix;
extern std::vector<std::vector<int>> displayArr;
extern std::vector<std::vector<int>> startNArray;
extern std::vector<std::vector<PAIR>> largestMatrix;
extern std::vector<std::vector<PAIR>> fattestMatrix;
extern std::vector<std::vector<int>> latinMatrix;
extern std::vector<int> histogram;

// Scalar Globals
extern int cnt;
extern int largest;
extern int fattest;
extern bool iterationKiller;
extern double mean;
extern std::vector<int> mRank;
extern std::vector<int> wRank;
extern char ch;
extern bool Pseudo;

// System initialization and resizing
void initializeSystem(int newN);

#endif
