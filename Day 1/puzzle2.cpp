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
        
        int fullRotateCount = number/100;
        zeroCount = zeroCount + fullRotateCount;

        int remainder = number % 100;
        //cout <<line<<" "<<rotation<<" "<<number<<" "<<remainder<<" "<<fullRotateCount<<endl;

        if(rotation == 'L'){
            if(currentDialNum-remainder<0){
                if(currentDialNum!=0){
                    zeroCount++;
                }
                currentDialNum = 100 + currentDialNum - remainder;
            }
            else{
                currentDialNum = currentDialNum - remainder;
                if(currentDialNum==0){
                    zeroCount++;
                }
            }
        }
        else if(rotation == 'R'){
            if(currentDialNum+remainder>99){
                if(currentDialNum!=0){
                    zeroCount++;
                }
                currentDialNum = currentDialNum+remainder-100;
            }
            else{
                currentDialNum = currentDialNum + remainder;
                if(currentDialNum==0){
                    zeroCount++;
                }
            }
        }
        
        cout<<"After rotating "<<rotation<<" by "<<remainder<<" the dial is at "<<currentDialNum<<" and zerocount is "<<zeroCount<<endl;
    }

    inputFile.close();

    cout<<zeroCount<<endl;

    return 0;
}