#include "OptionL.h"
#include "OptionH.h"
#include "OptionB.h"
#include "OptionE.h"
#include "OptionR.h"
#include "OptionS.h"
#include "OptionI.h"
#include "OptionP.h"
#include "OptionG.h"

// Start timer
clock_t tStart;

int main() {
    srand((unsigned int)time(NULL));
    
    while(1) {
        cout << "Choose an option below:\n";
        cout << "(R) Generate And Calculate Random Samples\n";
        cout << "(S) Verify Matching\n";
        cout << "(L) Test Latin Matrix\n";
        cout << "(H) Hill Climbing Search\n";
        cout << "(B) Best First Search\n";
        cout << "(I) Input Matrix\n";
        cout << "(P) Input Psuedo Latin Matrix\n";
        cout << "(E) Extract Top Seeds\n";
        cout << "(G) Generate a new matrix that is n + 1\n\n";
        cout << "Enter choice: ";
        cin >> ch;
        cout << '\n' << '\n';
        if (ch == 'R' || ch == 'r'){
            optionR();
        }else if (ch == 'S' || ch == 's'){
            optionS();
        }else if (ch == 'L' || ch == 'l'){
            optionL();
        }else if (ch == 'I' || ch == 'i'){
            optionI();
        }else if (ch == 'H' || ch == 'h'){
            optionH();
        }else if (ch == 'P' || ch == 'p'){
            optionP();
        }else if (ch == 'B' || ch == 'b'){
            optionB();
        }else if (ch == 'E' || ch == 'e'){
            optionE();
        }else if (ch == 'G' || ch == 'g'){
            optionG();
        }
    }
}//main method
             
