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

void print_lines(vector<string>& lines){
    for(unsigned i=0; i<lines.size(); ++i){
        cout<<lines[i]<<endl;
    }
}

// i is row and j is col
long long calculate_possibilities(vector<string>& lines, unsigned row, unsigned col, vector<vector<long long>>& cache){

    // value already been calculated
    if(cache[row][col]!=-1){
        return cache[row][col];
    }
    long long possibilities = 0;
    // check if left is a carrot
    if(col > 0 && lines[row][col-1]=='^'){
        //cout<<"Going to position: "<<row-1<<", "<<col-1<<endl;
        possibilities += calculate_possibilities(lines, row-1, col-1, cache);
    }
    // check if right is a carrot
    if(col < lines.back().size()-1 && lines[row][col+1]=='^'){
        //cout<<"Going to position: "<<row-1<<", "<<col+1<<endl;
        possibilities += calculate_possibilities(lines, row-1, col+1, cache);
    }
    // check if above has line
    if(lines[row-1][col]=='|'){
        //cout<<"Going to position: "<<row-1<<", "<<col<<endl;
        possibilities += calculate_possibilities(lines, row-1, col, cache);
    }
    // base case
    if(lines[row-1][col] == 'S'){
        possibilities+=1;
    }
    cache[row][col] = possibilities;
    return possibilities;
}

int main() {
    ifstream inputFile("puzzle_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }
    string line;

    vector<string> file_lines;
    vector<vector<long long>> cache_possibilites;
    while( getline(inputFile, line)){
        file_lines.push_back(line);
    }

    // we can ignore the last line
    for(unsigned i=0; i<file_lines.size()-1; ++i){
        //cout<<"Processing line: "<<i<<endl;
        for(unsigned j=0; j<file_lines[i].size(); ++j){
            if(file_lines[i][j]=='|' && file_lines[i+1][j]=='^'){
                file_lines[i+1][j-1] = '|';
                file_lines[i+1][j+1] = '|';
            }
            else if(file_lines[i][j]=='|' && file_lines[i+1][j]=='.'){
                file_lines[i+1][j] = '|';
            }
            // Found an S to start move line down
            else if(file_lines[i][j]=='S'){
                file_lines[i+1][j] = '|';
            }
        }
    }
    print_lines(file_lines);

    for(unsigned i=0; i<file_lines.size(); ++i){
        cache_possibilites.push_back(vector<long long>(file_lines[i].size(), -1));
    }

    long long all_possibilities = 0;
    for(unsigned j=0; j<file_lines.back().size(); ++j){
        if(file_lines.back()[j]=='|'){
            cout<<"Processing position: "<<file_lines.size()-1<<", "<<j<<" with value "<<file_lines[file_lines.size()-1][j]<<endl;
            long long local_poss = calculate_possibilities(file_lines, file_lines.size()-1, j, cache_possibilites);
            cout<<"Got Local Possibilites of: "<<local_poss<<endl;
            all_possibilities += local_poss;
        }
    }

    cout<<all_possibilities<<endl;

    return 0;
}