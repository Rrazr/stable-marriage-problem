#ifndef Globals_h
#define Globals_h

#include <vector>

// Struct definition
struct PAIR {
    int m, w;
};

// Constants
// Using inline for constants to allow them to be defined in the header in C++17+
inline const int n = 7;
inline const int MAX_SM = 1231;
inline const int histogramSize = 100000;

// Shared Global Variables
extern PAIR matrix[n][n];
extern int displayArr[n+1][n+1];
extern int startNArray[n+1][n+1];
extern int cnt;
extern int largest;
extern PAIR largestMatrix[n][n];
extern int fattest;
extern PAIR fattestMatrix[n][n];
extern int histogram[histogramSize];
extern bool iterationKiller;
extern double mean;
extern std::vector<int> mRank;
extern std::vector<int> wRank;
extern char ch;
extern bool Pseudo;
extern int latinMatrix[n][n];
extern int matching[n];

#endif
