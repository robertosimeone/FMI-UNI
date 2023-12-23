#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
#include <time.h>
#include <iomanip>
#include <limits.h>
#include <random>
int * n_queens;
//vector<int>n_queens;
//vector<int>row_conflicts;
//vector<int>diag_left_right_conflicts;
//vector<int>diag_right_left_conflicts;
int * row_conflicts;
int * diag_left_right_conflicts;
int * diag_right_left_conflicts;
int boardDimension;
int getSingleSquareConflicts(int &x,int &y,bool  isQueen){
//    int conflicts = 0;
//    conflicts+=row_conflicts[x]-isQueen;
//    conflicts+=diag_left_right_conflicts[y-x+boardDimension-1]-isQueen;
//    conflicts+=diag_right_left_conflicts[x+y]-isQueen;
//    conflicts+=row_conflicts[x]+diag_left_right_conflicts[y-x+boardDimension-1]+diag_right_left_conflicts[x+y]-3*isQueen;
//    return conflicts;
    return row_conflicts[x]+diag_left_right_conflicts[y-x+boardDimension-1]+diag_right_left_conflicts[x+y]-3*isQueen;

}
int getColWithQueenWithMaxConflicts(){
    int maxConflictQueenConflicts = -1;
    vector<int> maxConflictsQueens;
    int currQueenConflicts;
    for(int i = 0 ; i < boardDimension;++i){
        currQueenConflicts = getSingleSquareConflicts(n_queens[i],i,true);
        if(maxConflictQueenConflicts < currQueenConflicts){
            maxConflictQueenConflicts = currQueenConflicts;
            maxConflictsQueens.clear();
            maxConflictsQueens.push_back(i);
        }
        else if(maxConflictQueenConflicts == currQueenConflicts){
            maxConflictsQueens.push_back(i);
        }
    }
    if(maxConflictQueenConflicts == 0){
        return -1;
    }
    if(maxConflictsQueens.size() == 1){
//        if(maxConflictQueenConflicts == 0){
//            return -1;
//        }
        return maxConflictsQueens[0];
    }
    else{
//        if(maxConflictQueenConflicts == 0){
//            return -1;
//        }
//        int rand_index = rand() % maxConflictsQueens.size();
        return maxConflictsQueens[rand() % maxConflictsQueens.size()];
    }

}
int getRowWithMinConflicts(int & currentCol){
    int minConflicts = INT_MAX;
    bool isQueen = false;
    int queen_index = n_queens[currentCol];
    vector<int> minConflictsQueens;
    int currQueenConflicts;
    for(int i = 0 ; i < boardDimension;++i){
        if(queen_index == i){
            isQueen = true;
        }
        else{
            isQueen = false;
        }
        currQueenConflicts = getSingleSquareConflicts(i,currentCol,isQueen);
        if(minConflicts > currQueenConflicts){
            minConflicts = currQueenConflicts;
            minConflictsQueens.clear();
            minConflictsQueens.push_back(i);
        }
        else if(minConflicts == currQueenConflicts){
            minConflictsQueens.push_back(i);
        }
    }
    if(minConflictsQueens.size() == 1){
        return minConflictsQueens[0];
    }
    else{
        /*int rand_index = rand() % minConflictsQueens.size();*/
        return minConflictsQueens[rand() % minConflictsQueens.size()];
    }

}
void updateMatrix(int & previous_row,int & current_row,int & col){
    row_conflicts[previous_row]--;
    diag_left_right_conflicts[col-previous_row+boardDimension-1]--;
    diag_right_left_conflicts[col+previous_row]--;

    row_conflicts[current_row]++;
    diag_left_right_conflicts[col-current_row+boardDimension-1]++;
    diag_right_left_conflicts[col+current_row]++;
}
void updateMatrixInitially(int & current_row,int & col){
    row_conflicts[current_row]++;
    diag_left_right_conflicts[col-current_row+boardDimension-1]++;
    diag_right_left_conflicts[col+current_row]++;
}
void randomBoardInitialization(){
//    for(int i = 0;  i < boardDimension;i++){
//        n_queens[i] = rand()%boardDimension;
//        updateMatrixInitially(n_queens[i],i);
//    }
//-------------------------------------
//    for(int i = 0 ; i < boardDimension;++i){
//        int currQueenRowIndex = getRowWithMinConflicts(i);
//        n_queens[i] = currQueenRowIndex;
//        updateMatrixInitially(currQueenRowIndex,i);
//    }
//---------------------------------------------------------
    int startRow = boardDimension/2;

    int initialCol = 0;
    int currCol = initialCol;
    for(int i = 0 ; i < boardDimension;i++){
        n_queens[currCol] = startRow;
        updateMatrixInitially(startRow,currCol);
        startRow++;
        currCol+=2;
        if(currCol>=boardDimension || startRow>=boardDimension){
           startRow=0;
           initialCol++;
           currCol = initialCol;
        }
    }


}
void printBoard(){
    cout << "[ ";
    for(int i = 0; i < boardDimension;i++){
        cout << "'" << n_queens[i] << "'";
        if(i!=boardDimension-1)
            cout << ", ";
    }
    cout << " ]";
    cout << endl;

}
void solve(){
    const int k = 1500;
//    n_queens.resize(boardDimension,-1);
    n_queens = new int[boardDimension]{-1};
//    row_conflicts.resize(boardDimension,0);
    row_conflicts = new int[boardDimension]{0};
//    diag_right_left_conflicts.resize(2*boardDimension-1,0);
    diag_right_left_conflicts = new int[2*boardDimension-1]{0};
//    diag_left_right_conflicts.resize(2*boardDimension-1,0);
    diag_left_right_conflicts = new int[2*boardDimension-1]{0};
    randomBoardInitialization();
    int iter = 0;
    while(iter++ <=k*boardDimension){
        int col = getColWithQueenWithMaxConflicts();
        if(col==-1){
           return;
        }
        int row = getRowWithMinConflicts(col);
        int old = n_queens[col];
        n_queens[col] = row;
        updateMatrix(old,row,col);
    }
    delete [] n_queens;
    delete [] row_conflicts;
    delete[] diag_left_right_conflicts;
    delete [] diag_right_left_conflicts;
    int maxConflictQueenCol = getColWithQueenWithMaxConflicts();
    if(maxConflictQueenCol!=-1){
        solve();
        return;
    }
}
int main(){
    cin >> boardDimension;
    if(boardDimension == 2 || boardDimension == 3){
        cout << -1 << endl;
        return 0;
    }
    else if(boardDimension == 1){
        cout <<"["<<0<<"]"<<endl;
        return 0;
    }
    clock_t start, end;
    start = clock();
//    ios_base::sync_with_stdio(false);
    solve();
//    vector<int> result = solve();
    end = clock();
    if(boardDimension<=50){
    cout << "[";
    //n_queens.size()
    for(int i = 0; i < boardDimension;i++){
        cout<< n_queens[i];
        if(i!=boardDimension-1)
            cout << ", ";
    }
    cout << "]";
    cout << endl;
    }
    else{
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout<< setprecision(2) << fixed << time_taken<<endl;
    }


    return 0;

}
