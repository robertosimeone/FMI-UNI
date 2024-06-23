#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <cmath>
int counter = 0;
using namespace std;
queue<string> recurrence_events;
queue<string> no_recurrence_events;
vector<vector<string>> kfold_vector;
vector<string> current_kfolddata;
map<int,string> title;
const int minSampleSize = 25;
const int no_rec_ev_per_set = 40;
const int rec_ev_per_set = 17;

void readFile(string &filename){
    ifstream data(filename);
    if(data.is_open()){
        string line = "";
        while(getline(data,line)){
            if(line[0] == 'n'){
                no_recurrence_events.emplace(line);
            }else{
                recurrence_events.emplace(line);
            }
        }
    }
    data.close();
}
void arrange_kfold_vector(int k){
    kfold_vector.resize(5);
    int extra = 0;
    for(int i = 0; i < k; i ++){
        if(i == 4)
            extra = 1;
        for(int j = 0;j < rec_ev_per_set;j++){
            kfold_vector[i].push_back(recurrence_events.front());
            recurrence_events.pop();
        }
        for(int j = 0;j < no_rec_ev_per_set+extra;j++){
            kfold_vector[i].push_back(no_recurrence_events.front());
            no_recurrence_events.pop();
        }
    }
}
void inspect_vectors(){
    for(int i =0 ; i < kfold_vector.size();i++){
        cout << "vector " << i << " elements:" << endl;
        for(int j = 0 ; j < kfold_vector[i].size();j++){
            cout << "\t" << j <<" :"<< kfold_vector[i][j] << endl;
        }
    }
}
void concatCurrentFold(int chosen){
    vector<string> concatenatedVector;
    for(int i = 0; i < kfold_vector.size();++i){
        if(i!=chosen)
            std::move(kfold_vector[i].begin(), kfold_vector[i].end(), std::back_inserter(concatenatedVector));
    }
    current_kfolddata = concatenatedVector;
}
string readFromCol(int col,string row){
    string result;
    int counter = 0 ;
    for(int i = 0 ; i < col;i++){
        while(row[counter]!=','){
            counter++;
        }
        counter++;
    }
    char separator;
    if(col !=9)
        separator = ',';
    else
        separator = '\0';
    while(row[counter]!=separator){
        result +=row[counter];
        counter++;
    }
//    cout << "<readFromCol>: " << result << endl;
    return result;

}
class State{
    //for sure needed
public:
//    vector<State> next_states;
    int ch_number;
    State * previous_state = nullptr;


    set<int> forbidden_rows;
    set<int> forbidden_cols;

    map<int,map<string,pair<int,int> > > table_yes_no;
    int total_yes;
    int total_no;
    vector<State*> children;

    double entropy = -1;
    bool isLeafNode;
//    string decision;
    int data_size;
    vector<string> filtered_attributes;

    string attribute_value;
    string dominant;

    int bestGainColumn;

    //check for previous/next states
//    string atttribute_value,State * previous_state,set<int> forbidden_rows,set<int> forbidden_cols,int col
    State(State * previous_state = nullptr,string attribute_value = "none"){
//        dominant = "none";
//        decision = "none";
        bestGainColumn = -1;
        this->previous_state = previous_state;
        this->attribute_value = "none";
        if(previous_state!=nullptr) {
            this-> filtered_attributes = previous_state->filtered_attributes;
            this->filtered_attributes.push_back(attribute_value);
            if(filtered_attributes[0] == "1" and filtered_attributes[1] == "20-24"){
                int b = 10;
            }
            this->forbidden_cols = previous_state->forbidden_cols;
            this->forbidden_cols.emplace(previous_state->bestGainColumn);

            this->forbidden_rows = previous_state->forbidden_rows;
            string result;

            //filter the data
            if (attribute_value != "none") {
                for (int i = 0; i < current_kfolddata.size(); ++i) {
                    if (this->forbidden_rows.find(i) == this->forbidden_rows.end()) {
                        result = readFromCol(previous_state->bestGainColumn, current_kfolddata[i]);
                        if (result != attribute_value) {
                            this->forbidden_rows.emplace(i);
//                            cout << i << endl;
                        }
                    }
                }
                this->attribute_value = attribute_value;

            }
        }
        this->calculateTable();

        this->calculateEntropy();
        this->findIsLeafNode();
        cout << "data size" << data_size << endl;
        cout << "yes count: " << total_yes << endl;
        cout << "no count: " << total_no << endl;
        cout << "entropy of class" << this->entropy << endl;
        if(!isLeafNode)
            cout << "not a leaf node; continuing;" << endl;
        else
            cout << "leaf node;not  continuing;" << endl;
        cout << "forbidden rows number : " << forbidden_rows.size() << endl;
        for(int i =0 ; i < filtered_attributes.size();i++){
            cout << filtered_attributes[i] << " ";
        }
        cout << endl << endl;
        if(entropy!=0) {
            this->bestGainColumn = this->findBestGainColumn();
        }

    }
    void updateTableWithSingleRow(string row){
        string curr_word;
        char separator;
        if(row == "recurrence-events,40-49,premeno,25-29,0-2,no,3,left,right_up,no"){
            int b = 10;
        }
        if(row[0] == 'r'){
            int start = 18;
            //todo check listings
            for(int i = 1 ; i <= 9;i++){
                if(forbidden_cols.find(i)!=forbidden_cols.end())
                    continue;
                curr_word = "";
                if(i!=9){
                    separator = ',';
                }
                else{
                    separator = '\0';
                }
                while(row[start]!=separator){
                    curr_word+=row[start++];

                }
                table_yes_no[i][curr_word].first++;
                start++;
            }

        }
        else {
            int start = 21;
            for(int i = 1 ; i <= 9;i++){
                if(forbidden_cols.find(i)!=forbidden_cols.end())
                    continue;
                curr_word = "";
                if(i!=9){
                    separator = ',';
                }
                else{
                    separator = '\0';
                }
                while(row[start]!=separator){
                    curr_word+=row[start++];

                }
                table_yes_no[i][curr_word].second++;
                start++;
            }
        }
    }
    void calculateTable(){
        for(int i = 0  ; i < current_kfolddata.size();++i){
            if(forbidden_rows.find(i)==forbidden_rows.end()){
                updateTableWithSingleRow(current_kfolddata[i]);
            }
        }

    }
    double calculateSingleEntropy(pair<int,int> dis){
        if(dis.first ==0 or dis.second==0){
            return 0;
        }
        double first_pi = (double)dis.first/(dis.first+dis.second);
//        cout << -(double)first_pi*log2(first_pi)-(double)(1-first_pi)*log2(1-first_pi) << endl;
        return -(double)first_pi*log2(first_pi)-(double)(1-first_pi)*log2(1-first_pi);
    }
    //todo fix this not working properly
    double findColumnEntropy(int column_index){
        double entropy = 0;
        double current_chance;
        for (auto it = table_yes_no[column_index].begin(); it != table_yes_no[column_index].end(); it++) {
            double current_pi = (double)(it->second.first+it->second.second)/data_size;
            entropy+=current_pi * calculateSingleEntropy(it->second);
        }
        return entropy;

    }
//    map<int,map<string,pair<int,int> > > table_yes_no;
    //do not check for forbidden cols
    int findBestGainColumn(){
        double maxGain = INT_MIN;
        int maxGainColumn = -1;
        double currentGain = -1;

        for(int i = 1 ; i <=9;i++){
            if(forbidden_cols.find(i)!=forbidden_cols.end())
                continue;
            currentGain = this->entropy - findColumnEntropy(i);
            cout << "info gain column: " << i << " is : " << currentGain << endl;
            if(currentGain >= maxGain) {
                maxGain = currentGain;
                maxGainColumn = i;
            }
        }
        cout << "info gain column: " << maxGainColumn << " is : " << maxGainColumn << endl;
        return maxGainColumn;
    }



    void calculateEntropy(){
        int yes_count = 0;
        int no_count = 0;
        string result;
        for(int i =0 ; i < current_kfolddata.size();i++){
            if(forbidden_rows.find(i)==forbidden_rows.end()){
                result = readFromCol(0,current_kfolddata[i]);
                if(result == "recurrence-events"){
                    yes_count++;
                }
                else{
                    no_count++;
                }
            }
        }
        int whole = yes_count+no_count;
        total_no = no_count;
        total_yes = yes_count;
        data_size = whole;
        if(yes_count == 0 or no_count == 0)
            this->entropy = 0;
        else
            this->entropy = -log2((double)yes_count/whole)*yes_count/whole-log2((double)no_count/whole)*no_count/whole;
//        for(auto it = forbidden_cols.begin();it!=forbidden_cols.end();it++){
//            cout <<
//        }
        if(yes_count>no_count){
            dominant = "recurrence-events";
        }else if(no_count>yes_count){
            dominant = "no-recurrence-events";
        }
        else{
            dominant = "equal";
        }

    }
    void findIsLeafNode(){
        this->isLeafNode = entropy==0;
    }
};

string readLabel(string row){
    string result;
    int counter= 0 ;
    while(row[counter]!=','){
        result+=row[counter];
        counter++;
    }
    return result;
}
class PostID3{
public:
    State * root;
    int test_set;
    PostID3(int test_set_index){
        this->test_set = test_set_index;
        this->buildTree(nullptr,"none");
    }
    void buildTree(State * parentState,string filterAttributeValue="none"){
        State * childState;
        if(parentState == nullptr){
            root = new State();
            childState = root;
        }
        else
        {
            childState = new State(parentState,filterAttributeValue);
            parentState->children.push_back(childState);
        }
        if(childState->isLeafNode) {
            cout << "leaf node from the buildTree function,wont continue;" << endl << endl;
        }

        //find children only if node is not leaf
        if(!childState->isLeafNode and  childState->data_size>=minSampleSize and childState->forbidden_cols.size() != 9) {
            for (auto it = childState->table_yes_no[childState->bestGainColumn].begin();
                 it != childState->table_yes_no[childState->bestGainColumn].end(); it++) {
                buildTree(childState, it->first);
            }
        }
        if(childState->data_size<minSampleSize) {
            childState->isLeafNode = true;
            cout << " minsamples cutting" <<endl;
        }


    }
    string classifyRow(string current_sample){
        State * current_node = root;
        string test;
        while(!current_node->isLeafNode){
            test = readFromCol(current_node->bestGainColumn,current_sample);
            //                current_node = current_node->children[test];

            for(int i = 0 ; i < current_node->children.size();i++){
                if(current_node->children[i]->attribute_value == test){
                    current_node = current_node->children[i];
                    break;
                }

            }
        }
        string dominant = current_node->dominant;
        while(dominant == "none"){
            current_node = current_node->previous_state;
            string dominant = current_node->dominant;
        }
        return dominant;
    }
    double calculate_precision(){
        double right = 0;
        string current_sample;
        int samples = kfold_vector[test_set].size();
        for(int i = 0 ; i < samples;i++){
            cout << "i : " << i << " row : " << kfold_vector[test_set][i] << endl;
        }
        for(int i = 0 ; i < samples;i++){
            cout << i << endl;
            current_sample = kfold_vector[test_set][i];
            string realResult = readLabel(current_sample);
            string predicted = classifyRow(current_sample);
            right += (realResult==predicted);
        }
        return (double)right/samples;
    }
    ~PostID3(){
        delete root;
    }
};
class PreID3{
public:
    State * root;
    int test_set;
    PreID3(int test_set_index){
        this->test_set = test_set_index;
        this->buildTree(nullptr,"none");
    }
    void buildTree(State * parentState,string filterAttributeValue="none"){
        State * childState;
        if(parentState == nullptr){
            root = new State();
            childState = root;
        }
        else
        {
            childState = new State(parentState,filterAttributeValue);
            parentState->children.push_back(childState);
        }
        if(childState->isLeafNode) {
            cout << "leaf node from the buildTree function,wont continue;" << endl << endl;
        }

        //find children only if node is not leaf
        if(!childState->isLeafNode and  childState->data_size>=minSampleSize and childState->forbidden_cols.size() != 9) {
            for (auto it = childState->table_yes_no[childState->bestGainColumn].begin();
                 it != childState->table_yes_no[childState->bestGainColumn].end(); it++) {
                buildTree(childState, it->first);
            }
        }
        if(childState->data_size<minSampleSize) {
            childState->isLeafNode = true;
            cout << " minsamples cutting" <<endl;
        }


    }
    string classifyRow(string current_sample){
        State * current_node = root;
        string test;
        while(!current_node->isLeafNode){
            test = readFromCol(current_node->bestGainColumn,current_sample);
            //                current_node = current_node->children[test];

            for(int i = 0 ; i < current_node->children.size();i++){
                if(current_node->children[i]->attribute_value == test){
                    current_node = current_node->children[i];
                    break;
                }

            }
        }
        string dominant = current_node->dominant;
        while(dominant == "none"){
            current_node = current_node->previous_state;
            string dominant = current_node->dominant;
        }
        return dominant;
    }
    double calculate_precision(){
        double right = 0;
        string current_sample;
        int samples = kfold_vector[test_set].size();
        for(int i = 0 ; i < samples;i++){
            cout << "i : " << i << " row : " << kfold_vector[test_set][i] << endl;
        }
        for(int i = 0 ; i < samples;i++){
            cout << i << endl;
            current_sample = kfold_vector[test_set][i];
            string realResult = readLabel(current_sample);
            string predicted = classifyRow(current_sample);
            right += (realResult==predicted);
        }
        return (double)right/samples;
    }
    ~PreID3(){
        delete root;
    }


};
int main(){
    string filename = "/Users/robertborisov/UNI/IS/homeworks/CLionHomeworks/id3/breast-cancer.data";
    readFile(filename);
    arrange_kfold_vector(5);
//    for(int i = 0 ;i < kfold_vector[0].size();i++){
//        cout << kfold_vector[0][i] << endl;
//    }
//    return 0;
    vector<double> precision_results;
    int chosen = -1;
    for(int i = 0 ; i <5;i++){
        concatCurrentFold(i);
        PreID3 tree = PreID3(i);


        precision_results.push_back(tree.calculate_precision());

    }
    double total = 0;
    for(int  i = 0 ; i < precision_results.size();i++){
        total+=precision_results[i];
        cout << "Test :" << i << endl;
        cout << precision_results[i] << endl;
    }
    cout << (double)total/5;
    return 0;
}