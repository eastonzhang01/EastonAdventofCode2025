#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("Day2Input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }

    unsigned long long sum_invalid_ids=0;
    string number_range="";
    char range_delimiter=',';

    while(getline(inputFile, number_range, range_delimiter)){
        //cout<<number_range<<endl;
        size_t delimit_position = number_range.find('-');
        string beginNumString=number_range.substr(0, delimit_position);
        string endNumString = number_range.substr(delimit_position+1);
        //cout<<beginNumString<<" "<<endNumString<<endl;

        unsigned long long begin = stoull(beginNumString);
        unsigned long long end = stoull(endNumString);

        // loop through each number in the range ex: 11-22
        for(unsigned long long i=begin; i <=end; ++i){
            string numAsString = to_string(i);
            // within each number, we loop through the first half of the characters to check each "pattern" from 1 character up to half the size
            for(size_t j=0; j<numAsString.size()/2; ++j){
                // get the pattern based on where we are in the loop
                string pattern = numAsString.substr(0, j+1);
                size_t ind_start_compare = j+1;
                bool repeating = true;
                // increment through each other part of the number to check that the pattern is actually repeating
                while(ind_start_compare<numAsString.size()){
                    if(pattern!=numAsString.substr(ind_start_compare, j+1)){
                        repeating=false;
                    }
                    ind_start_compare +=j+1;
                }
                // if we find a repeating pattern we add to sum and break out of loop for current number
                if(repeating==true){
                    sum_invalid_ids+=i;
                    j=numAsString.size();
                }
            }
        }
    }

    cout<<sum_invalid_ids<<endl;
    return 0;
}