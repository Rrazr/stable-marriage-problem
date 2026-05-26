#include <StableMarriage/Globals.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <chrono>

// From NumberOfSMFunctions.h

bool ok2(int q[], int col) {
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
        std::cout << "Number of Stable Marriages: " << cnt << '\n';
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
    std::cout<<"Man"<<"  "<<"Woman"<<std::endl;
    for( i=0;i<n;i++)
    {
        std::cout<<" "<<i + 1<<"     "<<q[i] + 1<<std::endl;
    }
}

void numberOfStableMatchings() {
    iterationKiller = true;
    cnt = 0;
    int q[n];
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

void printHistogram(){
    for (int i = 0; i < histogramSize; i ++){
        if (histogram[i] != 0){
            std::cout << i << ": " << histogram[i] << '\n';
        }
    }
    std::cout << "Mean: " << mean / 1000.0 << '\n';
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
    int arr[n];
    int temp[n];
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            arr[j] = matrix[i][j].m;
            temp[j] = matrix[i][j].m;
        }
        std::sort(temp, temp + n);
        for(int k = 0; k < n; k++){
            arr[k] = findIndex(temp, n, arr[k]);
            matrix[i][k].m = arr[k];
        }
    }
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            arr[j] = matrix[j][i].w;
            temp[j] = matrix[j][i].w;
        }
        std::sort(temp, temp + n);
        for(int k = 0; k < n; k++){
            arr[k] = findIndex(temp, n, arr[k]);
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

void noSoulmatesRandomizer(){
    clearRankings();
    int ind = 0;
    for (int i = 0; i < n; i ++){
        ind = std::rand() % n;
        if (i == n - 1){
            while (repeatedOnes(ind)){
                ind = std::rand() % n;
            }
        }
        matrix[i][ind].m = 0;
    }
    for (int i = 0; i < n; i ++){
        for (int k = 0; k < n; k ++){
            mRank.push_back(k + 1);
        }
        mRank.erase(mRank.begin() + (n - 1));
        for (int j = 0; j < n; j ++){
            if (matrix[i][j].m == -1){
                ind = std::rand() % mRank.size();
                matrix[i][j].m = mRank[ind];
                mRank.erase(mRank.begin() + ind);
            }
        }
    }
    for (int i = 0; i < n; i ++){
        do{
            ind = std::rand() % n;
        }while(matrix[ind][i].m == 0);
        matrix[ind][i].w = 0;
    }
    for (int i = 0; i < n; i ++){
        for (int k = 0; k < n; k ++){
            wRank.push_back(k + 1);
        }
        wRank.erase(wRank.begin() + (n - 1));
        for (int j = 0; j < n; j ++){
            if (matrix[j][i].w == -1){
                ind = std::rand() % wRank.size();
                matrix[j][i].w = wRank[ind];
                wRank.erase(wRank.begin() + ind);
            }
        }
    }
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
        std::cout << std::endl;
    }
}

void updateDisplayArray(int r, int c){
    displayArr[r][c] = cnt;
}

void dropToOneLessN(int orignalN){
    int badRow = 0;
    int badCol = 0;
    int row = 0;
    int col = 0;
    int count = 0;
    int max = 0;
    int lastIteraation = 0;

    for (int i = 0; i < orignalN; i++)
    {
        for (int j = 0; j < orignalN; j++)
        {
            displayArr[i][j] = 0;
        }
    }
    std::ifstream FileToRead;
    FileToRead.open("/Users/thecownextdoorr/Desktop/eightcross.txt");
    std::ofstream specialMatrixFile("/Users/thecownextdoorr/Desktop/eightToSevenForHeatMap.txt", std::ios::app);
    std::string str;

    while (FileToRead >> str)
    {
        badRow = 0;
        badCol = 0;
        row = 0;
        col = 0;
        max = 0;
        lastIteraation = 0;
        int m;
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                FileToRead >> m;
                startNArray[i][j] = m;
            }
        }
        do
        {
            row = 0;
            col = 0;
            for (int i = 0; i < orignalN; i++)
            {
                for (int j = 0; j < orignalN; j++)
                {
                    if ((i != badRow && j != badCol))
                    {
                        matrix[row][col].m = startNArray[i][j];
                        matrix[row][col].w = n - matrix[row][col].m;
                        if (col < orignalN - 2)
                        {
                            col++;
                        }
                        else if (col == orignalN - 2)
                        {
                            col = 0;
                            row++;
                        }
                    }
                }
            }
            convertToGeneral();
            numberOfStableMatchings();
            specialMatrixFile << "Number of SM is " << cnt << std::endl;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    specialMatrixFile << matrix[i][j].m + 1 << ' ' << matrix[i][j].w + 1 << "  ";
                }
                specialMatrixFile << '\n';
            }
            if (cnt > max)
            {
                max = cnt;
            }
            updateDisplayArray(badRow, badCol);
            if (badRow == orignalN - 1 && badCol == orignalN - 1)
            {
                lastIteraation++;
            }
            else if (badRow < orignalN - 1)
            {
                badRow++;
            }
            else if (badRow == orignalN - 1)
            {
                badCol++;
                badRow = 0;
            }
        } while ((badRow != orignalN || badCol != orignalN) && lastIteraation != 1);
        count++;
        specialMatrixFile << "Count is " << count << std::endl;
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                specialMatrixFile << startNArray[i][j] + 1 << " ";
            }
            specialMatrixFile << std::endl;
        }
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                specialMatrixFile << displayArr[i][j] << "   ";
            }
            specialMatrixFile << std::endl;
        }
        std::cout << "count is " << count << std::endl;
    }
    specialMatrixFile.close();
    FileToRead.close();
    std::cout << std::endl << "max is " << max << std::endl;
    std::cout << "count is " << count << std::endl;
}

void dropTo2LessN(int orignalN){
    int row = 0;
    int col = 0;
    int count = 0;
    int max  = 0;
    std::ifstream FileToRead;
    FileToRead.open("/Users/thecownextdoorr/Desktop/TenCross.txt");
    std::ofstream FileToWrite("/Users/thecownextdoorr/Desktop/TenToEight.txt", std::ios::app);
    std::string str;
    while(FileToRead >> str){
        int m;
        for (int i = 0; i < n+2; i ++){
            for (int j = 0; j < n+2; j ++){
                FileToRead >> m;
                startNArray[i][j] = m;
                std::cout << startNArray[i][j] << " ";
                }
                std::cout << std::endl;
            }
        row = 0;
        col = 0;
        for(int badColOne = 0; badColOne < orignalN - 1; badColOne++){
            for(int badColTwo = badColOne + 1; badColTwo < orignalN; badColTwo++){
                for(int badRowOne = 0; badRowOne < orignalN - 1; badRowOne++){
                    for(int badRowTwo = badRowOne + 1; badRowTwo < orignalN; badRowTwo++){
                        row = 0;
                        col = 0;
                        for(int i = 0; i < orignalN; i++){
                            for(int j = 0; j < orignalN; j ++){
                                if((i != badRowOne && i != badRowTwo && j != badColOne && j != badColTwo)){
                                    matrix[row][col].m = startNArray[i][j];
                                    matrix[row][col].w =  n - matrix[row][col].m;
                                    if(col < orignalN - 3){
                                        col++;
                                    }
                                    else if (col == orignalN - 3){
                                        col = 0;
                                        row++;
                                    }
                                }
                            }
                        }
                        convertToGeneral();
                        numberOfStableMatchings();
                        if(cnt > max){
                            max = cnt;
                        }
                        count++;
                        std::cout << "count is " << count<< std::endl;
                        for (int i = 0; i < n; i ++){
                            for (int j = 0; j < n; j ++){
                                std::cout << matrix[i][j].m << ' ' << matrix[i][j].w << "  ";
                            }
                            std::cout << '\n';
                        }
                        std::cout << '\n';
                        FileToWrite << "Number of SM " << cnt << std::endl;
                        for (int i = 0; i < n; i ++){
                            for (int j = 0; j < n; j ++){
                                FileToWrite << matrix[i][j].m + 1 << ' ' << matrix[i][j].w + 1 << "  ";
                            }
                            FileToWrite << '\n';
                        }
                        FileToWrite << '\n';
                    }
                }
            }
        }
    }
    std::cout << "count is " << count;
    std::cout << "max is " << max << std::endl;
    FileToRead.close();
    FileToWrite.close();
}

void dropToLessN(int orignalN){
    int row = 0;
    int col = 0;
    int count = 0;
    int max  = 0;
    for(int badColOne = 0; badColOne < orignalN - 2; badColOne++){
    for(int badColTwo = badColOne + 1; badColTwo < orignalN - 1; badColTwo++){
    for(int badColThree = badColTwo + 1; badColThree < orignalN; badColThree++){
    for(int badRowOne = 0; badRowOne < orignalN - 2; badRowOne++){
    for(int badRowTwo = badRowOne + 1; badRowTwo < orignalN - 1; badRowTwo++){
    for(int badRowThree = badRowTwo + 1; badRowThree < orignalN; badRowThree++){
    row = 0;
    col = 0;
    for(int i = 0; i < orignalN; i++){
        for(int j = 0; j < orignalN; j ++){
            if((i != badRowOne && i != badRowTwo && i != badRowThree && j != badColOne && j != badColTwo && j != badColThree)){
                matrix[row][col].m = startNArray[i][j];
                matrix[row][col].w =  n - matrix[row][col].m;
                if(col < orignalN - 4){
                    col++;
                }
                else if (col == orignalN - 4){
                    col = 0;
                    row++;
                }
            }
       }
    }
    convertToGeneral();
    numberOfStableMatchings();
    if(cnt > max){
        max = cnt;
    }
    count++;
    std::cout << "count is " << count <<std::endl;
    std::ofstream myFile("/Users/thecownextdoorr/Desktop/18to15BeforeHillClimb", std::ios::app);
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n; j ++){
                    myFile << matrix[i][j].m + 1 << ' ' << matrix[i][j].w + 1 << "  ";
                }
                myFile << '\n';
            }
            myFile << '\n';
            myFile.close();
    }
    }
    }
    }
    }
    }
    std::cout << "count is " << count;
    std::cout << "max is " << max << std::endl;
}
