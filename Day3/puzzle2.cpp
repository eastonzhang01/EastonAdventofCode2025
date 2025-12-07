#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include <set>

using namespace std;

int main() {
    ifstream inputFile("puzzle_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }

    string line;
    unsigned long long totalJoltage = 0;
    while(getline(inputFile, line)){
        string joltage = "";
        // have left and right to look at window
        int left_most_pos = 0;
        int right_most_pos = line.size() - 12;
        // for each digit we just get the biggest number within that number's window
        while(joltage.size()!=12){
            char greatest_num = '0';
            int greatest_num_pos = -1;
            cout<<"For joltage size = "<<joltage.size()<<" looking at window: "<<right_most_pos<<" | "<<left_most_pos<<endl;
            // look from right to left
            for(int i=right_most_pos; i>=left_most_pos; --i){
                if(line[i]>=greatest_num){
                    greatest_num = line[i];
                    greatest_num_pos = i;
                }
            }
            cout<<"    greatest num found: "<<greatest_num<<" at position: "<<greatest_num_pos<<endl;
            // change the window based on the number found
            joltage+=greatest_num;
            left_most_pos = greatest_num_pos+1;
            right_most_pos++;
        }
        unsigned long long real_number = stoull(joltage);
        cout<<line<<" has largest joltage: "<<real_number<<endl;
        totalJoltage += real_number;
    }
        

    cout<<totalJoltage<<endl;
    if(totalJoltage==3121910778619){
        cout<<"Match Test Value!"<<endl;
    }
    else{
        cout<<"Does not Match"<<endl;
    }
    return 0;
}















/*
int main() {
    ifstream inputFile("puzzle_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }

    string line;
    unsigned long long totalJoltage = 0;
    while(getline(inputFile, line)){
        vector<int> digits;
        //initialize first 12 spots to first spots in line
        for(int i=0; i<12; ++i){
            digits.push_back(i);
        }
        cout<<"Got here"<<endl;
        for(int i=0; i<line.size(); ++i){
            cout<<"Enter "<<i<<" line loop"<<endl;
            // calculate the number of digits available left in the line
            int availableDigitsLeft = line.size()-i;
            int digits_starting_pos = 0;
            if(availableDigitsLeft<12){
                digits_starting_pos = 12-availableDigitsLeft;
            }
            //cout<<"i: "<<i<<" digit_starting_pos: "<<digits_starting_pos<<endl;

            // look through digits, but only starting at available digits left
            // end at 
            for(int j=digits_starting_pos; j<=i; ++j){
                // check if the number we are looking at is bigger than digits left
                //cout<<"digits[j] = "<<digits[j]<<" and j = "<<j<<endl;
                // check that the previous digit is not assigned to spot at i we are looking at
                if(j>0 && digits[j-1]==i){
                    break;
                }

                if(line[i]>line[digits[j]]){
                    //replace the current digit and all subsequent ones
                    int temp_pos = i;
                    while(j<12){
                        //cout<<"Replacing digits[j] "<<j<<" with "<<line[temp_pos]<<endl;
                        digits[j]=temp_pos;
                        ++j; ++temp_pos;
                    }
                    break;
                }
            }
        }
        //combine characters to create number
        string digits_concat = "";
        for(int i=0; i<12; ++i){
            digits_concat+=line[digits[i]];
        }

        unsigned long long real_number = stoull(digits_concat);
        cout<<line<<" has largest joltage: "<<real_number<<endl;
        totalJoltage += real_number;
    }

    cout<<totalJoltage<<endl;
    if(totalJoltage==3121910778619){
        cout<<"Match Test Value!"<<endl;
    }
    else{
        cout<<"Does not Match"<<endl;
    }
    return 0;
}
*/