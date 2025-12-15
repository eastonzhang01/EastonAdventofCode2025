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

int main() {
    ifstream inputFile("test_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }
    string line;

    vector<string> file_lines;
    while( getline(inputFile, line)){
        file_lines.push_back(line);
    }

    unsigned long long split_count=0;
    // we can ignore the last line
    for(unsigned i=0; i<file_lines.size()-1; ++i){
        //cout<<"Processing line: "<<i<<endl;
        for(unsigned j=0; j<file_lines[i].size(); ++j){
            // found a line and found a split below the line
            //cout<<"Processing position: "<<i<<", "<<j<<" with value "<<file_lines[i][j]<<endl;
            if(file_lines[i][j]=='S' && file_lines[i+1][j]=='^'){
                split_count++;
                file_lines[i+1][j-1] = 'S';
                file_lines[i+1][j+1] = 'S';
            }
            // Found an S to start move line down
            else if(file_lines[i][j]=='S'){
                file_lines[i+1][j] = 'S';
                //cout<<file_lines[i+1][j]<<endl;
            }
        }
    }
    print_lines(file_lines);

    cout<<split_count<<endl;

    return 0;
}