#ifndef NumberOfSMFunctions_h
#define NumberOfSMFunctions_h

#include "Globals.h"
#include <vector>

bool ok2(const std::vector<int>& q, int col);
void backtrack(int &col);
void print(int q[]);
void numberOfStableMatchings();
void readAndWriteFromFile();

#endif /* NumberOfSMFunctions_h */
