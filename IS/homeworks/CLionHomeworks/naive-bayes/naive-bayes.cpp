#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
vector<string> df;
int **republicans;
int **democrats;
int democrats_number = 0;
int republicans_number = 0;
int test_counter = 1;
vector<vector<string>> split_data;
void readFile(string &filename){
    ifstream data(filename);
    if(data.is_open()){
        string line = "";
        while(getline(data,line)){
            df.push_back(line);
        }
    }
    data.close();
}
void reevaluate_matrix(string & current_data){
    int size = current_data.size();
    string cls = "";
    int second_start = 0;
    while(current_data[second_start]!=','){
        cls+=current_data[second_start];
        second_start++;
    }
    cls == "republican" ? republicans_number++ : democrats_number++;
    second_start++;
    int counter = 0;
    for(int i = second_start; i < size;++i){
        if(current_data[i] == ',')
            continue;
        if(current_data[i] == 'n'){
            if(cls == "republican"){
                republicans[0][counter]++;
            }
            else{
                democrats[0][counter]++;
            }

        }
        else if(current_data[i] == 'y'){
            if(cls == "republican"){
                republicans[1][counter]++;
            }
            else{
                democrats[1][counter]++;
            }

        }
        else if(current_data[i] == '?'){
            if(cls == "republican"){
                republicans[2][counter]++;
            }
            else{
                democrats[2][counter]++;
            }

        }
        counter++;

    }
}
double getTestAccuracy(vector<string>& test){
    // u must not know the cls
    int counter = 0;
    string curr_str;
    int right_predictions = 0;
    int size = test.size();
    for(int i =0  ; i < size;++i){
        counter = 0 ;
        curr_str = "";
        double demProb =  0;
        double repProb = 0;
        while(test[i][counter] != ','){
            curr_str+=test[i][counter];
            counter++;
        }
        counter++;
        int second_counter = 0;
        unsigned long curr_size = test[i].size();
        int cur_feature = 0;
        for(int j = counter;j < curr_size;++j){
            int curr_index = -1;
            if(test[i][j] == ',')
                continue;
            test[i][j] == 'n' ? curr_index = 0
                              : test[i][j] == 'y' ? curr_index = 1
                                                  : curr_index = 2;
            //calculate both prob - > P(democrat | x) and P(republican | x)
            int denDemProb = 0;
            int denRepProb = 0;
            for(int i = 0 ; i < 3;i++){
                denDemProb+= democrats[i][second_counter];
                denRepProb+=republicans[i][second_counter];
            }
            demProb += log2((double)(democrats[curr_index][second_counter] + 1)/(denDemProb+3));
            repProb += log2((double)(republicans[curr_index][second_counter] + 1)/(denRepProb+3));
            second_counter++;
        }
        demProb+=log2((double)(democrats_number+1)/(democrats_number+republicans_number+2));
        repProb+=log2((double)(republicans_number+1)/(democrats_number+republicans_number+2));
        string result = "";
        demProb <= repProb ? result="republican" : result="democrat";
        if(result == curr_str){
            right_predictions++;
        }
    }
    cout << "Train/test iteration : " << test_counter++ << endl;
    cout << "Accuracy :" << (double)right_predictions/size*100 << endl << endl;
    return (double)right_predictions/size*100;
}
void naive_bayse(){
    //setup matrix
    //choose test set
    double sum = 0;
    for(int i = 0 ; i < 10;i++){
        republicans = new int*[3];
        democrats = new int*[3];
        for(int k = 0 ; k < 3;k++){
            republicans[k] = new int[16]{0};
            democrats[k] = new int[16]{0};
        }
        //iterate over training sets and train the model
        for(int j = 0; j < 10;j++){
            if(j == i)
                continue;
            unsigned long size = split_data[j].size();
            for(int z = 0 ; z < size; ++z){
                reevaluate_matrix(split_data[j][z]);
            }
        }
        sum+= getTestAccuracy(split_data[i]);
    //cleanup matrix for the next iteration of test/training
    for(int p = 0 ;p < 3;++p){
        delete [] republicans[p];
        delete [] democrats[p];
    }
    republicans_number = 0;
    democrats_number = 0;
    delete[] republicans;
    delete[] democrats;
    }
    cout << endl << "Avg accuracy from 10 train/test iterations :" << sum/10 << endl;
}

void split_into_ten(){
    split_data.resize(10);
    const int num = 43;
    int which_vector = 0;
    int counter = 0;
    unsigned long df_size = df.size();
    for(int i = 0 ; i < df_size;++i) {
        split_data[which_vector].push_back(df[i]);
        if (which_vector == 9)
            continue;
        counter++;
        if (counter == num) {
            which_vector++;
            counter = 0;
        }
    }
}
int main(){
    string filename = "/Users/robertborisov/UNI/IS/homeworks/CLionHomeworks/naive-bayes/congressional+voting+records/house-votes-84.data";
    readFile(filename);
    split_into_ten();
    naive_bayse();

    return 0;

}
//435 examples
//16 features - > xi
// class - > republican/democrat - > CK
//P(CK | xt )  = P(CK)*P(xi|Ck)....*P(xn|CK)