#include <StableMarriage/Globals.h>

int n = 7;
int MAX_SM = 1231;
int histogramSize = 100000;

std::vector<std::vector<PAIR>> matrix;
std::vector<std::vector<int>> displayArr;
std::vector<std::vector<int>> startNArray;
std::vector<std::vector<PAIR>> largestMatrix;
std::vector<std::vector<PAIR>> fattestMatrix;
std::vector<std::vector<int>> latinMatrix;
std::vector<int> histogram;

int cnt = 0;
int largest = 0;
int fattest = 0;
bool iterationKiller = false;
double mean = 0.0;
std::vector<int> mRank;
std::vector<int> wRank;
char ch;
