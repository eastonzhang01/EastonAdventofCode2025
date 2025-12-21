#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include <set>
#include <sstream>
#include <cmath>

using namespace std;

struct DistancePair{
    long long distance;
    int coordinate1_pos;
    int coordinate2_pos;

    bool operator>(const DistancePair& other) const {
        return distance > other.distance;
    }
};

 long long calc_distance(int x1, int y1, int z1, int x2, int y2, int z2){
    long long dx = (long long)x1-x2;
    long long dy = (long long)y1-y2;
    long long dz = (long long)z1-z2;
    return dx*dx + dy*dy + dz*dz;
}

void print_coordinates(vector<vector<int>>& coordinates){
    for(size_t i=0; i<coordinates.size(); ++i){
            cout<<coordinates[i][0]<<", "<<coordinates[i][1]<<", "<<coordinates[i][2]<<endl;
        }
}

void print_circuits(vector<int>& circuits){
    cout<<"Current circuits list: [";
    for(size_t i=0; i<circuits.size(); ++i){
        cout<<circuits[i]<<", ";
    }
    cout<<"]"<<endl;
}

void print_circuits_map(map<int, vector<int>>& circuit_to_coordinates){
    for(const auto& [key, value]: circuit_to_coordinates){
        cout<<"Circuit key: "<<key;
        cout<<" has positions under it: [";
        for(size_t i=0; i<value.size(); ++i){
            cout<<value[i]<<", ";
        }
        cout<<"]"<<endl;
    }
}

int main() {
    ifstream inputFile("puzzle_input.txt");

    string line;

    vector<vector<int>> coordinates;

    while(getline(inputFile, line)){
        stringstream ss(line);
        vector<int> current_coordinate;
        string part;
        while(getline(ss, part, ',')){
            current_coordinate.push_back(stoi(part));
        }
        coordinates.push_back(current_coordinate);
    }
    
    priority_queue<DistancePair, vector<DistancePair>, greater<DistancePair>> distance_q;

    for(int i=0; i<coordinates.size()-1; ++i){
        for(int j=i+1; j<coordinates.size(); ++j){
             long long distance = calc_distance(coordinates[i][0], coordinates[i][1], coordinates[i][2], coordinates[j][0], coordinates[j][1], coordinates[j][2]);
            distance_q.push({distance, i, j});
        }
    }

    //cout<<distance_q.size()<<endl;
    int num_connections = 1000;

    vector<int> circuits = vector<int>(coordinates.size(), -1);
    map<int, vector<int>> circuit_to_coordinates; 
    int next_circuit_id = 0; 
    for(int i=0; i<num_connections; ++i){
        DistancePair curr_pair = distance_q.top();
        int first_pos = curr_pair.coordinate1_pos;
        int second_pos = curr_pair.coordinate2_pos;
        //cout<<"position 1: "<<first_pos<<" position 2: "<<second_pos<<endl;
        
        // neither in a circuit
        if(circuits[first_pos] == -1 && circuits[second_pos] == -1){
            //cout<<"--Neither in a circuit."<<endl;
            circuits[first_pos] = next_circuit_id;
            circuits[second_pos] = next_circuit_id;
            circuit_to_coordinates[next_circuit_id] = {first_pos, second_pos};
            next_circuit_id++;
        }
        // coorindate 1 is in a circuit
        else if(circuits[first_pos]!=-1 && circuits[second_pos] == -1){
            //cout<<"--position 1 in a circuit."<<endl;
            circuits[second_pos] = circuits[first_pos];
            circuit_to_coordinates[circuits[first_pos]].push_back(second_pos);
        }
        // coordinate 2 is in a circuit
        else if(circuits[first_pos]==-1 && circuits[second_pos] != -1){
            //cout<<"--position 2 in a circuit."<<endl;
            circuits[first_pos] = circuits[second_pos];
            circuit_to_coordinates[circuits[second_pos]].push_back(first_pos);
        }
        // both coordinates are in different circuit
        else if(circuits[first_pos] != circuits[second_pos]){
            int circuit1_key = circuits[first_pos];
            int circuit2_key = circuits[second_pos];
            
            // Print BEFORE merge
            cout << "BEFORE merge: circuit1=" << circuit1_key << " (size=" << circuit_to_coordinates[circuit1_key].size() 
                << ") with circuit2=" << circuit2_key << " (size=" << circuit_to_coordinates[circuit2_key].size() << ")" << endl;
            
            vector<int> circuit2_followers = circuit_to_coordinates[circuit2_key];

            circuit_to_coordinates[circuit1_key].insert(circuit_to_coordinates[circuit1_key].end(), circuit2_followers.begin(), circuit2_followers.end());
            
            for(int j=0; j<circuit2_followers.size(); ++j){
                circuits[circuit2_followers[j]] = circuit1_key;
            }
            //circuits[second_pos] = circuit1_key;

            circuit_to_coordinates.erase(circuit2_key);
            
            // Print AFTER merge
            cout << "AFTER merge: circuit1=" << circuit1_key << " now has size=" << circuit_to_coordinates[circuit1_key].size() << endl;
            cout << "Erased circuit " << circuit2_key << endl << endl;
        }
        else if(circuits[first_pos] == circuits[second_pos] && circuits[first_pos]!=-1){
            //cout<<"--none of conditions hit"<<endl;
        }
        //print_circuits(circuits);
        //print_circuits_map(circuit_to_coordinates);

        distance_q.pop();
    }

    int first=1;
    int second=1;
    int third=1;

    vector<int> circuit_counts;
    for(const auto& [key, value]: circuit_to_coordinates){
        int num_coordinates = value.size();
        circuit_counts.push_back(num_coordinates);
    }
    cout << "Final circuit_to_coordinates map:" << endl;
    print_circuits_map(circuit_to_coordinates);
    cout << "Number of circuits: " << circuit_counts.size() << endl;
    cout << "All circuit sizes: ";
    for(int size : circuit_counts) {
        cout << size << " ";
    }
    cout << endl;
    sort(circuit_counts.begin(), circuit_counts.end(), std::greater<>());

    first = circuit_counts[0];
    second=circuit_counts[1];
    third=circuit_counts[2];

    cout<<first<<", "<<second<<", "<<third<<endl;
    
    unsigned long long total = 1ULL * first * second * third;
    cout<<total<<endl;

    return 0;
}