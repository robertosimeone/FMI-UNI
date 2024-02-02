#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <limits.h>
#include <cmath>
using namespace  std;
const int max_counter = 800 ;
void readFile(string filename,vector<pair<double,double>>&x_y,char separator){
    std::ifstream townsXYcsv (filename);
    string line = "";
    int counter = 0;
    string temp;
    double x,y;
    while(townsXYcsv and getline(townsXYcsv,line)){
        stringstream x_y_coordinates(line);
        temp = "";
        getline(x_y_coordinates, temp, separator);
        x = atof(temp.c_str());
        getline(x_y_coordinates, temp);
        y = atof(temp.c_str());
        x_y.push_back(make_pair(x,y));


    }
}
//kMeans function that returns the pair
//first element of pair is clusterization vector
//second element of pair is C - within point scatter
vector<pair<double,double>> initialize_centroids(vector<pair<double,double>>&x_y,int k){
    set<int> usedPoints;
    vector<pair<double,double>>clusters;
    int size = x_y.size();
    int current;
    for(int i = 0 ; i < k ;i ++){
        do {
            current = rand() % size;
        }while(usedPoints.find(current) != usedPoints.end());
        usedPoints.emplace(current);
        clusters.push_back(make_pair(x_y[current].first,x_y[current].second));
    }
        return clusters;

}
vector<pair<double,double>> kMeans_plus_plus_initialization(vector<pair<double,double>>&x_y,int k){
    set<int> usedPoints;
    vector<pair<double,double>>clusters;
    int size = x_y.size();
    int current;
    //add first random point to clusters
    current = rand() % size;
    clusters.push_back(make_pair(x_y[current].first,x_y[current].second));
    long double * distances;
    long double currentDistance;
    for(int i = 0 ; i < k-1 ; i++){
        distances = new long double[size];
        for(int j = 0; j < size;j++){
            long double currentMin;
            for(int t = 0 ; t < clusters.size();t++){
                currentDistance = sqrt(pow(clusters[t].first-x_y[j].first,2)
                                       +pow(clusters[t].second-x_y[j].second,2));
                if(t == 0) {
                    currentMin = currentDistance;
                    continue;
                }
                currentMin = min(currentMin,currentDistance);

            }
            distances[j] = currentMin;
        }
        int index = 0;
        long double currentMaxDistance = distances[0];
        for(int s = 0 ; s < size;s++){
            if(currentMaxDistance < distances[s]){
                currentMaxDistance = distances[s];
                index = s;
            }
        }
        clusters.push_back(make_pair(x_y[index].first,x_y[index].second));
        delete [] distances;
    }

    ofstream file("/Users/robertborisov/uni/is/homeworks/CLionHomeworks/kMeans/centroids.csv");
    file << "centroid_x,centroid_y" << endl;
    for(int i = 0 ; i < clusters.size();i++){
        file << clusters[i].first<<','<<clusters[i].second << endl;
    }
    return clusters;

}
pair<vector<int>,long double> kMeans(int k,vector<pair<double,double>>&x_y){
    int current_counter = 0;
    vector<int> clusterNames(k);
    for(int i = 0 ; i < k;++i){
        clusterNames.push_back(i);
    }
    int numPoints = x_y.size();

    vector<int> labels(numPoints);
    vector<int> previous_labels(numPoints);
    vector<pair<double,double>> centroids = initialize_centroids(x_y,k);
    int *numberOfPointsInCentroid;
    long double minDistance;
    long double current_distance;
    int cluster;
    while(true){
        numberOfPointsInCentroid = new int[k]{0};
        //assign each point to the closest cluster
        for(int i  =  0 ; i < numPoints;i++){
//            minDistance = INT_MAX;
               for(int j = 0 ; j < k;++j){
                   current_distance = sqrt(pow(centroids[j].first-x_y[i].first,2)
                           +pow(centroids[j].second-x_y[i].second,2));
                   if(j == 0){
                       minDistance = current_distance;
                       cluster = j;
                       continue;
                   }
                   if(current_distance < minDistance){
                       minDistance = current_distance;
                       cluster = j;
                   }
               }
               labels[i] = cluster;
               numberOfPointsInCentroid[cluster]++;
        }
        if(previous_labels == labels){
            break;
        }
        previous_labels = labels;
        //calculate new centroids
        vector<pair<double,double>> updatedCentroids;
        updatedCentroids.resize(k, make_pair(0,0));
        for(int i = 0 ; i < numPoints;i++){
            updatedCentroids[labels[i]].first+=(double)(1.0/numberOfPointsInCentroid[labels[i]])*x_y[i].first;
            updatedCentroids[labels[i]].second+=(double)(1.0/numberOfPointsInCentroid[labels[i]])*x_y[i].second;
        }
        centroids = updatedCentroids;

//    if(current_counter > max_counter){
//        break;
//    }
//    current_counter++;
        delete [] numberOfPointsInCentroid;
    }
//    cout <<"------------------------------------------------------------------------------------------------------" << endl;
//    for(int i = 0 ; i < centroids.size();i++){
//        cout <<i<<" centroid : "<<"x :"<< centroids[i].first << "  y:" << centroids[i].second << endl;
//        cout << "number of points in centroid: " << numberOfPointsInCentroid[i] << endl;
//    }
//    cout <<"------------------------------------------------------------------------------------------------------" << endl;
    vector<double> withinPointScatterForEachCluster(k,0);
    for(int i = 0 ; i < numPoints;i++){
        withinPointScatterForEachCluster[labels[i]] += pow(x_y[i].first - centroids[labels[i]].first,2)
                                                       +pow(x_y[i].second - centroids[labels[i]].second,2);
    }
    long double C = 0;
    for(int i = 0; i < withinPointScatterForEachCluster.size();i++){
            C+=numberOfPointsInCentroid[i]*withinPointScatterForEachCluster[i];
    }
    delete [] numberOfPointsInCentroid;
    return make_pair(labels,C);

}
pair<vector<int>,long double> kMeans_plus_plus(int k,vector<pair<double,double>>&x_y){
    int current_counter = 0;
    vector<int> clusterNames(k);
    for(int i = 0 ; i < k;++i){
        clusterNames.push_back(i);
    }
    int numPoints = x_y.size();

    vector<int> labels(numPoints);
    vector<int> previous_labels(numPoints);
    vector<pair<double,double>> centroids = kMeans_plus_plus_initialization(x_y,k);
//    for(int i = 0 ; i < centroids.size();i++){
//        cout << "centroid id : " << i << " x :" << centroids[i].first << " y : " << centroids[i].second << endl;
//    }
    int *numberOfPointsInCentroid;
    long double minDistance;
    long double current_distance;
    int cluster;
    while(true){
        numberOfPointsInCentroid = new int[k]{0};
        //assign each point to the closest cluster
        for(int i  =  0 ; i < numPoints;i++){
//            minDistance = INT_MAX;
            for(int j = 0 ; j < k;++j){
                current_distance = sqrt(pow(centroids[j].first-x_y[i].first,2)
                                        +pow(centroids[j].second-x_y[i].second,2));
                if(j == 0){
                    minDistance = current_distance;
                    cluster = j;
                    continue;
                }
                if(current_distance < minDistance){
                    minDistance = current_distance;
                    cluster = j;
                }
            }
            labels[i] = cluster;
            numberOfPointsInCentroid[cluster]++;
        }
        if(previous_labels == labels){
            break;
        }
        previous_labels = labels;
        //calculate new centroids
        vector<pair<double,double>> updatedCentroids;
        updatedCentroids.resize(k, make_pair(0,0));
        for(int i = 0 ; i < numPoints;i++){
            updatedCentroids[labels[i]].first+=(double)(1.0/numberOfPointsInCentroid[labels[i]])*x_y[i].first;
            updatedCentroids[labels[i]].second+=(double)(1.0/numberOfPointsInCentroid[labels[i]])*x_y[i].second;
        }
        centroids = updatedCentroids;

//    if(current_counter > max_counter){
//        break;
//    }
//    current_counter++;
        delete [] numberOfPointsInCentroid;
    }
//    cout <<"------------------------------------------------------------------------------------------------------" << endl;
//    for(int i = 0 ; i < centroids.size();i++){
//        cout <<i<<" centroid : "<<"x :"<< centroids[i].first << "  y:" << centroids[i].second << endl;
//        cout << "number of points in centroid: " << numberOfPointsInCentroid[i] << endl;
//    }
//    cout <<"------------------------------------------------------------------------------------------------------" << endl;
    vector<double> withinPointScatterForEachCluster(k,0);
    for(int i = 0 ; i < numPoints;i++){
        withinPointScatterForEachCluster[labels[i]] += pow(x_y[i].first - centroids[labels[i]].first,2)
                                                       +pow(x_y[i].second - centroids[labels[i]].second,2);
    }
    long double C = 0;
    for(int i = 0; i < withinPointScatterForEachCluster.size();i++){
        C+=numberOfPointsInCentroid[i]*withinPointScatterForEachCluster[i];
    }
    delete [] numberOfPointsInCentroid;
    return make_pair(labels,C);

}
int findBestK(int from,int to,vector<pair<double,double>>&x_y){
    int counter = 0;
    vector<long double> results(to-from+1,0);
    for(int i = from ; i <= to;i++){
        results[counter++] = kMeans(i,x_y).second;
    }
//    cout << "----------------------------------------------------------------------------------------------------"<<endl;
//    for(int i = 0 ; i <= results.size();i++){
//        cout << i << "  :" << results[i]<<endl;
//    }
//    cout << "----------------------------------------------------------------------------------------------------"<<endl;
    long double bestDifference = results[0]-results[1];
    long double currentDifference;
    int index = -1;
    for(int i = 0 ; i < results.size()-1;i++){
        currentDifference = results[i]-results[i+1];
        if(currentDifference>=bestDifference){
            bestDifference = currentDifference;
            index = i+1;
        }
    }
    return from+index;

}
int findBestKWithKmeans_plus_plus(int from,int to,vector<pair<double,double>>&x_y){
    int counter = 0;
    vector<long double> results(to-from+1,0);
    for(int i = from ; i <= to;i++){
        results[counter++] = kMeans_plus_plus(i,x_y).second;
    }
//    cout << "----------------------------------------------------------------------------------------------------"<<endl;
//    for(int i = 0 ; i <= results.size();i++){
//        cout << i << "  :" << results[i]<<endl;
//    }
//    cout << "----------------------------------------------------------------------------------------------------"<<endl;
    long double bestDifference = results[0]-results[1];
    long double currentDifference;
    int index = -1;
    for(int i = 0 ; i < results.size()-1;i++){
        currentDifference = results[i]-results[i+1];
        if(currentDifference>=bestDifference){
            bestDifference = currentDifference;
            index = i+1;
        }
    }
    return from+index;

}
vector<int> randomRestart(int k,int times,vector<pair<double,double>>&x_y){
    pair<vector<int>,double long > minClusterResult;
    pair<vector<int>,double long> currentClusterResult;
    minClusterResult.second = INT_MAX;
    for(int i = 0; i < times;i++){
        currentClusterResult = kMeans(k,x_y);
//        cout << "current--cluster-result-from-kMeans " <<  currentClusterResult.second << endl;
        if(i==0){
            minClusterResult = currentClusterResult;
        }
        if(currentClusterResult.second < minClusterResult.second){
            minClusterResult = currentClusterResult;
//            cout << "current-max-cluster-result " << minClusterResult.second << endl;
        }

    }
//    cout << "final-max-cluster-result " << minClusterResult.second << endl;
    return minClusterResult.first;
}
vector<int> randomRestartKmeans_plus_plus(int k,int times,vector<pair<double,double>>&x_y){
    pair<vector<int>,double long > minClusterResult;
    pair<vector<int>,double long> currentClusterResult;
    minClusterResult.second = INT_MAX;
    for(int i = 0; i < times;i++){
        currentClusterResult = kMeans_plus_plus(k,x_y);
//        cout << "current--cluster-result-from-kMeans " <<  currentClusterResult.second << endl;
        if(i==0){
            minClusterResult = currentClusterResult;
        }
        if(currentClusterResult.second < minClusterResult.second){
            minClusterResult = currentClusterResult;
//            cout << "current-max-cluster-result " << minClusterResult.second << endl;
        }

    }
//    cout << "final-max-cluster-result " << minClusterResult.second << endl;
    return minClusterResult.first;
}
void solveNormal(vector<pair<double,double>>&x_y){
    ofstream file("/Users/robertborisov/uni/is/homeworks/CLionHomeworks/kMeans/normal.csv");
    int k = findBestK(2,10,x_y);
    vector<int> labels = randomRestart(k,10,x_y);
    if(file){
        file << "cluster" << endl;
    }
    for(int i =0 ; i < labels.size();i++){
        if(file.is_open()){
            file << labels[i] << endl;
        }
    }
    file.close();

}
void solveNormalKMeans_plus_plus(vector<pair<double,double>>&x_y){
    ofstream file("/Users/robertborisov/uni/is/homeworks/CLionHomeworks/kMeans/normal_plus_plus.csv");
    int k = findBestKWithKmeans_plus_plus(2,10,x_y);
    vector<int> labels = randomRestartKmeans_plus_plus(k,10,x_y);
    if(file){
        file << "cluster" << endl;
    }
    for(int i =0 ; i < labels.size();i++){
        if(file.is_open()){
            file << labels[i] << endl;
        }
    }
    file.close();

}
void solveUnbalanced(int k,vector<pair<double,double>>&x_y){
    ofstream file("/Users/robertborisov/uni/is/homeworks/CLionHomeworks/kMeans/unbalance.csv");
//    int z = findBestK(8,10,x_y);
    vector<int> labels = randomRestart(k,500,x_y);
    if(file){
        file << "cluster" << endl;
    }
    for(int i =0 ; i < labels.size();i++){
        if(file.is_open()){
            file << labels[i] << endl;
        }
    }
    file.close();
}
void solveUnbalancedWithKMeans_plus_plus(int k,vector<pair<double,double>>&x_y){
//    cout << "------------------------------------------------------------------------------------------------------------" << endl;
//    cout << "unbalanced solving" << endl;
    ofstream file("/Users/robertborisov/uni/is/homeworks/CLionHomeworks/kMeans/unbalance_plus_plus.csv");
//    int z = findBestK(8,10,x_y);
    vector<int> labels = randomRestartKmeans_plus_plus(k,1000,x_y);
    if(file){
        file << "cluster" << endl;
    }
    for(int i =0 ; i < labels.size();i++){
        if(file.is_open()){
            file << labels[i] << endl;
        }
    }
    file.close();
}

int main(){
    srand(time(nullptr));
    string normal = "/Users/robertborisov/uni/is/homeworks/CLionHomeworks/kMeans/normal/normal.txt";
    string unabalance = "/Users/robertborisov/uni/is/homeworks/CLionHomeworks/kMeans/unbalance/unbalance.txt";
    vector<pair<double,double>> x_y_normal;
    vector<pair<double,double>> x_y_unbalance;
    std::clock_t start = std::clock();
    readFile(normal,x_y_normal,'\t');
//    for(int i = 0 ; i < 20;i++){
//        cout << "id : " << i << " x :  " << x_y_normal[i].first << " y: " <<x_y_normal[i].second << endl;
//    }
//    cout << "------------------------------------------------------------"<<endl;
    readFile(unabalance,x_y_unbalance,' ');
//    for(int i = 0 ; i < 20;i++){
//        cout << "id : " << i << " x :  " << x_y_unbalance[i].first << " y: " <<x_y_unbalance[i].second << endl;
//    }
//    return 0;

    solveNormal(x_y_normal);
    solveNormalKMeans_plus_plus(x_y_normal);

    solveUnbalanced(8,x_y_unbalance);
    solveUnbalancedWithKMeans_plus_plus(8,x_y_unbalance);

    std::clock_t end = std::clock();
    double elapsedSeconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << elapsedSeconds << " seconds" << std::endl;


    return 0;
}