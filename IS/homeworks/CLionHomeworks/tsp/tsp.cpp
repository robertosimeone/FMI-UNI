#include <iostream>
#include <stdlib.h>
#include <string>
//1 point/2 point + cycle crossover
#include <tuple>
#include <map>
#include <queue>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <set>
#include <queue>
using namespace  std;
pair<int,int> * coordinates_array;
//queue<string> townNames;
//for 100 40000 and 16 doesnt work

const int pop_stop = 30000;
double best_distance = INT_MAX;
int global_counter =0;
int n;
int chosenPopulation = 1;
double current_best = -1;
double previous_best = -1;
int consecutive_best_chromosome_counter = 0 ;
string * towns;
const int fixed_population_size = 100;
const int  goal_distance = 857;
void generateTownNames(){
    std::ifstream townNamesFile ("/Users/robertborisov/uni/is/homeworks/CLionHomeworks/tsp/cities.txt");
    string currentName;
    int counter = 0;
    if(townNamesFile.is_open()){
        towns = new string[n];
        while(townNamesFile and counter <n){
            townNamesFile>>towns[counter];
            counter++;
        }
    }
}
//class Town{
//public:
//    string name;
//    int x;
//    int y;
//    int number;
//    Town() = default;
//    Town(string name,int x, int y){
//        this->name = name;
//        this->x = x;
//        this->y = y;
//    }
//    double calculateDistanceTo(const Town &b){
//        return sqrt(pow(x-b.x,2)+pow(y-b.y,2));
//    }
//    ~Town() = default;
//};
double calculateDistance(int x1,int y1,int x2,int y2){
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}
class Chromosome{
    public:
    int size;
    vector<int>  genes;
    double totalDistance;


    Chromosome(){
        size  = n;
        genes.resize(size);
        for(int i = 0 ; i < size;i++){
            genes[i] = i;
        }
        random_shuffle(genes.begin(),genes.end());
        totalDistance = 0;
        this->calculateTotalDistance();

    }
    Chromosome(vector<int>&genes){
        totalDistance = 0;
        size = n;
        this->genes.resize(size,-1);
//        for(int i = 0 ; i<size;i++){
//            this->genes[i] = genes[i];
//        }
//        crossover(genes1,genes2);
        this->genes = genes;
        mutate();
        calculateTotalDistance();

    }
    Chromosome(const Chromosome & other){
        this->totalDistance = other.totalDistance;
        this->size = other.size;
        this->genes.resize(this->size);
        for(int i = 0 ; i < this->size;++i){
            genes[i] = other.genes[i];
        }
    }

    void mutate(){
        int firstGene = rand() % size;
        int secondGene = rand() % size;
        swap(genes[firstGene],genes[secondGene]);
    }
    void calculateTotalDistance(){
//        if(genes[0] == 2 and genes[1] == 1 and genes[2] == 3 and genes[3] == 0 and genes[4] == 4){
//            int x = 2;
//        }
        for(int i = 0 ; i < n-1;++i){
             this->totalDistance+=calculateDistance(coordinates_array[genes[i]].first,coordinates_array[genes[i]].second,
                               coordinates_array[genes[i+1]].first,coordinates_array[genes[i+1]].second);
        }

    }
    bool operator<( Chromosome & other){
        return 1/this->totalDistance < 1/other.totalDistance;
    }
    bool operator<=( Chromosome & other){
        return 1/this->totalDistance <= 1/other.totalDistance;
    }
    bool operator>( Chromosome & other){
        return other < *this;
    }
    bool operator>=( Chromosome & other){
        return other <= *this;
    }
//    Chromosome(){
//
//    }
    ~Chromosome() = default;
};
void generateTowns(int n){
    coordinates_array = new pair<int,int>[n];
    for(int i = 0 ; i < n;++i){
        coordinates_array[i].first = rand() % 1000;
        coordinates_array[i].second = rand() % 500;
    }
}
priority_queue<Chromosome,vector<Chromosome>,less<> > population;
queue<Chromosome> nextPopulation;
void crossover(vector<int>&genes1,vector<int> & genes2,int split){
    set<int> used_genes;
    vector<int> genes(n);
    for(int i = 0 ; i < split;i++){
        genes[i] = genes1[i];
        used_genes.insert(genes1[i]);
    }
    for(int i = 0;i < n;i++){
        if(used_genes.find(genes2[i])==used_genes.end()){
            genes[split] = genes2[i];
//                used_genes.insert(genes[i]);
            split++;
        }

    }
    nextPopulation.emplace(Chromosome(genes));
}
void reproduce(Chromosome & parent1, Chromosome & parent2){
    int split  = rand() % (n-2) + 1;
    crossover(parent1.genes,parent2.genes,split);
    crossover(parent2.genes,parent1.genes,split);
}
void generateTownsOnStraightLine(int n){
    coordinates_array = new pair<int,int>[n];
    for(int i = 0 ; i < n;++i){
        coordinates_array[i].first = rand() % 1000;
        coordinates_array[i].second = 1;
    }
}
void initializePopulation(){
    for(int i =0;i < fixed_population_size; ++i){
        Chromosome chromo;
        population.emplace(chromo);
    }
}
void printq(){
    while (!population.empty()){
        Chromosome cur = population.top();
        population.pop();
        for(int i = 0 ; i < n;i++){
            cout << cur.genes[i] << " ";
        }
        cout << cur.totalDistance;
        cout << endl;
    }
}
bool isNotTerminated(){
    if(global_counter > pop_stop){
//        printq();
        return false;
        }
//    if(consecutive_best_chromosome_counter >= 100) {
//        return false;
//    }
    return true;

}

void swapQ(){
    while(!population.empty()){
        population.pop();
    }
    while(!nextPopulation.empty()){
        population.emplace(nextPopulation.front());
        nextPopulation.pop();
    }
}
void tsp(){
    int t = 1;
    initializePopulation();



    while(isNotTerminated()){
//        cout << "t" << t<<endl;
             if(t == 1 || t == 1000 || t== 3000 || t == 7000 || t == 10000 || t == 14000 || t == 18000 || t == 22000 || t == 27000 || t == 40001) {
//        for(int i = 0; i < n;i++){
//            cout << population.top().genes[i] << " ";
//        }
//        cout << endl;
                 cout << population.top().totalDistance << endl;
             }

        while(population.size()!=fixed_population_size/2) {
//            cout << "popsize" << population.size()<<endl;
//            cout <<"fixed pop size"<< fixed_population_size/2 << endl;
//            cout << "Im here" << endl;
            Chromosome firstParent = population.top();
            population.pop();
            Chromosome secondParent = population.top();
            population.pop();
            nextPopulation.emplace(firstParent);
            nextPopulation.emplace(secondParent);
            reproduce(firstParent,secondParent);
        }
        swapQ();
        global_counter++;
        current_best = population.top().totalDistance;
        if(current_best==previous_best){
            consecutive_best_chromosome_counter++;
        }
        else{
            consecutive_best_chromosome_counter=0;
        }
        previous_best = current_best;
//        cout << "t : " << t << endl;
        t++;

    }



}
//

void bubbleSort(pair<int,int> * arr, int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].first > arr[j + 1].first) {
                swap(arr[j].first, arr[j + 1].first);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (!swapped)
            break;
    }
}
bool checkMinDistaneLine(){
    double tspDistance = population.top().totalDistance;
    double realDistance = 0;
    bubbleSort(coordinates_array,n);
    for(int i = 0 ; i < n-1;i++){
        realDistance+=calculateDistance(coordinates_array[i].first,coordinates_array[i].second,
                                      coordinates_array[i+1].first,coordinates_array[i+1].second);
    }
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "OrderedPath" << endl;
    cout << "x's : ";
    for(int i = 0 ; i < n;++i){
        cout <<  coordinates_array[i].first << " ";
    }
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << endl;
    cout << realDistance << endl;
    return tspDistance == realDistance;
}


int main() {
    srand((int) time(0));
    cin >> n;
    generateTownsOnStraightLine(n);
    tsp();
    vector<int> bestGenes = population.top().genes;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "pathFound x's: " << endl;
    for(int i = 0 ; i < n;i++){
        cout << coordinates_array[bestGenes[i]].first << " ";
    }
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << endl;

    cout << checkMinDistaneLine();
    delete[] towns;

}




//distance: 857
//x : 807     y : 1
//x : 249     y : 1
//x : 73     y : 1
//x : 658     y : 1
//x : 930     y : 1


