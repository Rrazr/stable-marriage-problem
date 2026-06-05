#include <StableMarriage/Globals.h>
#include <StableMarriage/UIUtils.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <chrono>

void initializeSystem(int newN) {
    n = newN;
    
    matrix.assign(n, std::vector<PAIR>(n));
    largestMatrix.assign(n, std::vector<PAIR>(n));
    localMaxMatrix.assign(n, std::vector<PAIR>(n));
    latinMatrix.assign(n, std::vector<int>(n));
    
    displayArr.assign(n + 1, std::vector<int>(n + 1, 0));
    startNArray.assign(n + 2, std::vector<int>(n + 2, 0));
    
    histogram.assign(histogramSize, 0);
    mRank.clear();
    wRank.clear();
    cnt = 0;
    largest = 0;
    localMax = 0;
    mean = 0.0;
}

// From NumberOfSMFunctions.h

bool ok2(const std::vector<int>& q, int col) {
    int i;
    for(i=0; i<col;i++){
        if(q[col]==q[i])
            return false;
    }

    for(i=0; i<col; i++)
    {
        if( ( matrix[col][q[i]].m<matrix[col][q[col]].m )&& ( matrix[col][q[i]].w<matrix[i][q[i]].w ) )
            return false;
        if( ( matrix[i][q[col]].w<matrix[col][q[col]].w )&& ( matrix[i][q[col]].m<matrix[i][q[i]].m) )
            return false;
    }

    return true;
}

void backtrack(int &col) {
    col--;
    if(col==-1){
        //std::cout << "Number of Stable Marriages: " << cnt << '\n';
        mean += cnt;
        histogram[cnt] ++;
        if (cnt > largest){
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    largestMatrix[i][j].m = matrix[i][j].m;
                    largestMatrix[i][j].w = matrix[i][j].w;
                }
            }
        }
        largest = cnt > largest ? cnt : largest;
        iterationKiller = false;
    }
}

void print(int q[]) {
    int i;
    std::cout<<"Man"<<"  "<<"Woman"<<'\n';
    for( i=0;i<n;i++)
    {
        std::cout<<" "<<i + 1<<"     "<<q[i] + 1<<'\n';
    }
}

void numberOfStableMatchings() {
    iterationKiller = true;
    cnt = 0;
    std::vector<int> q(n);
    q[0]=0;
    int c=1;
    bool from_backtrack=false;
    while(iterationKiller){
        while(c<n){
            if(!from_backtrack)
                q[c]=-1;
            
            from_backtrack=false;
            while(q[c]<n){
                q[c]++;
                while(q[c]==n)
                {
                    backtrack(c);
                    if (!iterationKiller){
                        break;
                    }
                    q[c]++;
                }
                if (!iterationKiller){
                    break;
                }
                if(ok2(q, c))
                    break;
            }
            if (!iterationKiller){
                break;
            }
            c++;
        }
        if (!iterationKiller){
            break;
        }
        cnt ++;
        backtrack(c);
        from_backtrack=true;
    }
}

void readAndWriteFromFile(){
    bool alreadyExists = true;
    if(cnt > 50){
        int num;
        std::string str;
        std::ifstream specialMatrixFile;
        specialMatrixFile.open("/Users/ryan/Desktop/Matrices.txt");
        while(!specialMatrixFile.eof()){
            alreadyExists = true;
            for (int i = 0; i < 5; i ++){
                if (!(specialMatrixFile >> str)) break;
            }
            std::cout << "Matrix:\n";
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    specialMatrixFile >> num;
                    std::cout << num << "  ";
                    if(num != matrix[i][j].m + 1){
                        alreadyExists = false;
                    }
                    specialMatrixFile >> num;
                    std::cout << num << "  ";
                    if(num != matrix[i][j].w + 1){
                        alreadyExists = false;
                    }
                }
                std::cout << '\n';
            }
            if (alreadyExists){
                break;
            }
        }
        specialMatrixFile.close();
        if(!alreadyExists){
            std::ofstream specialMatrixFile("/Users/ryan/Desktop/Matrices.txt", std::ios::app);
            specialMatrixFile <<"Number of Stable Marriages: " << cnt << '\n';
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    specialMatrixFile << matrix[i][j].m + 1 << ' ' << matrix[i][j].w + 1 << "  ";
                }
                specialMatrixFile << '\n';
            }
            specialMatrixFile.close();
        }
    }
}

// From MatrixManipFunctions.h

void printHistogram(int numSamples){
    for (int i = 0; i < histogramSize; i ++){
        if (histogram[i] != 0){
            std::cout << i << ": " << histogram[i] << '\n';
        }
    }
    std::cout << "Mean: " << mean / numSamples << '\n';
}

void printMatrix(){
    std::cout << "\nMatrix:\n";
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            std::cout << matrix[i][j].m + 1 << ',' << matrix[i][j].w + 1 << "  ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int findIndex(int temp[], int size, int num){
    for (int i = 0; i < n + 1; i++){
        if (temp[i] == num){
            return i;
        }
    }
    return 0;
}

void convertToGeneral(){
    std::vector<int> arr(n);
    std::vector<int> temp(n);
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            arr[j] = matrix[i][j].m;
            temp[j] = matrix[i][j].m;
        }
        std::sort(temp.begin(), temp.end());
        for(int k = 0; k < n; k++){
            arr[k] = findIndex(temp.data(), n, arr[k]);
            matrix[i][k].m = arr[k];
        }
    }
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            arr[j] = matrix[j][i].w;
            temp[j] = matrix[j][i].w;
        }
        std::sort(temp.begin(), temp.end());
        for(int k = 0; k < n; k++){
            arr[k] = findIndex(temp.data(), n, arr[k]);
            matrix[k][i].w = arr[k];
        }
    }
}

void clearMatrix(){
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            matrix[i][j].m = -1;
            matrix[i][j].w = -1;
        }
    }
}

void clearRankings(){
    mRank.clear();
    wRank.clear();
}

void clearHistogram(){
    for (int i = 0; i < histogramSize; i ++){
        histogram[i] = 0;
    }
    mean = 0;
    largest = 0;
}

bool repeatedOnes(int j){
    for (int i = 0; i < n - 1; i ++){
        if (matrix[i][j].m != 0){
            return false;
        }
    }
    return true;
}

void randomizer(){
    clearRankings();
    int ind;
    for (int i = 0; i < n; i ++){
        for (int k = 0; k < n; k ++){
            mRank.push_back(k);
            wRank.push_back(k);
        }
        for (int j = 0; j < n; j ++){
            ind = std::rand() % mRank.size();
            matrix[i][j].m = mRank[ind];
            mRank.erase(mRank.begin() + ind);
            ind = std::rand() % wRank.size();
            matrix[j][i].w = wRank[ind];
            wRank.erase(wRank.begin() + ind);
        }
    }
}

void swapMen(int i, int j, int k){
    int temp = matrix[i][j].m;
    matrix[i][j].m = matrix[i][k].m;
    matrix[i][k].m = temp;
}

void swapWomen(int i, int j, int k){
    int temp = matrix[j][i].w;
    matrix[j][i].w = matrix[k][i].w;
    matrix[k][i].w = temp;
}

void displayDifferentNumbers(){
    for(int i = 0; i < n + 1; i++){
        for(int j = 0; j < n + 1; j++){
            std::cout << displayArr[i][j] << "   ";
        }
        std::cout << '\n';
    }
}

void updateDisplayArray(int r, int c){
    displayArr[r][c] = cnt;
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}
