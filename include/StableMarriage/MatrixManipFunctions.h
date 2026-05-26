#ifndef MatrixManipFunctions_h
#define MatrixManipFunctions_h

#include "Globals.h"

void printHistogram();
void printMatrix();
int findIndex(int temp[], int size, int num);
void convertToGeneral();
void clearMatrix();
void clearRankings();
void clearHistogram();
bool repeatedOnes(int j);
void noSoulmatesRandomizer();
void randomizer();
void swapMen(int i, int j, int k);
void swapWomen(int i, int j, int k);
void displayDifferentNumbers();
void updateDisplayArray(int r, int c);
void dropToOneLessN(int orignalN);
void dropTo2LessN(int orignalN);
void dropToLessN(int orignalN);
void increaseNByOne(int beginningN);

#endif /* MatrixManipFunctions_h */
