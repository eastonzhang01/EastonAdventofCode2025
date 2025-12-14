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

unsigned long long get_column_number(vector<string>& lines, unsigned i){
    string number_string = "";
    for(unsigned j=0; j<lines.size()-1; j++){
        number_string += lines[j][i];
    }
    return stoull(number_string);
}

int main() {
    ifstream inputFile("puzzle_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }
    string line;

    // put each line into a vector of lines
    vector<string> lines;
    while( getline(inputFile, line)){
        lines.push_back(line);
    }

    unsigned long long total = 0;
    vector<unsigned long long> numbers;
    for(int i=line.size()-1; i>=0; --i){
        cout<<"***Processing column: "<<i<<endl;
        unsigned long long column_number = get_column_number(lines, i);
        cout<<"Got column number: "<<column_number<<endl;
        numbers.push_back(column_number);
        if(line[i]!= ' '){
            cout<<"Found non-whitespace"<<endl;
            unsigned long long current_num = 1;
            if(line[i]=='+'){
                for(unsigned k=0; k<numbers.size(); ++k){
                    current_num+=numbers[k];
                }
                current_num--;
            }
            else{
                for(unsigned k=0; k<numbers.size(); ++k){
                    current_num*=numbers[k];
                }
            }
            cout<<"Found column group total = "<<current_num<<endl;
            // clean up for next batch of numbers
            --i;
            numbers.clear();
            total+=current_num;
        }
    }


    cout<<total<<endl;
    return 0;
}