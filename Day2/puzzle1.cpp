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

        for(unsigned long long i=begin; i<=end; ++i){
            string numAsString = to_string(i);
            if(numAsString.size()%2==0){
                string firstHalf = numAsString.substr(0, numAsString.size()/2);
                string secondHalf = numAsString.substr(numAsString.size()/2);
                //cout<<"Original Number: "<<numAsString<<", first half: "<<firstHalf<<", second half: "<<secondHalf<<endl;
                if(firstHalf==secondHalf){
                    sum_invalid_ids+=i;
                }
            }
        }
    }

    cout<<sum_invalid_ids<<endl;
    return 0;
}