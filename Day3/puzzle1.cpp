#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("puzzle_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }

    string line;
    long totalJoltage =0;
    while(getline(inputFile, line)){
        char firstDigit = line[0];
        char secondDigit= line[1];

        for(size_t i=1; i<line.size(); ++i){
            if(line[i]>firstDigit && (i+1)!=line.size()){
                firstDigit = line[i];
                secondDigit = line[i+1];
            }
            else if(line[i]>secondDigit){
                secondDigit = line[i];
            }
        }

        string joltage = "";
        joltage+=firstDigit;
        joltage+=secondDigit;

        int joltage_num=stoi(joltage);
        cout<<line<<" has max joltage of "<<joltage_num<<endl;
        totalJoltage+=joltage_num;
    }

    cout<<totalJoltage<<endl;
    return 0;
}