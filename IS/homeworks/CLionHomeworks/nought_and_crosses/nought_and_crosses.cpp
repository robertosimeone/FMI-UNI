#include <iostream>
#include <string>
#include <utility>
#include <cmath>
#include <climits>
using namespace std;
const int globalA = 10;
int * rowAssessments;
int * colAssessments;
int frontDiag = 0;
int backDiagonal = 0;
pair <int,int > min_value(string &state,int depth,char & pc_symbol,char & player_symbol,int pos,int alfa,int beta);
bool isBoardFull(string & state){
    int size = state.size();
    for(int i =0  ; i < size;++i){
        if(state[i] == '-')
            return false;
    }
    return true;
}
void updateAssessments(int pos,char & symbol){
    int x = pos/3;
    int y = pos%3;
    if(symbol == 'X') {
        rowAssessments[x]++;
        colAssessments[y]++;
        if( x == y)
            frontDiag++;
        if(x+y==2)
            backDiagonal++;
    }
    else if(symbol == 'O') {
        rowAssessments[x]--;
        colAssessments[y]--;
        if( x == y)
            frontDiag--;
        if(x+y==2)
            backDiagonal--;
    }
}
void returnUpdateAssessments(int pos,char & symbol){
    int x = pos/3;
    int y = pos%3;
    if(symbol == 'X') {
        rowAssessments[x]--;
        colAssessments[y]--;
        if( x == y)
            frontDiag--;
        if(x+y==2)
            backDiagonal--;
    }
    else if(symbol == 'O') {
        rowAssessments[x]++;
        colAssessments[y]++;
        if( x == y)
            frontDiag++;
        if(x+y==2)
            backDiagonal++;
    }
}
bool hasPlayerWon(string & state,char & symbol) {
    int size = state.size();
    int param = -1;
    if (symbol == 'X')
        param = 3;
    else
        param = -3;
    if (frontDiag == param || backDiagonal == param)
        return true;
    for (int i = 0; i < size; ++i) {
        if (rowAssessments[i] == param) {
            return true;
        }
    }
    for (int i = 0; i < size; ++i) {
        if (colAssessments[i] == param) {
            return true;
        }

    }
    return false;
}
int terminal_test(string & state,int depth,char & pc_symbol,char & player_symbol){
    if(hasPlayerWon(state,pc_symbol)) {
//        cout << "id-globalA-depth: " <<x << " "<< globalA - depth <<endl;
//        x++;
        return globalA - depth;
    }
    if(hasPlayerWon(state,player_symbol))
        return depth-globalA;
//        return -1;
    if(isBoardFull(state))
        return 0;
    return -100;

}
pair <int,int > max_value(string &state,int depth,char & pc_symbol,char & player_symbol,int pos,int alfa,int beta){
    int result = terminal_test(state,depth,pc_symbol,player_symbol);
    if(result !=-100)
        return make_pair(result,pos);
    pair<int,int> v;
    v.first = INT_MIN;
    pair<int,int> res;
    for(int i = 0 ; i < state.size();i++){
        if(state[i]=='-'){
            state[i] = pc_symbol;
            updateAssessments(i,pc_symbol);
            res = min_value(state,depth+1,pc_symbol,player_symbol,i,alfa,beta);
            if(res.first > v.first){
                v.first = res.first;
                v.second = i;
                }
            state[i] = '-';
            returnUpdateAssessments(i,pc_symbol);
            if(v.first>=alfa) {
                alfa = v.first;
            }
            if(v.first>=beta) {
//                cout << "------------------------------------------------------------------------------------" << endl;
//                cout << "v.first: " << v.first << " alfa : " <<alfa  << " beta : " << beta << endl;
//                cout << "max cut activated on depth" << depth << " and iteration " << i << endl;
//                cout << "------------------------------------------------------------------------------------" << endl;
                return v;
            }
            // try changing this one with the

        }
    }
    return v;
}
pair <int,int > min_value(string &state,int depth,char & pc_symbol,char & player_symbol,int pos,int alfa,int beta) {
    int result = terminal_test(state, depth, pc_symbol, player_symbol);
    if (result != -100)
        return make_pair(result, pos);
    pair<int, int> v;
    v.first = INT_MAX;
    pair<int, int> res;
    for (int i = 0; i < state.size(); i++) {
        if (state[i] == '-') {
            state[i] = player_symbol;
            updateAssessments(i, player_symbol);
            res = max_value(state, depth+1, pc_symbol, player_symbol, i,alfa,beta);
            if(res.first <v.first){
                v.first = res.first;
                v.second = i;
            }
            state[i] = '-';
            returnUpdateAssessments(i, player_symbol);
            if(v.first<=beta) {
                beta = v.first;
            }
            if(v.first<=alfa){
//                cout << "------------------------------------------------------------------------------------" << endl;
//                cout << "v.first: " << v.first << " alfa : " <<alfa  << " beta : " << beta << endl;
//                cout << "min cut activated on depth" << depth << " and iteration " << i << endl;
//                cout << "------------------------------------------------------------------------------------" << endl;
                return v;
            }

        }
    }
    return v;
}

void MiniMaxDecision(string &state,char & pc_symbol, char & player_symbol){
    pair<int,int> result = max_value(state,0,pc_symbol,player_symbol,-1,INT_MIN,INT_MAX);
    cout << "result.first : " << result.first << " result.second : " << result.second << endl;
    state[result.second] = pc_symbol;
    updateAssessments(result.second,pc_symbol);
}
void printBoard(string & state){
    int size = state.size();
    for(int i = 0 ; i < size;i++){
        cout <<'_';
    }
    cout <<endl;
    for(int i = 0 ;i < size;i++){
        cout << state[i];
        if((i+1)%3 == 0){
            cout << endl;
        }
        else{
            cout << " ";
        }
    }
    for(int i = 0 ; i < size;i++){
        cout <<'_';
    }
    cout <<endl;
}
bool checkValidCoordinates(int x,int y,string & state){
    int size = state.size();
    return (x >=0 && x < size && y>=0 && y<size);
}
void game(string & state,char & player_symbol,char & pc_symbol,bool  isPlayerFirst){
    rowAssessments = new int[3]{0};
    colAssessments = new int[3]{0};
    int size = state.size()/3;
    int playerX,playerY;
    int pc_turn_choice;
    int result = -10;
    while(true){
        printBoard(state);
        if(isPlayerFirst) {
            cout << "It's your turn! Please enter your coordinates" << endl;
            cin >> playerX >> playerY;
            while (!checkValidCoordinates(playerX, playerY, state)) {
                cout << "Invalid Coordinates. Please try again" << endl;
                cout << "It's your turn! Please enter your coordinates" << endl;
                cin >> playerX >> playerY;
            }
            state[playerX * size + playerY] = player_symbol;
            printBoard(state);
            updateAssessments(playerX * size + playerY, player_symbol);
            result = terminal_test(state, 0, pc_symbol, player_symbol);
            if (result != -100) {
                break;
            };
        }
        MiniMaxDecision(state,pc_symbol,player_symbol);
        result  =terminal_test(state,0,pc_symbol,player_symbol);
        if(result!=-100){
            break;
        };
        if(!isPlayerFirst)
            isPlayerFirst = true;
    }
    if(result >= -10 && result <=-1){
        cout << "You have won the game!" <<endl;
    }
    else if(result == 0){
        cout << "You drew the game with the computer." <<endl;
    }
    else{
        cout <<"You have lost the game! Better luck next time!" << endl;
    }
    printBoard(state);
}
bool isAnswerValid(string & answer){
    if(answer!="y"){
        if(answer!="n")
            return false;
        return true;
    }
    return true;
}

int main(){
    string answer;
    char computer_symbol;
    char player_symbol;
    string board ="---------";
    cout << "Do you want to go first? [y/n]" << endl;
    cin >> answer;
    while(!isAnswerValid(answer)){
        cout << "Your answer couldn't be recognized. Please try again" << endl;
        cout << "Do you want to go first? [y/n]" << endl;
        cin >> answer;
    }
    if(answer=="y"){
        computer_symbol = 'O';
        player_symbol = 'X';
        game(board,player_symbol, computer_symbol,player_symbol=='X');
        delete[] rowAssessments;
        delete[] colAssessments;

    }
    else if(answer == "n"){
        computer_symbol = 'X';
        player_symbol = 'O';
        game(board,player_symbol, computer_symbol,player_symbol=='X');
        delete[] rowAssessments;
        delete[] colAssessments;
    }

    return 0;
}
//result.first : 0 result.second : 8
//_________
//        X - -
//- - -
//- - O
//        _________