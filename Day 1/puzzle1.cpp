// Online C++ compiler to run C++ program online
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream inputFile("Day1Input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }

    string line;
    int zeroCount = 0;
    int currentDialNum = 50;

    while(getline(inputFile, line)){
        char rotation = line[0];
        int number = stoi(line.substr(1));
        
        //int fullRotateCount = number/100;
        int remainder = number % 100;
        cout <<line<<" "<<rotation<<" "<<number<<" "<<remainder<<endl;

        if(rotation == 'L'){
            currentDialNum = currentDialNum - remainder;
            if(currentDialNum<0){
                currentDialNum = 100+currentDialNum;
            }
        }
        if(rotation == 'R'){
            currentDialNum = currentDialNum + remainder;
            if(currentDialNum>99){
                currentDialNum = currentDialNum-100;
            }
        }
        if(currentDialNum==0){
            zeroCount++;
        }
    }

    inputFile.close();

    cout<<zeroCount<<endl;

    return 0;
}