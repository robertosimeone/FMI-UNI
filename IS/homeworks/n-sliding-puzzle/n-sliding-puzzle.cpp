#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
using namespace std;
#include <stdlib.h>
#include <cmath>
#include <limits.h>
#include <set>
vector<int>board;
vector<int> goalState;
vector<int> goalStateIndex;
//set<vector<int> > visited;
int cnt = 0;
void printBoard(){
    int size = sqrt(board.size());
    for(int i = 0 ;i < board.size();i++) {
        cout << board[i] << " ";
        if((i+1)%size == 0)
            cout << endl;
    }
}
bool isGoal(){
    if(board == goalState)
        return true;
    return false;
}
int singleManhattan(int index,int goalIndex,int boardSize){
    int index_i = index/boardSize;
    int index_j = index%boardSize;
    int goal_i = goalIndex/boardSize;
    int goal_j = goalIndex%boardSize;
    return abs(index_i-goal_i) + abs(index_j-goal_j);
}
//
int indexConversionToOne(int row, int col,int boardSize){
    return boardSize*row+col;
}
pair<int,int> indexConversionToTwo(int index,int boardSize){
    return pair<int,int>(index/boardSize,index%boardSize);
}
int manhattan(){
    int totalManhattan = 0;
    int boardSize = sqrt(board.size());
    for(int i = 0 ; i < board.size();i++){
        if(board[i]!=0){
            totalManhattan+=singleManhattan(i,goalStateIndex[board[i]],boardSize);
        }

    }
    return totalManhattan;

}
//naive approach
int inversionCount(){
    int inversions = 0;
    for(int i  = 0 ; i < board.size();i++){
        int currentNumber = board[i];
        if(currentNumber == 0)
            continue;
        for(int j = i-1 ; j >=0;j--){
            if(board[j]!=0 and board[j]>currentNumber){
                inversions++;
            }
        }
    }
    return inversions;
}
bool isSolvable(int zeroIndex){
    int boardSize = sqrt(board.size());
    int inversions = inversionCount();
    int zeroRow = zeroIndex/boardSize;
    if(boardSize%2 == 0){
        if((inversions + zeroRow)%2 == 1)
            return true;
    }
    else{
        if(inversions%2 == 0)
            return true;
    }
    return false;

}

bool checkCoordinates(pair<int,int>& coordinates,int boardSize){
    if(coordinates.first>=0 and coordinates.first<boardSize and coordinates.second>=0 and coordinates.second <boardSize)
        return true;
    return false;
}
int move(pair<int,int>&row_col,int zeroIndex){
    int boardSize = sqrt(board.size());
    pair<int,int> new_coordinates = indexConversionToTwo(zeroIndex,boardSize);
    new_coordinates.first +=row_col.first;
    new_coordinates.second +=row_col.second;
    bool inBounds = checkCoordinates(new_coordinates, boardSize);
    if(!inBounds)
        return -1;
    else{
        int new_index = indexConversionToOne(new_coordinates.first,new_coordinates.second,boardSize);
        swap(board[zeroIndex],board[new_index]);
//        if(visited.count(board) == 1){
//            swap(board[zeroIndex],board[new_index]);
//            return -1;
//        }
        return new_index;
    }


}
string pairToString(pair<int,int> & move){
    string result = "";
    if(move.first == 0 && move.second == 1){
        result = "left";
    }
    if(move.first == 0 && move.second == -1){
        result = "right";
    }
    if(move.first == 1 && move.second == 0){
        result = "up";
    }
    if(move.first == -1 && move.second == 0){
        result = "down";
    }
    return result;
}
bool compare(pair<int,int>& move1,pair<int,int>& move2,int zeroIndex){
    int move1_result = move(move1,zeroIndex);
    int move1_manhattan = INT_MAX;
    int move2_manhattan = INT_MAX;
    if(move1_result!=-1) {
        move1_manhattan = manhattan();
        pair<int,int> backMove;
        backMove.first = move1.first*-1;
        backMove.second = move1.second*-1;
        move(backMove,move1_result);


    }
    int move2_result = move(move2,zeroIndex);
    if(move2_result!=-1) {
        move2_manhattan = manhattan();
        pair<int,int> backMove;
        backMove.first = move2.first*-1;
        backMove.second = move2.second*-1;
        move(backMove,move2_result);

    }
    return move1_manhattan <= move2_manhattan;

}
int search(int zeroIndex,vector<string>&guide,vector<pair<int,int> >&steps,int cost,int  bound,vector<pair<int,int> >moves){
    int f = cost + manhattan();
    if (f > bound){
        return f;
    }
    if(isGoal()){
        cout << steps.size()<<endl;
        for(int i =0 ; i <= steps.size();i++){
            cout << guide[i] << endl;
        }
        return 0;
    }
    int min = INT_MAX;
//    sort(moves.begin(),moves.end(),[](pair<int,int> &a, pair<int,int>&b){
//        int zeroIndex = -1;
//        for(int i = 0 ;i < board.size();i++){
//            if(board[i]==0) {
//                zeroIndex = i;
//                break;
//            }
//        }
//        return compare(a,b,zeroIndex);
//    });
    for(int i = 0 ; i <4;i++){
        if(steps.size()!=0){
            pair<int,int> oppositeStep;
            oppositeStep.first = steps.back().first*-1;
            oppositeStep.second = steps.back().second*-1;
            if(oppositeStep==moves[i]){
                continue;
            }
        }
            int zero_index = move(moves[i],zeroIndex);
            if(zero_index != -1) {
                cnt++;
//                visited.insert(board);
                string instruction = pairToString(moves[i]);
                guide.push_back(instruction);
                steps.push_back(moves[i]);
                int t = search(zero_index, guide, steps, cost + 1, bound, moves);
                if (t == 0)
                    return 0;
                if (t < min) {
                    min = t;
                }
                pair<int, int> backMove;
                backMove.first = moves[i].first * (-1);
                backMove.second = moves[i].second * (-1);
                //move backwards
                move(backMove, zero_index);
                guide.pop_back();
                steps.pop_back();

            }
    }
    return min;

}
//fix for unsolvable
bool ida_star(int zeroIndex,vector<string>&guide,vector<pair<int,int>
>&steps,vector<pair<int,int> >moves){
    if(!isSolvable(zeroIndex))
        return false;
    int treshold = manhattan();
    int t;
    while(true){
//        visited.clear();
//        visited.insert(board);
        t = search(zeroIndex,guide,steps,0,treshold,moves);
        if(t == 0)
            return true;
        treshold = t;
    }
    cnt = 0;
}

int main() {
    vector<pair<int, int> > moves {make_pair(1, 0), make_pair(-1, 0),make_pair(0, -1), make_pair(0, 1)};
    vector<string>guide;
    vector<pair<int,int> >steps;
    int currentZeroIndex = -1;
    int tileNumber;
    cin >> tileNumber;
    goalState.resize(tileNumber+1,0);
    goalStateIndex.resize(tileNumber+1,0);
    int chosen_index;
    cin>> chosen_index;
    if(chosen_index==-1){
        chosen_index = tileNumber;
    }
    int temp;
    for(int i = 0 ; i < tileNumber+1;i++){
        cin>>temp;
        board.push_back(temp);
        if(temp == 0)
            currentZeroIndex = i;
    }
    std::clock_t start = std::clock();
    int counter = 1;
    for(int i = 0 ; i < tileNumber+1;i++){
        if(chosen_index == i){
            goalStateIndex[0] = i;
            goalState[i] = 0;
        }
        else{
            goalStateIndex[counter] = i;
            goalState[i] = counter;
            counter++;
        }
    }
    bool result = ida_star(currentZeroIndex,guide,steps,moves);
    if(!result)
        cout << "Unsolvable board" << endl;
    std::clock_t end = std::clock();
    double elapsedSeconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << elapsedSeconds << " seconds" << std::endl;

    }
//}
//implement dynamic moves
//15
//-1
//9 5 1 12
//10 0 11 13
//3 7 14 6
//2 8 15 4 - > cannot calculate this one