#include <StableMarriage/OptionI.h>
#include <StableMarriage/Globals.h>
#include <StableMarriage/NumberOfSMFunctions.h>
#include <iostream>

void optionI() {
    int m, w;
    for (int i = 0; i < n; i ++){
        std::cout << "Enter Row " << i + 1 << ": ";
        for (int j = 0; j < n; j ++){
            std::cin >> m >> w;
            matrix[i][j].m = m - 1;
            matrix[i][j].w = w - 1;
        }
        std::cout << '\n';
    }
    std::cout << "This is the given matrix:\n";
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            std::cout << matrix[i][j].m + 1 << ',' << matrix[i][j].w + 1 << "  ";
        }
        std::cout << '\n';
    }
    numberOfStableMatchings();
}
