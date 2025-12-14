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

using namespace std;

void print_matrix(vector<vector<string>>& matrix){
    for(int i =0; i<matrix.size(); ++i){
        for(int j=0; j<matrix[i].size(); ++j){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main() {
    ifstream inputFile("test_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }
    string line;
    vector<vector<string>> matrix;
    while( getline(inputFile, line)){
        vector<string> current_line = vector<string>();
        stringstream ss(line);
        string word;
        while(ss>>word){
            current_line.push_back(word);
        }
        matrix.push_back(current_line);
    }
    print_matrix(matrix);

    unsigned long long total = 0;;

    vector<string> operation = matrix[matrix.size()-1];

    // i is each column, j is each row
    for(unsigned i=0; i<operation.size(); ++i){
        unsigned long long current_total = stoull(matrix[0][i]);
        for(unsigned j=1; j<matrix.size()-1; ++j){
            if(operation[i]=="+"){
                current_total+=stoull(matrix[j][i]);
            }
            else{
                current_total*=stoull(matrix[j][i]);
            }
        }
        cout<<current_total<<endl;
        total+=current_total;
    }
    cout<<total<<endl;
    return 0;
}