#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
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
pair<double,double> * coordinates_array;
//queue<string> townNames;
//for 100 40000 and 16 doesnt work

const int pop_stop = 1000;
double best_distance = INT_MAX;
int global_counter =0;
int n;
int chosenPopulation = 1;
double current_best = -1;
double previous_best = -1;
int consecutive_best_chromosome_counter = 0 ;
string * towns;
const int fixed_population_size = 800;
void generateTownNames(){
    std::ifstream townNamesFile ("/Users/robertborisov/uni/is/homeworks/CLionHomeworks/tsp/UK_TSP/uk12_name.csv");
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
double calculateDistance(double x1,double y1,double x2,double y2){
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
//        cout << firstGene << " " << secondGene << endl;
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
    coordinates_array = new pair<double,double>[n];
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
//    time_t x = time(0);
    int split  = rand() % (n-2) + 1;
//    cout << "split : " << split << endl;
    crossover(parent1.genes,parent2.genes,split);
    crossover(parent2.genes,parent1.genes,split);
}
void generateTownsFromCV(int n){
    coordinates_array = new pair<double,double>[n];
    std::ifstream townsXYcsv ("/Users/robertborisov/uni/is/homeworks/CLionHomeworks/tsp/UK_TSP/uk12_xy.csv");
    string line = "";
    int counter = 0;
    string temp;
    while(townsXYcsv and getline(townsXYcsv,line)){
        stringstream x_y(line);
        temp = "";
        getline(x_y,temp,',');
        coordinates_array[counter].first = atof(temp.c_str());
        getline(x_y,temp);
        coordinates_array[counter].second = atof(temp.c_str());
        counter++;

    }
//    for(int i = 0 ; i < n;++i){
//        cout << i  << "i"<<"x : " <<coordinates_array[i].first << " y : " << coordinates_array[i].second << endl;
//    }
//    return;
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
    int inner = 1;



    while(isNotTerminated()){
//        cout << "t" << t<<endl;
             if(t == 1 || t == 10 || t== 15 || t == 20 || t == 30 || t == 40 || t == 300 || t == 500 || t == 700 || t == 1001) {
//        for(int i = 0; i < n;i++){
//            cout << population.top().genes[i] << " ";
//        }
//        cout << endl;
                 cout << inner <<" : "<<population.top().totalDistance << endl;
                 inner++;
             }
             if(t == 2999){
                 int a = 5;



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

int main() {
    srand(time(nullptr));
    cin >> n;
    generateTownNames();
    generateTownsFromCV(n);
    std::clock_t start = std::clock();
    tsp();
    vector<int> bestGenes = population.top().genes;


    std::clock_t end = std::clock();
    double elapsedSeconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << elapsedSeconds << " seconds" << std::endl;



    cout << "------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "pathFound x's: " << endl;
    for(int i = 0 ; i < n;i++){
        cout << towns[bestGenes[i]] << endl;
    }
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << endl;


//    cout << checkMinDistaneLine();
    delete[] towns;

}




//distance: 857
//x : 807     y : 1
//x : 249     y : 1
//x : 73     y : 1
//x : 658     y : 1
//x : 930     y : 1


