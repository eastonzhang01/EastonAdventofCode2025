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

int main() {
    ifstream inputFile("puzzle_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }
    string line;
    getline(inputFile, line);

    vector<unsigned long long> low_nums;
    vector<unsigned long long> high_nums;
    unsigned long long num_fresh=0;
    while(line != ""){
        stringstream ss(line);
        char delimiter='-';

        string low_num;
        string high_num;

        getline(ss, low_num, delimiter);
        getline(ss, high_num);
        unsigned long long low = stoull(low_num);
        unsigned long long high = stoull(high_num);

        low_nums.push_back(low);
        high_nums.push_back(high);

        getline(inputFile, line);
    }

    while(getline(inputFile, line)){
        unsigned long long num = stoull(line);

        for(int i=0; i<low_nums.size(); ++i){
            if(num>=low_nums[i] && num<=high_nums[i]){
                num_fresh++;
                break;
            }
        }

    }
    cout<<num_fresh<<endl;
    return 0;
}